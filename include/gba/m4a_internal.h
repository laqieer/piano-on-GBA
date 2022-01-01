#ifndef GUARD_GBA_M4A_INTERNAL_H
#define GUARD_GBA_M4A_INTERNAL_H

#include "gba/gba.h"

// ASCII encoding of 'Smsh' in reverse
// This is presumably short for SMASH, the developer of MKS4AGB.
#define ID_NUMBER 0x68736D53

#define C_V 0x40 // center value for PAN, BEND, and TUNE

#define SOUND_MODE_REVERB_VAL   0x0000007F
#define SOUND_MODE_REVERB_SET   0x00000080
#define SOUND_MODE_MAXCHN       0x00000F00
#define SOUND_MODE_MAXCHN_SHIFT 8
#define SOUND_MODE_MASVOL       0x0000F000
#define SOUND_MODE_MASVOL_SHIFT 12
#define SOUND_MODE_FREQ_05734   0x00010000
#define SOUND_MODE_FREQ_07884   0x00020000
#define SOUND_MODE_FREQ_10512   0x00030000
#define SOUND_MODE_FREQ_13379   0x00040000
#define SOUND_MODE_FREQ_15768   0x00050000
#define SOUND_MODE_FREQ_18157   0x00060000
#define SOUND_MODE_FREQ_21024   0x00070000
#define SOUND_MODE_FREQ_26758   0x00080000
#define SOUND_MODE_FREQ_31536   0x00090000
#define SOUND_MODE_FREQ_36314   0x000A0000
#define SOUND_MODE_FREQ_40137   0x000B0000
#define SOUND_MODE_FREQ_42048   0x000C0000
#define SOUND_MODE_FREQ         0x000F0000
#define SOUND_MODE_FREQ_SHIFT   16
#define SOUND_MODE_DA_BIT_9     0x00800000
#define SOUND_MODE_DA_BIT_8     0x00900000
#define SOUND_MODE_DA_BIT_7     0x00A00000
#define SOUND_MODE_DA_BIT_6     0x00B00000
#define SOUND_MODE_DA_BIT       0x00B00000
#define SOUND_MODE_DA_BIT_SHIFT 20

struct WaveData
{
    u16 type;
    u16 status;
    u32 freq;
    u32 loopStart;
    u32 size; // number of samples
    s8 data[1]; // samples
};

#define TONEDATA_TYPE_CGB    0x07
#define TONEDATA_TYPE_FIX    0x08
#define TONEDATA_TYPE_SPL    0x40 // key split
#define TONEDATA_TYPE_RHY    0x80 // rhythm

#define TONEDATA_P_S_PAN    0xc0
#define TONEDATA_P_S_PAM    TONEDATA_P_S_PAN

struct ToneData
{
    u8 type; //0x24
    u8 key;
    u8 length; // sound length (compatible sound)
    u8 pan_sweep; // pan or sweep (compatible sound ch. 1)
    union{
        struct WaveData *wav;
        u32 subInstrument;
    };
    union{
        struct{
            u8 attack; //0x2C
            u8 decay;
            u8 sustain;
            u8 release;
        };
        u8 *keySplitTable;
    };
};

#define SOUND_CHANNEL_SF_START       0x80
#define SOUND_CHANNEL_SF_STOP        0x40
#define SOUND_CHANNEL_SF_LOOP        0x10
#define SOUND_CHANNEL_SF_IEC         0x04
#define SOUND_CHANNEL_SF_ENV         0x03
#define SOUND_CHANNEL_SF_ENV_ATTACK  0x03
#define SOUND_CHANNEL_SF_ENV_DECAY   0x02
#define SOUND_CHANNEL_SF_ENV_SUSTAIN 0x01
#define SOUND_CHANNEL_SF_ENV_RELEASE 0x00
#define SOUND_CHANNEL_SF_ON (SOUND_CHANNEL_SF_START | SOUND_CHANNEL_SF_STOP | SOUND_CHANNEL_SF_IEC | SOUND_CHANNEL_SF_ENV)

#define CGB_CHANNEL_MO_PIT  0x02
#define CGB_CHANNEL_MO_VOL  0x01

#define CGB_NRx2_ENV_DIR_DEC 0x00
#define CGB_NRx2_ENV_DIR_INC 0x08

struct CgbChannel
{
    u8 statusFlags;
    u8 type;
    u8 rightVolume;
    u8 leftVolume;
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 key;
    u8 envelopeVolume;
    u8 envelopeGoal;
    u8 envelopeCounter;
    u8 pseudoEchoVolume;
    u8 pseudoEchoLength;
    u8 dummy1;
    u8 dummy2;
    u8 gateTime; //0x10
    u8 midiKey;
    u8 velocity;
    u8 priority;
    u8 rhythmPan;
    u8 dummy3[3];
    u8 dummy5;
    u8 sustainGoal;
    u8 n4;                  // NR[1-4]4 register (initial, length bit)
    u8 pan;
    u8 panMask;
    u8 modify;
    u8 length;
    u8 sweep;
    u32 frequency; //0x20
    u32 *wavePointer;       // instructs CgbMain to load targeted wave
    u32 *currentPointer;    // stores the currently loaded wave
    struct MusicPlayerTrack *track;
    void *prevChannelPointer; //0x30
    void *nextChannelPointer;
    u8 dummy4[8];
};

struct MusicPlayerTrack;

struct SoundChannel
{
    u8 statusFlags;
    u8 type;
    u8 rightVolume;
    u8 leftVolume;
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 key;             // midi key as it was translated into final pitch
    u8 envelopeVolume;
    u8 envelopeVolumeRight;
    u8 envelopeVolumeLeft;
    u8 pseudoEchoVolume;
    u8 pseudoEchoLength;
    u8 dummy1;
    u8 dummy2;
    u8 gateTime; //0x10
    u8 midiKey;         // midi key as it was used in the track data
    u8 velocity;
    u8 priority;
    u8 rhythmPan;
    u8 dummy3[3];
    u32 count;
    u32 fw;
    u32 frequency; //0x20
    struct WaveData *wav;
    s8 *currentPointer;
    struct MusicPlayerTrack *track;
    void *prevChannelPointer; //0x30
    void *nextChannelPointer;
    u32 dummy4;
    u16 xpi;
    u16 xpc;
};

#define MAX_DIRECTSOUND_CHANNELS 12

#define PCM_DMA_BUF_SIZE 1584 // size of Direct Sound buffer

struct MusicPlayerInfo;

typedef void (*MPlayFunc)();
typedef void (*PlyNoteFunc)(u32, struct MusicPlayerInfo *, struct MusicPlayerTrack *);
typedef void (*CgbSoundFunc)(void);
typedef void (*CgbOscOffFunc)(u8);
typedef u32 (*MidiKeyToCgbFreqFunc)(u8, u8, u8);
typedef void (*ExtVolPitFunc)(void);
typedef void (*MPlayMainFunc)(struct MusicPlayerInfo *);

struct SoundInfo
{
    // This field is normally equal to ID_NUMBER but it is set to other
    // values during sensitive operations for locking purposes.
    // This field should be volatile but isn't. This could potentially cause
    // race conditions.
    u32 ident;

    vu8 pcmDmaCounter;

    // Direct Sound
    u8 reverb;
    u8 maxChans;
    u8 masterVolume;
    u8 freq;

    u8 mode;
    u8 c15;          // periodically counts from 14 down to 0 (15 states)
    u8 pcmDmaPeriod; // number of V-blanks per PCM DMA
    u8 maxLines;
    u8 gap[3];
    s32 pcmSamplesPerVBlank; //0x10
    s32 pcmFreq;
    s32 divFreq;
    struct CgbChannel *cgbChans;
    MPlayMainFunc MPlayMainHead; //0x20
    struct MusicPlayerInfo *musicPlayerHead;
    CgbSoundFunc CgbSound;
    CgbOscOffFunc CgbOscOff;
    MidiKeyToCgbFreqFunc MidiKeyToCgbFreq; //0x30
    MPlayFunc *MPlayJumpTable;
    PlyNoteFunc plynote;
    ExtVolPitFunc ExtVolPit;
    u8 gap2[16]; //0x40
    struct SoundChannel chans[MAX_DIRECTSOUND_CHANNELS]; //0x50
    s8 pcmBuffer[PCM_DMA_BUF_SIZE * 2];
};

struct SongHeader
{
    u8 trackCount;
    u8 blockCount;
    u8 priority;
    u8 reverb;
    struct ToneData *tone;
    u8 *part[1];
};

struct PokemonCrySong
{
    u8 trackCount;
    u8 blockCount;
    u8 priority;
    u8 reverb;
    struct ToneData *tone;
    u8 *part[2];
    u8 gap;
    u8 part0; // 0x11
    u8 tuneValue; // 0x12
    u8 gotoCmd; // 0x13
    u32 gotoTarget; // 0x14
    u8 part1; // 0x18
    u8 tuneValue2; // 0x19
    u8 cont[2]; // 0x1A
    u8 volCmd; // 0x1C
    u8 volumeValue; // 0x1D
    u8 unkCmd0D[2]; // 0x1E
    u32 unkCmd0DParam; // 0x20
    u8 xreleCmd[2]; // 0x24
    u8 releaseValue; // 0x26
    u8 panCmd;
    u8 panValue; // 0x28
    u8 tieCmd; // 0x29
    u8 tieKeyValue; // 0x2A
    u8 tieVelocityValue; // 0x2B
    u8 unkCmd0C[2]; // 0x2C
    u16 unkCmd0CParam; // 0x2E
    u8 end[2]; // 0x30
};

#define MPT_FLG_VOLSET 0x01
#define MPT_FLG_VOLCHG 0x03
#define MPT_FLG_PITSET 0x04
#define MPT_FLG_PITCHG 0x0C
#define MPT_FLG_START  0x40
#define MPT_FLG_EXIST  0x80

struct MusicPlayerTrack
{
    u8 flags;
    u8 wait;
    u8 patternLevel;
    u8 repN;
    u8 gateTime;
    u8 key;
    u8 velocity;
    u8 runningStatus;
    u8 keyM;
    u8 pitM;
    s8 keyShift;
    s8 keyShiftX;
    s8 tune;
    u8 pitX;
    s8 bend;
    u8 bendRange;
    u8 volMR;//0x10
    u8 volML;
    u8 vol;
    u8 volX;
    s8 pan;
    s8 panX;
    s8 modM;
    u8 mod;
    u8 modT;
    u8 lfoSpeed;
    u8 lfoSpeedC;
    u8 lfoDelay;
    u8 lfoDelayC;
    u8 priority;
    u8 pseudoEchoVolume;
    u8 pseudoEchoLength;
    struct SoundChannel *chan; //0x20
    struct ToneData tone; //0x24
    u8 gap[10];//0x30
    u16 unk_3A;
    u32 unk_3C;
    u8 *cmdPtr;
    u8 *patternStack[3];
};

#define MUSICPLAYER_STATUS_TRACK 0x0000ffff
#define MUSICPLAYER_STATUS_PAUSE 0x80000000

#define MAX_MUSICPLAYER_TRACKS 16

#define TEMPORARY_FADE  0x0001
#define FADE_IN         0x0002
#define FADE_VOL_MAX    64
#define FADE_VOL_SHIFT  2

struct MusicPlayerInfo
{
    struct SongHeader *songHeader;
    u32 status;
    u8 trackCount;
    u8 priority;
    u8 cmd;
    u8 unk_B;
    u32 clock;
    u8 gap[8];
    u8 *memAccArea;
    u16 tempoD; //0x18
    u16 tempoU;
    u16 tempoI;
    u16 tempoC;
    u16 fadeOI;
    u16 fadeOC;
    u16 fadeOV;
    struct MusicPlayerTrack *tracks;
    struct ToneData *tone;
    u32 ident;
    MPlayMainFunc MPlayMainNext;
    struct MusicPlayerInfo *musicPlayerNext;
};

struct MusicPlayer
{
    struct MusicPlayerInfo *info;
    struct MusicPlayerTrack *track;
    u8 unk_8;
    u16 unk_A;
};

struct Song
{
    struct SongHeader *header;
    u16 ms;
    u16 me;
};

extern const struct MusicPlayer gMPlayTable[];
extern const struct Song gSongTable[];



extern u8 gMPlayMemAccArea[];

//u8 gPokemonCrySong[52];
//u8 gPokemonCrySongs[52 * MAX_POKEMON_CRIES];

#define MAX_POKEMON_CRIES 2

extern struct PokemonCrySong gPokemonCrySong;
extern struct PokemonCrySong gPokemonCrySongs[];

extern struct MusicPlayerInfo gPokemonCryMusicPlayers[];
extern struct MusicPlayerTrack gPokemonCryTracks[];

extern char SoundMainRAM[];

extern MPlayFunc gMPlayJumpTable[];

typedef void (*XcmdFunc)(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
extern const XcmdFunc gXcmdTable[];

extern struct CgbChannel gCgbChans[];

extern const u8 gScaleTable[];
extern const u32 gFreqTable[];
extern const u16 gPcmSamplesPerVBlankTable[];

extern const u8 gCgbScaleTable[];
extern const s16 gCgbFreqTable[];
extern const u8 gNoiseTable[];

extern const struct PokemonCrySong gPokemonCrySongTemplate;

extern const struct ToneData voicegroup000;
extern const struct ToneData voicegroup001;
extern const struct ToneData voicegroup002;
extern const struct ToneData voicegroup003;
extern const struct ToneData voicegroup004;
extern const struct ToneData voicegroup005;
extern const struct ToneData voicegroup006;
extern const struct ToneData voicegroup007;
extern const struct ToneData voicegroup008;
extern const struct ToneData voicegroup009;
extern const struct ToneData voicegroup117;

extern char gNumMusicPlayers[];
extern char gMaxLines[];

#define NUM_MUSIC_PLAYERS ((u16)gNumMusicPlayers)
#define MAX_LINES ((u32)gMaxLines)

u32 umul3232H32(u32 multiplier, u32 multiplicand);
void SoundMain(void);
void SoundMainBTM(void);
void TrackStop(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track);
void MPlayMain(struct MusicPlayerInfo *);
void RealClearChain(void *x);

void MPlayContinue(struct MusicPlayerInfo *mplayInfo);
void MPlayStart(struct MusicPlayerInfo *mplayInfo, struct SongHeader *songHeader);
void m4aMPlayStop(struct MusicPlayerInfo *mplayInfo);
void FadeOutBody(struct MusicPlayerInfo *mplayInfo);
void TrkVolPitSet(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track);
void MPlayFadeOut(struct MusicPlayerInfo *mplayInfo, u16 speed);
void ClearChain(void *x);
void Clear64byte(void *addr);
void SoundInit(struct SoundInfo *soundInfo);
void MPlayExtender(struct CgbChannel *cgbChans);
void m4aSoundMode(u32 mode);
void MPlayOpen(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track, u8 a3);
void CgbSound(void);
void CgbOscOff(u8);
void CgbModVol(struct CgbChannel *chan);
u32 MidiKeyToCgbFreq(u8, u8, u8);
void DummyFunc(void);
void MPlayJumpTableCopy(MPlayFunc *mplayJumpTable);
void SampleFreqSet(u32 freq);
void m4aSoundVSyncOn(void);
void m4aSoundVSyncOff(void);

void m4aMPlayTempoControl(struct MusicPlayerInfo *mplayInfo, u16 tempo);
void m4aMPlayVolumeControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u16 volume);
void m4aMPlayPitchControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, s16 pitch);
void m4aMPlayPanpotControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, s8 pan);
void ClearModM(struct MusicPlayerInfo *mplayInfo, struct MusicPlayerTrack *track);
void m4aMPlayModDepthSet(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u8 modDepth);
void m4aMPlayLFOSpeedSet(struct MusicPlayerInfo *mplayInfo, u16 trackBits, u8 lfoSpeed);

struct MusicPlayerInfo *SetPokemonCryTone(struct ToneData *tone);
void SetPokemonCryVolume(u8 val);
void SetPokemonCryPanpot(s8 val);
void SetPokemonCryPitch(s16 val);
void SetPokemonCryLength(u16 val);
void SetPokemonCryRelease(u8 val);
void SetPokemonCryProgress(u32 val);
int IsPokemonCryPlaying(struct MusicPlayerInfo *mplayInfo);
void SetPokemonCryChorus(s8 val);
void SetPokemonCryStereo(u32 val);
void SetPokemonCryPriority(u8 val);

// sound command handler functions
void ply_fine(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_goto(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_patt(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_pend(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_rept(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_memacc(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_prio(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_tempo(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_keysh(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_voice(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_vol(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_pan(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_bend(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_bendr(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_lfos(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_lfodl(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_mod(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_modt(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_tune(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_port(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xcmd(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_endtie(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_note(u32 note_cmd, struct MusicPlayerInfo *, struct MusicPlayerTrack *);

// extended sound command handler functions
void ply_xxx(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xwave(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xtype(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xatta(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xdeca(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xsust(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xrele(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xiecv(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xiecl(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xleng(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xswee(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xcmd_0C(struct MusicPlayerInfo *, struct MusicPlayerTrack *);
void ply_xcmd_0D(struct MusicPlayerInfo *, struct MusicPlayerTrack *);

#define W00	0x80		
#define W01	W00+1		
#define W02	W00+2		
#define W03	W00+3		
#define W04	W00+4		
#define W05	W00+5		
#define W06	W00+6		
#define W07	W00+7		
#define W08	W00+8		
#define W09	W00+9		
#define W10	W00+10		
#define W11	W00+11		
#define W12	W00+12		
#define W13	W00+13		
#define W14	W00+14		
#define W15	W00+15		
#define W16	W00+16		
#define W17	W00+17		
#define W18	W00+18		
#define W19	W00+19		
#define W20	W00+20		
#define W21	W00+21		
#define W22	W00+22		
#define W23	W00+23		
#define W24	W00+24		
#define W28	W00+25		
#define W30	W00+26		
#define W32	W00+27		
#define W36	W00+28		
#define W40	W00+29		
#define W42	W00+30		
#define W44	W00+31		
#define W48	W00+32		
#define W52	W00+33		
#define W54	W00+34		
#define W56	W00+35		
#define W60	W00+36		
#define W64	W00+37		
#define W66	W00+38		
#define W68	W00+39		
#define W72	W00+40		
#define W76	W00+41		
#define W78	W00+42		
#define W80	W00+43		
#define W84	W00+44		
#define W88	W00+45		
#define W90	W00+46		
#define W92	W00+47		
#define W96	W00+48		

#define FINE   0xb1
#define GOTO   0xb2
#define PATT   0xb3
#define PEND   0xb4
#define REPT   0xb5
#define MEMACC 0xb9
#define PRIO   0xba
#define TEMPO  0xbb
#define KEYSH  0xbc
#define VOICE  0xbd
#define VOL    0xbe
#define PAN    0xbf
#define BEND   0xc0
#define BENDR  0xc1
#define LFOS   0xc2
#define LFODL  0xc3
#define MOD    0xc4
#define MODT   0xc5
#define TUNE   0xc8

#define XCMD   0xcd
#define xRELE  0x07
#define xIECV  0x08
#define xIECL  0x09

#define EOT    0xce
#define TIE    0xcf

#define N01	TIE+1		
#define N02	N01+1		
#define N03	N01+2		
#define N04	N01+3		
#define N05	N01+4		
#define N06	N01+5		
#define N07	N01+6		
#define N08	N01+7		
#define N09	N01+8		
#define N10	N01+9		
#define N11	N01+10		
#define N12	N01+11		
#define N13	N01+12		
#define N14	N01+13		
#define N15	N01+14		
#define N16	N01+15		
#define N17	N01+16		
#define N18	N01+17		
#define N19	N01+18		
#define N20	N01+19		
#define N21	N01+20		
#define N22	N01+21		
#define N23	N01+22		
#define N24	N01+23		
#define N28	N01+24		
#define N30	N01+25		
#define N32	N01+26		
#define N36	N01+27		
#define N40	N01+28		
#define N42	N01+29		
#define N44	N01+30		
#define N48	N01+31		
#define N52	N01+32		
#define N54	N01+33		
#define N56	N01+34		
#define N60	N01+35		
#define N64	N01+36		
#define N66	N01+37		
#define N68	N01+38		
#define N72	N01+39		
#define N76	N01+40		
#define N78	N01+41		
#define N80	N01+42		
#define N84	N01+43		
#define N88	N01+44		
#define N90	N01+45		
#define N92	N01+46		
#define N96	N01+47		

#define CnM2	0		
#define CsM2	1		
#define DnM2	2		
#define DsM2	3		
#define EnM2	4		
#define FnM2	5		
#define FsM2	6		
#define GnM2	7		
#define GsM2	8		
#define AnM2	9		
#define AsM2	10		
#define BnM2	11		
#define CnM1	12		
#define CsM1	13		
#define DnM1	14		
#define DsM1	15		
#define EnM1	16		
#define FnM1	17		
#define FsM1	18		
#define GnM1	19		
#define GsM1	20		
#define AnM1	21		
#define AsM1	22		
#define BnM1	23		
#define Cn0 	24		
#define Cs0 	25		
#define Dn0 	26		
#define Ds0 	27		
#define En0 	28		
#define Fn0 	29		
#define Fs0 	30		
#define Gn0 	31		
#define Gs0 	32		
#define An0 	33		
#define As0 	34		
#define Bn0 	35		
#define Cn1 	36		
#define Cs1 	37		
#define Dn1 	38		
#define Ds1 	39		
#define En1 	40		
#define Fn1 	41		
#define Fs1 	42		
#define Gn1 	43		
#define Gs1 	44		
#define An1 	45		
#define As1 	46		
#define Bn1 	47		
#define Cn2 	48		
#define Cs2 	49	
#define Dn2 	50	
#define Ds2 	51	
#define En2 	52	
#define Fn2 	53	
#define Fs2 	54	
#define Gn2 	55	
#define Gs2 	56	
#define An2 	57	
#define As2 	58	
#define Bn2 	59	
#define Cn3 	60	
#define Cs3 	61	
#define Dn3 	62	
#define Ds3 	63	
#define En3 	64	
#define Fn3 	65	
#define Fs3 	66	
#define Gn3 	67	
#define Gs3 	68	
#define An3 	69	//440Hz
#define As3 	70	
#define Bn3 	71	
#define Cn4 	72	
#define Cs4 	73	
#define Dn4 	74	
#define Ds4 	75	
#define En4 	76	
#define Fn4 	77	
#define Fs4 	78	
#define Gn4 	79	
#define Gs4 	80	
#define An4 	81	
#define As4 	82	
#define Bn4 	83	
#define Cn5 	84	
#define Cs5 	85	
#define Dn5 	86	
#define Ds5 	87	
#define En5 	88	
#define Fn5 	89	
#define Fs5 	90	
#define Gn5 	91	
#define Gs5 	92	
#define An5 	93	
#define As5 	94	
#define Bn5 	95	
#define Cn6 	96	
#define Cs6 	97	
#define Dn6 	98	
#define Ds6 	99	
#define En6 	100	
#define Fn6 	101	
#define Fs6 	102	
#define Gn6 	103	
#define Gs6 	104	
#define An6 	105	
#define As6 	106	
#define Bn6 	107	
#define Cn7 	108	
#define Cs7 	109	
#define Dn7 	110	
#define Ds7 	111	
#define En7 	112	
#define Fn7 	113	
#define Fs7 	114	
#define Gn7 	115	
#define Gs7 	116	
#define An7 	117	
#define As7 	118	
#define Bn7 	119	
#define Cn8 	120	
#define Cs8 	121	
#define Dn8 	122	
#define Ds8 	123	
#define En8 	124	
#define Fn8 	125	
#define Fs8 	126	
#define Gn8 	127	

#endif // GUARD_GBA_M4A_INTERNAL_H
