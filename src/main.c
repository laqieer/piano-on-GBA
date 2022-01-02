#include "gba/gba.h"
#include "crt0.h"
#include "m4a.h"
#include "main.h"
#include "mgba.h"

#include <string.h>

static void VBlankIntr(void);
static void VCountIntr(void);
static volatile bool8 sGpuRegBufferLocked;
static vu16 sRegIE;

#define GPU_REG_BUF_SIZE 0x60

#define GPU_REG_BUF(offset) (*(u16 *)(&sGpuRegBuffer[offset]))
#define GPU_REG(offset) (*(vu16 *)(REG_BASE + offset))

static u8 sGpuRegBuffer[GPU_REG_BUF_SIZE];
static u8 sGpuRegWaitingList[GPU_REG_BUF_SIZE];
const IntrFunc gIntrTableTemplate[] =
{
    VCountIntr, // V-count interrupt
    NULL, // Serial interrupt
    NULL, // Timer 3 interrupt
    NULL, // H-blank interrupt
    VBlankIntr, // V-blank interrupt
    NULL,  // Timer 0 interrupt
    NULL,  // Timer 1 interrupt
    NULL,  // Timer 2 interrupt
    NULL,  // DMA 0 interrupt
    NULL,  // DMA 1 interrupt
    NULL,  // DMA 2 interrupt
    NULL,  // DMA 3 interrupt
    NULL,  // Key interrupt
    NULL,  // Game Pak interrupt
};

#define INTR_COUNT ((int)(sizeof(gIntrTableTemplate)/sizeof(IntrFunc)))

struct Main gMain;
IntrFunc gIntrTable[INTR_COUNT];
u32 IntrMain_Buffer[0x200];

void InitIntrHandlers(void);
void EnableVCountIntrAtLine150(void);

const u32 gKeyboard61Tiles[] = INCBIN_U32("graphics/keyboard_61.4bpp.lz");
const u32 gKeyboard61Palette[] = INCBIN_U32("graphics/keyboard_61.gbapal.lz");
const u32 gKeyMaskTiles[] = INCBIN_U32("graphics/key_mask.4bpp.lz");
const u32 gKeyMaskPalette[] = INCBIN_U32("graphics/key_mask.gbapal.lz");

void InitBG(void);
void InitOBJ(void);

u8 gAutoplay = 0;

#define MAX_TRACK_SIZE 0x1000
EWRAM_DATA u8 gCurrSongTrack[MAX_TRACK_SIZE];
const struct SongHeader gCurrSongHeader = {1, 0, 1, SOUND_MODE_REVERB_SET+50, &voicegroup005, &gCurrSongTrack};
const struct Song gCurrSong = {&gCurrSongHeader, 0, 0};
void fillSong(char *score);
void fillSongWithNotes(u8 *notes);

const char * const gScores[] = {
    // Lost In Thoughts All Alone (Fire Emblem)
    // (by Rena Strober)
    "6 0 r t|"
	"6 0 r t|"
	"6 0 r t|"
	"6 0 r t|"
	"[u6] 0 r t y o"
	"[u5] 0 r t y o"
	"[u4] 8 w e| [y3]|t|[r5]|"
	"[e4] 8 w e w y"
	"[e5] 9 e r w|"
	"[e4] 8 w e u y"
	"[u5] 9 e r|"
	"[u6] 0 r t y o"
	"[u5] 0 r t y o"
	"[u4] 8 w e| [y3]|t|[r5]|"
	"[e4] 8 w e w y"
	"[e5] 9 e r w|"
	"[e6]|0|w|e||u|"
	"[p4] 8 q [qo4]| [wu5]||"
	"5 9 w 9 [wu5] I"
	"[o3] 7 0 [I30]| [y92]||"
	"2 6 9 6 [y92] u"
	"[i1] 5 8 [u5] [81]|"
	"[t81]|[y81]|[r81]|"
	"[e4] [r8] [qe] 8 q [w8]"
	"[e4] [r8] [qe] 8 q [w8]"
	"[e5] [r9] [we] 9 w [w9]"
	"[e5] [u9] [wu] 9 [yw] 9 [uq84]||"
	"[u6] 0 r t y o"
	"[u5] 0 r t y o"
	"[u4] 8 w e| [y3]|t|[r5]|"
	"[e4] 8 w e w y"
	"[e5] 9 e r w|"
	"[e4] 8 w e u y"
	"[u5] 9 e r|"
	"[u6] 0 r t y o"
	"[u5] 0 r t y o"
	"[u4] 8 w e| [y3]|t|[r5]|"
	"[e4] 8 w e w y"
	"[e5] 9 e r w|"
	"[e6]|0|w|e",
};

u16 __key_curr=0, __key_prev=0;

inline void key_poll()
{
    __key_prev= __key_curr;
    __key_curr= ~REG_KEYINPUT & KEYS_MASK;
}

inline u32 key_pressed(u32 key)
{   return __key_curr & key;  }

inline u32 key_hit(u32 key)
{   return ( __key_curr &~ __key_prev) & key;  }

u8 gCurrNotes[8];

void clearCurrNotes()
{
    memset(gCurrNotes, 0, sizeof(gCurrNotes));
}

enum PITCH {
    PITCH_LOW = 0,
    PITCH_MID,
    PITCH_HIGH,
};

const u8 gNoteLUT[] = {
    Gn3, // L + A
    An3, // L + B
    Bn3, // L + Select
    Cn4, // L + Start
    Dn4, // A
    En4, // B
    Fn4, // Select
    Gn4, // Start
    An4, // R + A
    Bn4, // R + B
    Cn5, // R + Select
    Dn5, // R + Start
};

void EnableKeyInput()
{
    EnableInterrupts(INTR_FLAG_KEYPAD);
    REG_KEYCNT = KEY_INTR_ENABLE | KEYS_MASK;
}

void AgbMain()
{
    InitIntrHandlers();
    EnableVCountIntrAtLine150();
    mgba_open();
    InitBG();
    InitOBJ();
    m4aSoundInit();

    EnableKeyInput();

    for (;;)
    {
        VBlankIntrWait();
    }
}

const int gNotes[128] = {
    ['1'] = Cn2,
    ['!'] = Cs2,
    ['2'] = Dn2,
    ['@'] = Ds2,
    ['3'] = En2,
    ['4'] = Fn2,
    ['$'] = Fs2,
    ['5'] = Gn2,
    ['%'] = Gs2,
    ['6'] = An2,
    ['^'] = As2,
    ['7'] = Bn2,
    ['8'] = Cn3,
    ['*'] = Cs3,
    ['9'] = Dn3,
    ['('] = Ds3,
    ['0'] = En3,
    ['q'] = Fn3,
    ['Q'] = Fs3,
    ['w'] = Gn3,
    ['W'] = Gs3,
    ['e'] = An3,
    ['E'] = As3,
    ['r'] = Bn3,
    ['t'] = Cn4,
    ['T'] = Cs4,
    ['y'] = Dn4,
    ['Y'] = Ds4,
    ['u'] = En4,
    ['i'] = Fn4,
    ['I'] = Fs4,
    ['o'] = Gn4,
    ['O'] = Gs4,
    ['p'] = An4,
    ['P'] = As4,
    ['a'] = Bn4,
    ['s'] = Cn5,
    ['S'] = Cs5,
    ['d'] = Dn5,
    ['D'] = Ds5,
    ['f'] = En5,
    ['g'] = Fn5,
    ['G'] = Fs5,
    ['h'] = Gn5,
    ['H'] = Gs5,
    ['j'] = An5,
    ['J'] = As5,
    ['k'] = Bn5,
    ['l'] = Cn6,
    ['L'] = Cs6,
    ['z'] = Dn6,
    ['Z'] = Ds6,
    ['x'] = En6,
    ['c'] = Fn6,
    ['C'] = Fs6,
    ['v'] = Gn6,
    ['V'] = Gs6,
    ['b'] = An6,
    ['B'] = As6,
    ['n'] = Bn6,
    ['m'] = Cn7,
};

void fillSong(char *score) {
    gCurrSongTrack[0] = KEYSH;
    gCurrSongTrack[1] = 0;
    gCurrSongTrack[2] = TEMPO;
    gCurrSongTrack[3] = 60;
    gCurrSongTrack[4] = VOICE;
    gCurrSongTrack[5] = 0;
    gCurrSongTrack[6] = VOL;
    gCurrSongTrack[7] = 127;
    gCurrSongTrack[8] = PAN;
    gCurrSongTrack[9] = C_V;
    int i = 10;
    for (; *score; score++)
    {
        switch (*score)
        {
            case ' ':
            case '\n':
                break;
            case '|':
                gCurrSongTrack[i++] = W24;
                break;
            case '[':
                int cnt = 0;
                int pos = i;
                score++;
                for (; *score != ']'; score++, cnt++) {
                    gCurrSongTrack[i++] = TIE;
                    gCurrSongTrack[i++] = gNotes[*score];
                    gCurrSongTrack[i++] = 127;
                }
                gCurrSongTrack[i++] = W24;
                for (int j = 0; j < cnt; j++) {
                    gCurrSongTrack[i++] = EOT;
                    gCurrSongTrack[i++] = gCurrSongTrack[pos + 3 * j + 1];
                }
                break;
            case ']':
                mgba_printf(MGBA_LOG_ERROR, "fillSong: unexpected ']' at %s", score);
                break;
            default:
                gCurrSongTrack[i++] = N24;
                gCurrSongTrack[i++] = gNotes[*score];
                gCurrSongTrack[i++] = 127;
                gCurrSongTrack[i++] = W24;
        }
    }
    gCurrSongTrack[i++] = FINE;
    gCurrSongTrack[i++] = 0;
    gCurrSongTrack[i++] = 0;
    gCurrSongTrack[i++] = 0;
}

void fillSongWithNotes(u8 *notes)
{
    gCurrSongTrack[0] = KEYSH;
    gCurrSongTrack[1] = 0;
    gCurrSongTrack[2] = TEMPO;
    gCurrSongTrack[3] = 60;
    gCurrSongTrack[4] = VOICE;
    gCurrSongTrack[5] = 0;
    gCurrSongTrack[6] = VOL;
    gCurrSongTrack[7] = 127;
    gCurrSongTrack[8] = PAN;
    gCurrSongTrack[9] = C_V;
    int i = 10;
    if (notes[0])
    {
        if (notes[1])
        {
            for (int j = 0; notes[j]; j++)
            {
                gCurrSongTrack[i++] = TIE;
                gCurrSongTrack[i++] = notes[j];
                gCurrSongTrack[i++] = 127;
            }
            gCurrSongTrack[i++] = W24;
            for (int j = 0; notes[j]; j++) {
                gCurrSongTrack[i++] = EOT;
                gCurrSongTrack[i++] = notes[j];
            }
        }
        else
        {
            gCurrSongTrack[i++] = N24;
            gCurrSongTrack[i++] = notes[0];
            gCurrSongTrack[i++] = 127;
            gCurrSongTrack[i++] = W24;
        }
    }
    gCurrSongTrack[i++] = FINE;
    gCurrSongTrack[i++] = 0;
    gCurrSongTrack[i++] = 0;
    gCurrSongTrack[i++] = 0;
}

void EnableVCountIntrAtLine150(void)
{
    u16 gpuReg = REG_DISPSTAT | (150 << 8);
    if (REG_OFFSET_DISPSTAT < GPU_REG_BUF_SIZE)
    {
        u16 vcount;

        GPU_REG_BUF(REG_OFFSET_DISPSTAT) = gpuReg | DISPSTAT_VCOUNT_INTR;
        vcount = REG_VCOUNT & 0xFF;

        if ((vcount >= 161 && vcount <= 225) || (REG_DISPCNT & DISPCNT_FORCED_BLANK))
        {
            if (REG_OFFSET_DISPSTAT == REG_OFFSET_DISPSTAT)
            {
                REG_DISPSTAT &= ~(DISPSTAT_HBLANK_INTR | DISPSTAT_VBLANK_INTR);
                REG_DISPSTAT |= GPU_REG_BUF(REG_OFFSET_DISPSTAT);
            }
        }
        else
        {
            s32 i;

            sGpuRegBufferLocked = TRUE;

            for (i = 0; i < GPU_REG_BUF_SIZE && sGpuRegWaitingList[i] != 0xFF; i++)
            {
                if (sGpuRegWaitingList[i] == REG_OFFSET_DISPSTAT)
                {
                    sGpuRegBufferLocked = FALSE;
                    return;
                }
            }

            sGpuRegWaitingList[i] = REG_OFFSET_DISPSTAT;
            sGpuRegBufferLocked = FALSE;
        }
    }
    EnableInterrupts(INTR_FLAG_VCOUNT);
}

void InitIntrHandlers(void)
{
    int i;

    for (i = 0; i < INTR_COUNT; i++)
        gIntrTable[i] = gIntrTableTemplate[i];

    DmaCopy32(3, IntrMain, IntrMain_Buffer, sizeof(IntrMain_Buffer));

    INTR_VECTOR = IntrMain_Buffer;

    REG_IME = 1;

    EnableInterrupts(INTR_FLAG_VBLANK);
}

static void VBlankIntr(void)
{
    m4aSoundMain();

    key_poll();

    u8 autoplay = gAutoplay;
    if (key_hit(DPAD_UP))
    {
        gAutoplay = 1 - gAutoplay;
    }

    if (gAutoplay)
    {
        if (!autoplay)
        {
            fillSong(gScores[0]);
            m4aSongStart(&gCurrSong);
        }
        return;
    }

    if (autoplay)
    {
        m4aSongStop(&gCurrSong);
    }

    clearCurrNotes();

    enum PITCH pitch = PITCH_MID;
    if (key_pressed(L_BUTTON))
    {
        pitch = PITCH_LOW;
    }
    if (key_pressed(R_BUTTON))
    {
        pitch = PITCH_HIGH;
    }

    int i = 0;
    if (key_hit(A_BUTTON))
    {
        gCurrNotes[i++] = gNoteLUT[4 * pitch];
    }
    if (key_hit(B_BUTTON))
    {
        gCurrNotes[i++] = gNoteLUT[4 * pitch + 1];
    }
    if (key_hit(SELECT_BUTTON))
    {
        gCurrNotes[i++] = gNoteLUT[4 * pitch + 2];
    }
    if (key_hit(START_BUTTON))
    {
        gCurrNotes[i++] = gNoteLUT[4 * pitch + 3];
    }

    if (gCurrNotes[0])
    {
        mgba_printf(MGBA_LOG_INFO, "AgbMain: gCurrNotes: %s", gCurrNotes);
        fillSongWithNotes(gCurrNotes);
        m4aSongStart(&gCurrSong);
    }
}

static void VCountIntr(void)
{
    m4aSoundVSync();
}

void EnableInterrupts(u16 mask)
{
    sRegIE |= mask;
    u16 temp = REG_IME;
    REG_IME = 0;
    REG_IE = sRegIE;
    REG_IME = temp;
    u16 oldValue = REG_DISPSTAT & (DISPSTAT_HBLANK_INTR | DISPSTAT_VBLANK_INTR);
    u16 newValue = 0;

    if (sRegIE & INTR_FLAG_VBLANK)
        newValue |= DISPSTAT_VBLANK_INTR;

    if (REG_OFFSET_DISPSTAT < GPU_REG_BUF_SIZE){
        u16 vcount;
        GPU_REG_BUF(REG_OFFSET_DISPSTAT) = newValue;
        vcount = REG_VCOUNT & 0xFF;
        if ((vcount >= 161 && vcount <= 225) || (REG_DISPCNT & DISPCNT_FORCED_BLANK))
        {
            if (REG_OFFSET_DISPSTAT == REG_OFFSET_DISPSTAT)
            {
                REG_DISPSTAT &= ~(DISPSTAT_HBLANK_INTR | DISPSTAT_VBLANK_INTR);
                REG_DISPSTAT |= GPU_REG_BUF(REG_OFFSET_DISPSTAT);
            }
        }
        else
        {
            s32 i;
            sGpuRegBufferLocked = TRUE;
            for (i = 0; i < GPU_REG_BUF_SIZE && sGpuRegWaitingList[i] != 0xFF; i++)
            {
                if (sGpuRegWaitingList[i] == REG_OFFSET_DISPSTAT)
                {
                    sGpuRegBufferLocked = FALSE;
                    return;
                }
            }
            sGpuRegWaitingList[i] = REG_OFFSET_DISPSTAT;
            sGpuRegBufferLocked = FALSE;
        }
    }
}

void fillBGMap()
{
    u16 *map = BG_SCREEN_ADDR(24);
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 30; col++)
        {
            map[row * 32 + col] = row * 30 + col;
        }
    }
}

void InitBG(void)
{
    REG_DISPCNT = DISPCNT_BG0_ON;
    REG_BG0CNT |= BGCNT_SCREENBASE(24);
    LZ77UnCompVram(gKeyboard61Palette, BG_PLTT);
    LZ77UnCompVram(gKeyboard61Tiles, BG_CHAR_ADDR(0));
    fillBGMap();
}

const int gKeyPositions[128][2] = {
    [Cn2] = {0, 72},
    [Cs2] = {4, 56},
    [Dn2] = {7, 72},
    [Ds2] = {11, 56},
    [En2] = {13, 72},
    [Fn2] = {20, 72},
    [Fs2] = {24, 56},
    [Gn2] = {27, 72},
    [Gs2] = {30, 56},
    [An2] = {33, 72},
    [As2] = {37, 56},
    [Bn2] = {40, 72},
    [Cn3] = {46, 72},
    [Cs3] = {50, 56},
    [Dn3] = {53, 72},
    [Ds3] = {58, 56},
    [En3] = {60, 72},
    [Fn3] = {66, 72},
    [Fs3] = {70, 56},
    [Gn3] = {73, 72},
    [Gs3] = {77, 56},
    [An3] = {79, 72},
    [As3] = {84, 56},
    [Bn3] = {86, 72},
    [Cn4] = {93, 72},
    [Cs4] = {97, 56},
    [Dn4] = {100, 72},
    [Ds4] = {104, 56},
    [En4] = {106, 72},
    [Fn4] = {113, 72},
    [Fs4] = {117, 56},
    [Gn4] = {119, 72},
    [Gs4] = {123, 56},
    [An4] = {126, 72},
    [As4] = {130, 56},
    [Bn4] = {132, 72},
    [Cn5] = {139, 72},
    [Cs5] = {143, 56},
    [Dn5] = {146, 72},
    [Ds5] = {150, 56},
    [En5] = {152, 72},
    [Fn5] = {159, 72},
    [Fs5] = {163, 56},
    [Gn5] = {166, 72},
    [Gs5] = {169, 56},
    [An5] = {172, 72},
    [As5] = {176, 56},
    [Bn5] = {179, 72},
    [Cn6] = {185, 72},
    [Cs6] = {189, 56},
    [Dn6] = {192, 72},
    [Ds6] = {196, 56},
    [En6] = {198, 72},
    [Fn6] = {205, 72},
    [Fs6] = {209, 56},
    [Gn6] = {212, 72},
    [Gs6] = {216, 56},
    [An6] = {219, 72},
    [As6] = {223, 56},
    [Bn6] = {225, 72},
    [Cn7] = {232, 72},
};

void fillOAM()
{
    struct OamData oamTmp;
    struct OamData *oam = OAM;
    for (int i = 0; i < 128; i++)
    {
        oamTmp.affineMode = ST_OAM_AFFINE_ERASE;
        oamTmp.objMode = ST_OAM_OBJ_BLEND;
        oamTmp.shape = ST_OAM_V_RECTANGLE;
        oamTmp.x = gKeyPositions[i][0];
        oamTmp.y = gKeyPositions[i][1];
        *(u32 *)(&oam[i]) = *(u32 *)(&oamTmp);
    }
}

void InitOBJ(void)
{
    REG_DISPCNT |= DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP;
    LZ77UnCompVram(gKeyMaskPalette, OBJ_PLTT);
    LZ77UnCompVram(gKeyMaskTiles, OBJ_VRAM0);
    fillOAM();
    REG_BLDCNT = BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0;
    REG_BLDALPHA = BLDALPHA_BLEND(8, 8);
}
