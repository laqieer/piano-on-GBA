#include "gba/gba.h"
#include "crt0.h"
#include "m4a.h"
#include "main.h"
#include "mgba.h"

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

void AgbMain()
{
    InitIntrHandlers();
    EnableVCountIntrAtLine150();
    mgba_open();
    m4aSoundInit();
    m4aSongNumStart(0);
    for (;;)
    {
        VBlankIntrWait();
    }
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
