#include "gba/gba.h"
#include "scores.h"

const char score0[] = INCBIN_S8("scores/LOST_IN_THOUGHTS_ALL_ALONE_from_FIRE_EMBLEM_by_Rena_Strober.txt");
const char score1[] = INCBIN_S8("scores/BEYOND_THE_DISTANT_SKIES_from_FIRE_EMBLEM_by_Yuka_Tsujiyoko.txt");
const char score2[] = INCBIN_S8("scores/FODLAN_NO_GYOUFUU_from_FIRE_EMBLEM_by_Takeru_Kanazaki.txt");
const char score3[] = INCBIN_S8("scores/THE_EDGE_OF_DAWN_from_FIRE_EMBLEM_THREE_HOUSES_by_Yuka_Tsujiyoko.txt");

const int gScoreTempos[] = {
    70,
    125,
    168,
    180,
};

const char * const gScores[] = {
    score0,
    score1,
    score2,
    score3,
};

const int maxSongId = sizeof(gScores) / sizeof(gScores[0]) - 1;
