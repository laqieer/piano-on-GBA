typedef unsigned char   undefined;

typedef unsigned char    u8;
typedef unsigned s32    s32;
typedef long double    longdouble;
typedef long long    longlong;
typedef unsigned char    u8;
typedef unsigned s32    u32;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned s32    undefined4;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef struct _mbstate_t _mbstate_t, *P_mbstate_t;

undefined4 umul3232H32(u32 param_1,u32 param_2)

{
  return (s32)((ulonglong)param_2 * (ulonglong)param_1 >> 0x20);
}



void SoundMain(void)

{
  undefined4 *puVar1;
  
  puVar1 = SOUND_INFO_PTR;
  if ((undefined *)*SOUND_INFO_PTR != &ID_NUMBER) {
    return;
  }
  *SOUND_INFO_PTR = 0x68736d54;
  if (puVar1[8] != 0) {
    _081DD25E(puVar1[9]);
  }
  _081DD25E();
                    // WARNING: Treating indirect jump as call
  (*(code *)(SoundMainRAM_Buffer + 1))();
  return;
}



void SoundMainRAM(s32 param_1)

{
  u32 uVar1;
  u8 bVar2;
  char cVar3;
  s32 iVar4;
  u32 uVar5;
  s32 iVar6;
  u32 uVar7;
  s32 iVar8;
  s32 iVar9;
  s32 iVar10;
  char *pcVar11;
  char *pcVar12;
  s32 unaff_r4;
  undefined4 *unaff_r5;
  u32 *puVar13;
  u32 *puVar14;
  s32 unaff_r6;
  undefined4 *puVar15;
  u32 uVar16;
  u32 uVar17;
  u32 uVar18;
  u32 unaff_r8;
  u32 uVar19;
  u32 uVar20;
  s32 iVar21;
  bool bVar22;
  bool bVar23;
  u32 uStack00000004;
  u32 *in_stack_00000008;
  char *in_stack_0000000c;
  u32 uStack00000010;
  u32 in_stack_00000014;
  undefined4 *in_stack_00000018;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  code *UNRECOVERED_JUMPTABLE;
  
  bVar2 = *(u8 *)(param_1 + 5);
  if (bVar2 == 0) {
    puVar15 = (undefined4 *)(unaff_r6 + (s32)unaff_r5);
    if ((unaff_r8 >> 2 & 1) != 0) {
      *unaff_r5 = 0;
      unaff_r5 = unaff_r5 + 1;
      *puVar15 = 0;
      puVar15 = puVar15 + 1;
    }
    uVar5 = unaff_r8 >> 4;
    if ((unaff_r8 >> 3 & 1) != 0) {
      *unaff_r5 = 0;
      *puVar15 = 0;
      unaff_r5[1] = 0;
      unaff_r5 = unaff_r5 + 2;
      puVar15[1] = 0;
      puVar15 = puVar15 + 2;
    }
    do {
      *unaff_r5 = 0;
      *puVar15 = 0;
      unaff_r5[1] = 0;
      puVar15[1] = 0;
      unaff_r5[2] = 0;
      puVar15[2] = 0;
      unaff_r5[3] = 0;
      unaff_r5 = unaff_r5 + 4;
      puVar15[3] = 0;
      puVar15 = puVar15 + 4;
      uVar7 = uVar5 - 1;
      bVar22 = 0 < (s32)uVar5;
      uVar5 = uVar7;
    } while (uVar7 != 0 && bVar22);
  }
  else {
    uVar5 = unaff_r8;
    if (unaff_r4 == 2) {
      pcVar11 = (char *)(param_1 + 0x350);
    }
    else {
      pcVar11 = (char *)((s32)unaff_r5 + unaff_r8);
    }
    do {
      uVar7 = (s32)(((s32)*(char *)((s32)unaff_r5 + unaff_r6) + (s32)*(char *)unaff_r5 +
                     (s32)pcVar11[unaff_r6] + (s32)*pcVar11) * (u32)bVar2) >> 9;
      cVar3 = (char)uVar7;
      if ((uVar7 & 0x80) != 0) {
        cVar3 = cVar3 + '\x01';
      }
      *(char *)((s32)unaff_r5 + unaff_r6) = cVar3;
      *(char *)unaff_r5 = cVar3;
      uVar7 = uVar5 - 1;
      bVar22 = 0 < (s32)uVar5;
      uVar5 = uVar7;
      unaff_r5 = (undefined4 *)((s32)unaff_r5 + 1);
      pcVar11 = pcVar11 + 1;
    } while (uVar7 != 0 && bVar22);
  }
  iVar4 = in_stack_00000018[6];
  uVar5 = (u32)*(u8 *)((s32)in_stack_00000018 + 6);
  puVar15 = in_stack_00000018 + 0x14;
SoundMainRAM_ChanLoop:
  iVar10 = puVar15[9];
  uStack00000004 = uVar5;
  if (in_stack_00000014 != 0) {
    uVar5 = (u32)REG_VCOUNT;
    if (uVar5 < 0xa0) {
      uVar5 = uVar5 + 0xe4;
    }
    if (in_stack_00000014 <= uVar5) {
_081DD24A:
      *in_stack_00000018 = &ID_NUMBER;
                    // WARNING: Could not recover jumptable at 0x08001f2a. Too many branches
                    // WARNING: Treating indirect jump as call
      (*UNRECOVERED_JUMPTABLE)(in_stack_0000001c,in_stack_00000020,in_stack_00000024);
      return;
    }
  }
  bVar2 = *(u8 *)puVar15;
  uStack00000010 = (u32)bVar2;
  if ((bVar2 & 199) != 0) {
    if ((bVar2 & 0x80) == 0) {
      uVar5 = (u32)*(u8 *)((s32)puVar15 + 9);
      if ((bVar2 & 4) == 0) {
        if ((bVar2 & 0x40) == 0) {
          if ((uStack00000010 & 3) == 2) {
            uVar5 = *(u8 *)((s32)puVar15 + 5) * uVar5 >> 8;
            uVar7 = (u32)*(u8 *)((s32)puVar15 + 6);
            if (uVar5 <= uVar7) {
              if (uVar7 == 0) goto _081DCFC8;
              uStack00000010 = uStack00000010 - 1;
              *(char *)puVar15 = (char)uStack00000010;
              uVar5 = uVar7;
            }
          }
          else {
            if ((uStack00000010 & 3) == 3) goto _081DCFF8;
          }
        }
        else {
          uVar5 = *(u8 *)((s32)puVar15 + 7) * uVar5 >> 8;
          if (uVar5 <= *(u8 *)(puVar15 + 3)) {
_081DCFC8:
            if (*(u8 *)(puVar15 + 3) == 0) goto _081DCFB0;
            uStack00000010 = uStack00000010 | 4;
            *(char *)puVar15 = (char)uStack00000010;
            uVar5 = (u32)*(u8 *)(puVar15 + 3);
          }
        }
      }
      else {
        bVar2 = *(u8 *)((s32)puVar15 + 0xd);
        iVar6 = bVar2 - 1;
        *(char *)((s32)puVar15 + 0xd) = (char)iVar6;
        if (bVar2 == 0 || iVar6 == 0) goto _081DCFB0;
      }
    }
    else {
      if ((bVar2 & 0x40) != 0) {
_081DCFB0:
        *(undefined *)puVar15 = 0;
        goto _081DD240;
      }
      uStack00000010 = 3;
      *(undefined *)puVar15 = 3;
      puVar15[10] = iVar10 + 0x10 + puVar15[6];
      puVar15[6] = *(s32 *)(iVar10 + 0xc) - puVar15[6];
      uVar5 = 0;
      *(undefined *)((s32)puVar15 + 9) = 0;
      puVar15[7] = 0;
      if ((*(u8 *)(iVar10 + 3) & 0xc0) != 0) {
        uStack00000010 = 0x13;
        *(undefined *)puVar15 = 0x13;
      }
_081DCFF8:
      uVar5 = uVar5 + *(u8 *)(puVar15 + 1);
      if (0xfe < uVar5) {
        uStack00000010 = uStack00000010 - 1;
        *(char *)puVar15 = (char)uStack00000010;
        uVar5 = 0xff;
      }
    }
    *(char *)((s32)puVar15 + 9) = (char)uVar5;
    uVar5 = uVar5 * (*(u8 *)((s32)in_stack_00000018 + 7) + 1) >> 4;
    *(char *)((s32)puVar15 + 10) = (char)(uVar5 * *(u8 *)((s32)puVar15 + 2) >> 8);
    *(char *)((s32)puVar15 + 0xb) = (char)(uVar5 * *(u8 *)((s32)puVar15 + 3) >> 8);
    uStack00000010 = uStack00000010 & 0x10;
    if (uStack00000010 != 0) {
      in_stack_0000000c = (char *)(iVar10 + 0x10 + *(s32 *)(iVar10 + 8));
      uStack00000010 = *(s32 *)(iVar10 + 0xc) - *(s32 *)(iVar10 + 8);
    }
    uVar5 = puVar15[6];
    pcVar11 = (char *)puVar15[10];
    uVar7 = puVar15[7];
    if ((*(u8 *)((s32)puVar15 + 1) & 0x30) == 0) {
      iVar10 = (u32)*(u8 *)((s32)puVar15 + 10) * 0x10000;
      iVar6 = (u32)*(u8 *)((s32)puVar15 + 0xb) * 0x10000;
      uVar19 = uVar5;
      puVar13 = in_stack_00000008;
      uVar20 = unaff_r8;
      if ((*(u8 *)((s32)puVar15 + 1) & 8) == 0) {
        iVar8 = puVar15[8];
        uVar19 = SEXT14(*pcVar11);
        pcVar11 = pcVar11 + 1;
        iVar9 = (s32)*pcVar11 - uVar19;
        do {
          uVar16 = *puVar13;
          uVar18 = puVar13[0x18c];
          uVar17 = uVar5;
          do {
            puVar14 = puVar13;
            iVar21 = uVar19 + ((s32)(uVar7 * iVar9) >> 0x17);
            uVar16 = (iVar10 * iVar21 & 0xff00ffffU) + (uVar16 >> 8 | uVar16 << 0x18);
            uVar18 = (iVar6 * iVar21 & 0xff00ffffU) + (uVar18 >> 8 | uVar18 << 0x18);
            uVar7 = uVar7 + iVar4 * iVar8;
            uVar1 = uVar7 >> 0x17;
            uVar5 = uVar17;
            if (uVar1 != 0) {
              uVar7 = uVar7 & 0xc07fffff;
              uVar5 = uVar17 - uVar1;
              if (uVar5 == 0 || (s32)uVar17 < (s32)uVar1) {
                if (uStack00000010 == 0) {
                  uStack00000010 = 0;
                  goto _081DD174;
                }
                iVar21 = -uVar5;
                while( true ) {
                  bVar23 = SCARRY4(uStack00000010,uVar5);
                  uVar5 = uStack00000010 + uVar5;
                  bVar22 = uVar5 == 0;
                  uVar19 = uStack00000010;
                  pcVar11 = in_stack_0000000c;
                  if (!bVar22 && (s32)uVar5 < 0 == bVar23) break;
                  iVar21 = iVar21 - uStack00000010;
                }
              }
              else {
                iVar21 = uVar1 - 1;
                bVar22 = iVar21 == 0;
                if (bVar22) {
                  uVar19 = uVar19 + iVar9;
                }
              }
              if (!bVar22) {
                pcVar11 = pcVar11 + iVar21;
                uVar19 = SEXT14(*pcVar11);
              }
              pcVar11 = pcVar11 + 1;
              iVar9 = (s32)*pcVar11 - uVar19;
            }
            uVar17 = uVar5;
            puVar13 = puVar14 + 0x10000000;
          } while (puVar14 < &OAM_SIZE_3);
          puVar14[0x1000018c] = uVar18;
          puVar13 = puVar14 + 0x10000001;
          puVar14[0x10000000] = uVar16;
          uVar17 = uVar20 - 4;
          bVar22 = 3 < (s32)uVar20;
          uVar20 = uVar17;
        } while (uVar17 != 0 && bVar22);
        pcVar11 = pcVar11 + -1;
        goto _081DD228;
      }
      do {
        uVar5 = uVar19;
        if (4 < (s32)uVar19) {
          uVar5 = uVar19 - uVar20;
          if (uVar5 != 0 && (s32)uVar20 <= (s32)uVar19) {
            uVar7 = 0;
          }
          if (uVar5 == 0 || (s32)uVar19 < (s32)uVar20) {
            uVar19 = (uVar5 + uVar20) - 4;
            uVar7 = uVar20 - uVar19;
            uVar5 = uVar5 + uVar20 & 3;
            uVar20 = uVar19;
            if (uVar5 == 0) {
              uVar5 = 4;
            }
          }
          do {
            uVar19 = *puVar13;
            uVar17 = puVar13[0x18c];
            pcVar12 = pcVar11;
            do {
              puVar14 = puVar13;
              pcVar11 = pcVar12 + 1;
              uVar19 = (iVar10 * *pcVar12 & 0xff00ffffU) + (uVar19 >> 8 | uVar19 << 0x18);
              uVar17 = (iVar6 * *pcVar12 & 0xff00ffffU) + (uVar17 >> 8 | uVar17 << 0x18);
              pcVar12 = pcVar11;
              puVar13 = puVar14 + 0x10000000;
            } while (puVar14 < &OAM_SIZE_3);
            puVar14[0x1000018c] = uVar17;
            puVar13 = puVar14 + 0x10000001;
            puVar14[0x10000000] = uVar19;
            uVar19 = uVar20 - 4;
            bVar22 = 3 < (s32)uVar20;
            uVar20 = uVar19;
          } while (uVar19 != 0 && bVar22);
          uVar20 = uVar19 + uVar7;
          if (uVar20 == 0) break;
        }
        uVar16 = *puVar13;
        uVar18 = puVar13[0x18c];
        do {
          puVar14 = puVar13;
          uVar16 = (iVar10 * *pcVar11 & 0xff00ffffU) + (uVar16 >> 8 | uVar16 << 0x18);
          uVar18 = (iVar6 * *pcVar11 & 0xff00ffffU) + (uVar18 >> 8 | uVar18 << 0x18);
          uVar5 = uVar5 - 1;
          pcVar11 = pcVar11 + 1;
          if ((uVar5 == 0) &&
             (uVar5 = uStack00000010, pcVar11 = in_stack_0000000c, uStack00000010 == 0))
          goto _081DD174;
          puVar13 = puVar14 + 0x10000000;
        } while (puVar14 < &OAM_SIZE_3);
        puVar14[0x1000018c] = uVar18;
        puVar13 = puVar14 + 0x10000001;
        puVar14[0x10000000] = uVar16;
        uVar17 = uVar20 - 4;
        bVar22 = 3 < (s32)uVar20;
        uVar19 = uVar5;
        uVar20 = uVar17;
      } while (uVar17 != 0 && bVar22);
    }
    else {
      sub_82DF49C();
_081DD228:
      puVar15[7] = uVar7;
    }
    puVar15[6] = uVar5;
    puVar15[10] = pcVar11;
  }
  goto _081DD240;
_081DD174:
  *(char *)puVar15 = (char)uStack00000010;
  uVar5 = (3 - ((u32)puVar14 >> 0x1e)) * 8;
  uVar7 = uVar5 & 0x1f;
  uVar5 = uVar5 & 0x1f;
  ((u32 *)((u32)puVar14 & 0x3fffffff))[0x18c] = uVar18 >> uVar5 | uVar18 << 0x20 - uVar5;
  *(u32 *)((u32)puVar14 & 0x3fffffff) = uVar16 >> uVar7 | uVar16 << 0x20 - uVar7;
_081DD240:
  uVar5 = uStack00000004 - 1;
  if (uVar5 == 0 || (s32)uStack00000004 < 1) goto _081DD24A;
  puVar15 = puVar15 + 0x10;
  goto SoundMainRAM_ChanLoop;
}



void _081DD25E(void)

{
  code *UNRECOVERED_JUMPTABLE;
  
                    // WARNING: Could not recover jumptable at 0x08001f2a. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



void sub_82DF49C(undefined4 param_1,undefined4 param_2,s32 param_3,s32 param_4)

{
  s32 iVar1;
  s32 iVar2;
  u32 uVar3;
  u32 uVar4;
  s32 iVar5;
  undefined4 extraout_r1;
  s32 iVar6;
  s32 extraout_r1_00;
  undefined4 extraout_r1_01;
  s32 extraout_r1_02;
  char *pcVar7;
  u8 *unaff_r4;
  u32 *unaff_r5;
  u32 *puVar8;
  short *psVar9;
  u32 uVar10;
  s32 iVar11;
  u32 uVar12;
  s32 unaff_r8;
  s32 iVar13;
  u32 unaff_r9;
  s32 unaff_r10;
  s32 unaff_r11;
  s32 in_r12;
  s32 iVar14;
  bool bVar15;
  undefined8 uVar16;
  s32 in_stack_00000010;
  
  psVar9 = *(short **)(unaff_r4 + 0x24);
  if ((*unaff_r4 & 0x20) == 0) {
    *unaff_r4 = *unaff_r4 | 0x20;
    if ((unaff_r4[1] & 0x10) != 0) {
      param_4 = (*(s32 *)(psVar9 + 6) + (s32)psVar9 * 2 + 0x20) - param_4;
      *(s32 *)(unaff_r4 + 0x28) = param_4;
    }
    if (*psVar9 != 0) {
      param_4 = (param_4 - (s32)psVar9) + -0x10;
      *(s32 *)(unaff_r4 + 0x28) = param_4;
    }
  }
  iVar1 = unaff_r10 * 0x10000;
  iVar2 = unaff_r11 * 0x10000;
  if ((unaff_r4[1] & 8) == 0) {
    iVar13 = in_r12 * *(s32 *)(unaff_r4 + 0x20);
  }
  else {
    iVar13 = 0x800000;
  }
  if (*psVar9 == 0) {
    if ((unaff_r4[1] & 0x10) != 0) {
      pcVar7 = (char *)(param_4 + -1);
      iVar5 = (s32)*pcVar7;
      iVar6 = *(char *)(param_4 + -2) - iVar5;
      do {
        uVar10 = *unaff_r5;
        uVar12 = unaff_r5[0x18c];
        iVar11 = param_3;
        do {
          puVar8 = unaff_r5;
          iVar14 = iVar5 + ((s32)(unaff_r9 * iVar6) >> 0x17);
          uVar10 = (iVar1 * iVar14 & 0xff00ffffU) + (uVar10 >> 8 | uVar10 << 0x18);
          uVar12 = (iVar2 * iVar14 & 0xff00ffffU) + (uVar12 >> 8 | uVar12 << 0x18);
          unaff_r9 = unaff_r9 + iVar13;
          uVar3 = unaff_r9 >> 0x17;
          param_3 = iVar11;
          if (uVar3 != 0) {
            unaff_r9 = unaff_r9 & 0xc07fffff;
            param_3 = iVar11 - uVar3;
            if (param_3 == 0 || iVar11 < (s32)uVar3) goto _081DD4F4;
            pcVar7 = pcVar7 + -uVar3;
            iVar5 = (s32)*pcVar7;
            iVar6 = pcVar7[-1] - iVar5;
          }
          iVar11 = param_3;
          unaff_r5 = puVar8 + 0x10000000;
        } while (puVar8 < &OAM_SIZE_3);
        puVar8[0x1000018c] = uVar12;
        unaff_r5 = puVar8 + 0x10000001;
        puVar8[0x10000000] = uVar10;
        iVar11 = unaff_r8 + -4;
        bVar15 = 3 < unaff_r8;
        unaff_r8 = iVar11;
      } while (iVar11 != 0 && bVar15);
    }
  }
  else {
    *(undefined4 *)(unaff_r4 + 0x3c) = 0xff000000;
    if ((unaff_r4[1] & 0x10) == 0) {
      sub_82DF758();
      uVar16 = sub_82DF758(extraout_r1);
      iVar5 = (s32)uVar16;
      iVar6 = (s32)((ulonglong)uVar16 >> 0x20) - iVar5;
      do {
        uVar10 = *unaff_r5;
        uVar12 = unaff_r5[0x18c];
        iVar11 = unaff_r8;
        do {
          puVar8 = unaff_r5;
          iVar14 = iVar5 + ((s32)(unaff_r9 * iVar6) >> 0x17);
          uVar10 = (iVar1 * iVar14 & 0xff00ffffU) + (uVar10 >> 8 | uVar10 << 0x18);
          uVar12 = (iVar2 * iVar14 & 0xff00ffffU) + (uVar12 >> 8 | uVar12 << 0x18);
          unaff_r9 = unaff_r9 + iVar13;
          uVar3 = unaff_r9 >> 0x17;
          if (uVar3 != 0) {
            unaff_r9 = unaff_r9 & 0xc07fffff;
            iVar14 = param_3 - uVar3;
            if (iVar14 == 0 || param_3 < (s32)uVar3) {
              if (in_stack_00000010 == 0) {
_081DD4F4:
                *unaff_r4 = 0;
                uVar3 = (3 - ((u32)puVar8 >> 0x1e)) * 8;
                uVar4 = uVar3 & 0x1f;
                uVar3 = uVar3 & 0x1f;
                ((u32 *)((u32)puVar8 & 0x3fffffff))[0x18c] =
                     uVar12 >> uVar3 | uVar12 << 0x20 - uVar3;
                *(u32 *)((u32)puVar8 & 0x3fffffff) = uVar10 >> uVar4 | uVar10 << 0x20 - uVar4;
                return;
              }
              do {
                bVar15 = SCARRY4(iVar14,in_stack_00000010);
                iVar14 = iVar14 + in_stack_00000010;
              } while (iVar14 == 0 || iVar14 < 0 != bVar15);
_081DD358:
              sub_82DF758();
              iVar5 = extraout_r1_00;
              param_3 = iVar14;
            }
            else {
              if (uVar3 != 1) goto _081DD358;
              iVar5 = iVar5 + iVar6;
              param_3 = iVar14;
            }
            uVar16 = sub_82DF758(iVar5);
            iVar5 = (s32)uVar16;
            iVar6 = (s32)((ulonglong)uVar16 >> 0x20) - iVar5;
          }
          unaff_r5 = puVar8 + 0x10000000;
        } while (puVar8 < &OAM_SIZE_3);
        puVar8[0x1000018c] = uVar12;
        unaff_r5 = puVar8 + 0x10000001;
        puVar8[0x10000000] = uVar10;
        unaff_r8 = iVar11 + -4;
      } while (unaff_r8 != 0 && 3 < iVar11);
    }
    else {
      sub_82DF758();
      uVar16 = sub_82DF758(extraout_r1_01);
      iVar5 = (s32)uVar16;
      iVar6 = (s32)((ulonglong)uVar16 >> 0x20) - iVar5;
      do {
        uVar10 = *unaff_r5;
        uVar12 = unaff_r5[0x18c];
        iVar11 = unaff_r8;
        do {
          puVar8 = unaff_r5;
          iVar14 = iVar5 + ((s32)(unaff_r9 * iVar6) >> 0x17);
          uVar10 = (iVar1 * iVar14 & 0xff00ffffU) + (uVar10 >> 8 | uVar10 << 0x18);
          uVar12 = (iVar2 * iVar14 & 0xff00ffffU) + (uVar12 >> 8 | uVar12 << 0x18);
          unaff_r9 = unaff_r9 + iVar13;
          uVar3 = unaff_r9 >> 0x17;
          if (uVar3 != 0) {
            unaff_r9 = unaff_r9 & 0xc07fffff;
            iVar14 = param_3 - uVar3;
            if (iVar14 == 0 || param_3 < (s32)uVar3) goto _081DD4F4;
            if (uVar3 == 1) {
              iVar5 = iVar5 + iVar6;
              param_3 = iVar14;
            }
            else {
              sub_82DF758();
              iVar5 = extraout_r1_02;
              param_3 = iVar14;
            }
            uVar16 = sub_82DF758(iVar5);
            iVar5 = (s32)uVar16;
            iVar6 = (s32)((ulonglong)uVar16 >> 0x20) - iVar5;
          }
          unaff_r5 = puVar8 + 0x10000000;
        } while (puVar8 < &OAM_SIZE_3);
        puVar8[0x1000018c] = uVar12;
        unaff_r5 = puVar8 + 0x10000001;
        puVar8[0x10000000] = uVar10;
        unaff_r8 = iVar11 + -4;
      } while (unaff_r8 != 0 && 3 < iVar11);
    }
  }
  return;
}



undefined8 sub_82DF758(undefined4 param_1,undefined4 param_2,undefined4 param_3,u32 param_4)

{
  u32 uVar1;
  u8 bVar2;
  char cVar3;
  s32 iVar4;
  u8 *pbVar5;
  s32 unaff_r4;
  char *pcVar6;
  char *pcVar7;
  char cVar8;
  
  uVar1 = param_4 >> 6;
  if (uVar1 != *(u32 *)(unaff_r4 + 0x3c)) {
    *(u32 *)(unaff_r4 + 0x3c) = uVar1;
    iVar4 = uVar1 * 0x21 + *(s32 *)(unaff_r4 + 0x24);
    cVar8 = *(char *)(iVar4 + 0x10);
    pcVar6 = &DAT_03000001;
    bVar2 = *(u8 *)(iVar4 + 0x11);
    pbVar5 = (u8 *)(iVar4 + 0x12);
    iVar4 = 0x40;
    gUnknown_03001300 = cVar8;
    while( true ) {
      cVar3 = ""[bVar2 & 0xf];
      pcVar7 = pcVar6 + 1;
      *pcVar6 = cVar8 + cVar3;
      if (iVar4 + -2 == 0 || iVar4 < 2) break;
      bVar2 = *pbVar5;
      cVar8 = cVar8 + cVar3 + ""[bVar2 >> 4];
      pcVar6 = pcVar6 + 2;
      *pcVar7 = cVar8;
      pbVar5 = pbVar5 + 1;
      iVar4 = iVar4 + -2;
    }
  }
  return CONCAT44((s32)(&gUnknown_03001300)[param_4 & 0x3f],param_1);
}



undefined4 * SoundMainBTM(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  return param_1 + 0x10;
}



void RealClearChain(s32 param_1)

{
  s32 iVar1;
  s32 iVar2;
  
  if (*(s32 *)(param_1 + 0x2c) != 0) {
    iVar1 = *(s32 *)(param_1 + 0x34);
    iVar2 = *(s32 *)(param_1 + 0x30);
    if (iVar2 == 0) {
      *(s32 *)(*(s32 *)(param_1 + 0x2c) + 0x20) = iVar1;
    }
    else {
      *(s32 *)(iVar2 + 0x34) = iVar1;
    }
    if (iVar1 != 0) {
      *(s32 *)(iVar1 + 0x30) = iVar2;
    }
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}



undefined4 ply_fine(undefined4 param_1,undefined *param_2)

{
  u8 *pbVar1;
  undefined4 in_lr;
  
  pbVar1 = *(u8 **)(param_2 + 0x20);
  while (pbVar1 != (u8 *)0x0) {
    if ((*pbVar1 & 199) != 0) {
      *pbVar1 = *pbVar1 | 0x40;
    }
    RealClearChain(pbVar1);
    pbVar1 = *(u8 **)(pbVar1 + 0x34);
  }
  *param_2 = 0;
  return in_lr;
}



void ** MPlayJumpTableCopy(void **param_1)

{
  s32 iVar1;
  s32 iVar2;
  void **ppvVar3;
  void *pvVar4;
  undefined8 uVar5;
  
  iVar1 = 0x24;
  ppvVar3 = gMPlayJumpTableTemplate;
  do {
    pvVar4 = *ppvVar3;
    uVar5 = chk_adr_r2(param_1,iVar1);
    iVar2 = (s32)((ulonglong)uVar5 >> 0x20);
    *(void **)uVar5 = pvVar4;
    param_1 = (void **)uVar5 + 1;
    ppvVar3 = ppvVar3 + 1;
    iVar1 = iVar2 + -1;
  } while (iVar1 != 0 && 0 < iVar2);
  return param_1;
}



undefined4 ldrb_r3_r2(undefined4 param_1)

{
  return param_1;
}



undefined4 chk_adr_r2(undefined4 param_1)

{
  return param_1;
}



undefined4 ld_r3_tp_adr_i(undefined4 param_1,s32 param_2)

{
  *(s32 *)(param_2 + 0x40) = *(s32 *)(param_2 + 0x40) + 1;
  return param_1;
}



undefined4 _081DD64A(undefined4 param_1,s32 param_2,s32 param_3)

{
  *(s32 *)(param_2 + 0x40) = param_3 + 1;
  return param_1;
}



undefined4 ply_goto(undefined4 param_1,s32 param_2)

{
  uint3 *puVar1;
  u32 uVar2;
  undefined4 in_lr;
  undefined8 uVar3;
  
  puVar1 = (uint3 *)(*(s32 *)(param_2 + 0x40) + 1);
  uVar2 = (u32)*(u8 *)puVar1;
  uVar3 = ldrb_r3_r2((u32)*puVar1 << 8);
  *(u32 *)((s32)((ulonglong)uVar3 >> 0x20) + 0x40) = (u32)uVar3 | uVar2;
  return in_lr;
}



undefined4 ply_patt(undefined4 param_1,undefined *param_2)

{
  u32 uVar1;
  u8 *pbVar2;
  undefined4 in_lr;
  undefined8 uVar3;
  
  if (2 < (u8)param_2[2]) {
    pbVar2 = *(u8 **)(param_2 + 0x20);
    while (pbVar2 != (u8 *)0x0) {
      if ((*pbVar2 & 199) != 0) {
        *pbVar2 = *pbVar2 | 0x40;
      }
      RealClearChain(pbVar2);
      pbVar2 = *(u8 **)(pbVar2 + 0x34);
    }
    *param_2 = 0;
    return in_lr;
  }
  *(s32 *)(param_2 + (u32)(u8)param_2[2] * 4 + 0x44) = *(s32 *)(param_2 + 0x40) + 4;
  param_2[2] = param_2[2] + '\x01';
  uVar1 = (u32)*(u8 *)(uint3 *)(*(s32 *)(param_2 + 0x40) + 1);
  uVar3 = ldrb_r3_r2((u32)*(uint3 *)(*(s32 *)(param_2 + 0x40) + 1) << 8);
  *(u32 *)((s32)((ulonglong)uVar3 >> 0x20) + 0x40) = (u32)uVar3 | uVar1;
  return in_lr;
}



void ply_pend(undefined4 param_1,s32 param_2)

{
  s32 iVar1;
  
  if (*(u8 *)(param_2 + 2) != 0) {
    iVar1 = *(u8 *)(param_2 + 2) - 1;
    *(char *)(param_2 + 2) = (char)iVar1;
    *(undefined4 *)(param_2 + 0x40) = *(undefined4 *)(param_2 + iVar1 * 4 + 0x44);
  }
  return;
}



undefined4 ply_rept(undefined4 param_1,s32 param_2)

{
  uint3 *puVar1;
  s32 extraout_r1;
  char *pcVar2;
  u32 uVar3;
  u32 uVar4;
  undefined4 in_lr;
  undefined8 uVar5;
  
  pcVar2 = *(char **)(param_2 + 0x40);
  if (*pcVar2 == '\0') {
    *(char **)(param_2 + 0x40) = pcVar2 + 1;
  }
  else {
    uVar4 = *(u8 *)(param_2 + 3) + 1;
    *(char *)(param_2 + 3) = (char)uVar4;
    uVar3 = uVar4;
    ld_r3_tp_adr_i();
    param_2 = extraout_r1;
    if (uVar4 <= uVar3) {
      *(undefined *)(extraout_r1 + 3) = 0;
      *(char **)(extraout_r1 + 0x40) = pcVar2 + 5;
      return in_lr;
    }
  }
  puVar1 = (uint3 *)(*(s32 *)(param_2 + 0x40) + 1);
  uVar3 = (u32)*(u8 *)puVar1;
  uVar5 = ldrb_r3_r2((u32)*puVar1 << 8);
  *(u32 *)((s32)((ulonglong)uVar5 >> 0x20) + 0x40) = (u32)uVar5 | uVar3;
  return in_lr;
}



void ply_prio(void)

{
  s32 extraout_r1;
  undefined in_r3;
  
  ld_r3_tp_adr_i();
  *(undefined *)(extraout_r1 + 0x1d) = in_r3;
  return;
}



void ply_tempo(void)

{
  s32 iVar1;
  s32 in_r3;
  
  iVar1 = ld_r3_tp_adr_i();
  *(short *)(iVar1 + 0x1c) = (short)(in_r3 * 2);
  *(short *)(iVar1 + 0x20) = (short)((u32)*(ushort *)(iVar1 + 0x1e) * in_r3 * 2 >> 8);
  return;
}



void ply_keysh(void)

{
  u8 *extraout_r1;
  u8 in_r3;
  
  ld_r3_tp_adr_i();
  extraout_r1[10] = in_r3;
  *extraout_r1 = *extraout_r1 | 0xc;
  return;
}



void ply_voice(s32 param_1,s32 param_2)

{
  u8 bVar1;
  s32 extraout_r1;
  s32 extraout_r1_00;
  s32 extraout_r1_01;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  bVar1 = **(u8 **)(param_2 + 0x40);
  *(u8 **)(param_2 + 0x40) = *(u8 **)(param_2 + 0x40) + 1;
  puVar2 = (undefined4 *)((u32)bVar1 * 0xc + *(s32 *)(param_1 + 0x30));
  uVar3 = *puVar2;
  chk_adr_r2();
  *(undefined4 *)(extraout_r1 + 0x24) = uVar3;
  uVar3 = puVar2[1];
  chk_adr_r2();
  *(undefined4 *)(extraout_r1_00 + 0x28) = uVar3;
  uVar3 = puVar2[2];
  chk_adr_r2();
  *(undefined4 *)(extraout_r1_01 + 0x2c) = uVar3;
  return;
}



void ply_vol(void)

{
  u8 *extraout_r1;
  u8 in_r3;
  
  ld_r3_tp_adr_i();
  extraout_r1[0x12] = in_r3;
  *extraout_r1 = *extraout_r1 | 3;
  return;
}



void ply_pan(void)

{
  u8 *extraout_r1;
  char in_r3;
  
  ld_r3_tp_adr_i();
  extraout_r1[0x14] = in_r3 - 0x40;
  *extraout_r1 = *extraout_r1 | 3;
  return;
}



void ply_bend(void)

{
  u8 *extraout_r1;
  char in_r3;
  
  ld_r3_tp_adr_i();
  extraout_r1[0xe] = in_r3 - 0x40;
  *extraout_r1 = *extraout_r1 | 0xc;
  return;
}



void ply_bendr(void)

{
  u8 *extraout_r1;
  u8 in_r3;
  
  ld_r3_tp_adr_i();
  extraout_r1[0xf] = in_r3;
  *extraout_r1 = *extraout_r1 | 0xc;
  return;
}



void ply_lfodl(void)

{
  s32 extraout_r1;
  undefined in_r3;
  
  ld_r3_tp_adr_i();
  *(undefined *)(extraout_r1 + 0x1b) = in_r3;
  return;
}



void ply_modt(void)

{
  u8 *extraout_r1;
  u32 in_r3;
  
  ld_r3_tp_adr_i();
  if (extraout_r1[0x18] != in_r3) {
    extraout_r1[0x18] = (u8)in_r3;
    *extraout_r1 = *extraout_r1 | 0xf;
  }
  return;
}



void ply_tune(void)

{
  u8 *extraout_r1;
  char in_r3;
  
  ld_r3_tp_adr_i();
  extraout_r1[0xc] = in_r3 - 0x40;
  *extraout_r1 = *extraout_r1 | 0xc;
  return;
}



void ply_port(undefined4 param_1,s32 param_2)

{
  undefined *puVar1;
  u32 uVar2;
  
  uVar2 = (u32)**(u8 **)(param_2 + 0x40);
  puVar1 = (undefined *)_081DD64A(&REG_SOUND1CNT + uVar2,param_2,*(u8 **)(param_2 + 0x40) + 1);
  *puVar1 = (char)uVar2;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void m4aSoundVSync(void)

{
  u8 bVar1;
  s32 *piVar2;
  s32 iVar3;
  
  piVar2 = SOUND_INFO_PTR;
  if ((*SOUND_INFO_PTR + 0x978c92adU < 2) &&
     (bVar1 = *(u8 *)(SOUND_INFO_PTR + 1), iVar3 = bVar1 - 1,
     *(char *)(SOUND_INFO_PTR + 1) = (char)iVar3, iVar3 == 0 || bVar1 == 0)) {
    *(undefined *)(piVar2 + 1) = *(undefined *)((s32)piVar2 + 0xb);
    if ((_REG_DMA1CNT & 0x2000000) != 0) {
      _REG_DMA1CNT = 0x84400004;
    }
    if ((_REG_DMA2CNT & 0x2000000) != 0) {
      _REG_DMA2CNT = 0x84400004;
    }
    _REG_DMA1CNT = CONCAT22(0xb600,(short)_REG_DMA1CNT);
    _REG_DMA2CNT = CONCAT22(0xb600,(short)_REG_DMA2CNT);
  }
  return;
}



undefined8 MPlayMain(MusicPlayerInfo *param_1,undefined4 param_2)

{
  s32 iVar1;
  u32 uVar2;
  s32 iVar3;
  u32 uVar4;
  u8 bVar5;
  u8 *pbVar6;
  u32 uVar7;
  u32 uVar8;
  u32 uVar9;
  SoundChannel *pSVar10;
  MusicPlayerTrack *pMVar11;
  undefined4 unaff_r8;
  undefined4 unaff_r9;
  bool bVar12;
  
  if ((undefined *)param_1->ident != &ID_NUMBER) {
    return CONCAT44(param_2,param_1);
  }
  param_1->ident = 0x68736d54;
  if (param_1->MPlayMainNext != (MPlayMainFunc *)0x0) {
    call_r3(param_1->musicPlayerNext);
  }
  iVar1 = SOUND_INFO_PTR;
  if (((s32)param_1->status < 0) || (FadeOutBody(param_1), (s32)param_1->status < 0)) {
_081DDA6C:
    param_1->ident = (u32)&ID_NUMBER;
    return CONCAT44(unaff_r9,unaff_r8);
  }
  uVar2 = (u32)param_1->tempoC + (u32)param_1->tempoI;
_081DD9BC:
  param_1->tempoC = (u16)uVar2;
  if (0x95 < uVar2) {
    pMVar11 = param_1->tracks;
    uVar8 = 1;
    uVar9 = 0;
    uVar2 = (u32)param_1->trackCount;
    do {
      if ((pMVar11->flags & 0x80) != 0) {
        uVar9 = uVar9 | uVar8;
        pSVar10 = pMVar11->chan;
        while (pSVar10 != (SoundChannel *)0x0) {
          if ((pSVar10->statusFlags & 199) == 0) {
            ClearChain(pSVar10);
          }
          else {
            if ((pSVar10->gateTime != 0) &&
               (iVar3 = pSVar10->gateTime - 1, pSVar10->gateTime = (u8)iVar3, iVar3 == 0)) {
              pSVar10->statusFlags = pSVar10->statusFlags | 0x40;
            }
          }
          pSVar10 = (SoundChannel *)pSVar10->nextChannelPointer;
        }
        if ((pMVar11->flags & 0x40) != 0) {
          Clear64byte(pMVar11);
          pMVar11->flags = -0x80;
          pMVar11->bendRange = '\x02';
          pMVar11->volX = '@';
          pMVar11->lfoSpeed = '\x16';
          (pMVar11->tone).type = '\x01';
        }
        do {
          while( true ) {
            while( true ) {
              if (pMVar11->wait != '\0') {
                pMVar11->wait = pMVar11->wait + -1;
                if ((pMVar11->lfoSpeed != 0) && (pMVar11->mod != '\0')) {
                  if (pMVar11->lfoDelayC == '\0') {
                    iVar3 = (u32)pMVar11->lfoSpeedC + (u32)pMVar11->lfoSpeed;
                    pMVar11->lfoSpeedC = (u8)iVar3;
                    if ((iVar3 + -0x40) * 0x1000000 < 0) {
                      iVar3 = (s32)(char)(u8)iVar3;
                    }
                    else {
                      iVar3 = 0x80 - iVar3;
                    }
                    uVar7 = (s32)(iVar3 * (u32)pMVar11->mod) >> 6;
                    if ((((u8)pMVar11->modM ^ uVar7) & 0xff) != 0) {
                      pMVar11->modM = (s8)uVar7;
                      if (pMVar11->modT == '\0') {
                        bVar5 = 0xc;
                      }
                      else {
                        bVar5 = 3;
                      }
                      pMVar11->flags = pMVar11->flags | bVar5;
                    }
                  }
                  else {
                    pMVar11->lfoDelayC = pMVar11->lfoDelayC + -1;
                  }
                }
                goto _081DD998;
              }
              pbVar6 = pMVar11->cmdPtr;
              bVar5 = *pbVar6;
              uVar7 = (u32)bVar5;
              if (uVar7 < 0x80) {
                uVar7 = (u32)pMVar11->runningStatus;
              }
              else {
                pbVar6 = pbVar6 + 1;
                pMVar11->cmdPtr = pbVar6;
                if (0xbc < uVar7) {
                  pMVar11->runningStatus = bVar5;
                }
              }
              if (uVar7 < 0xcf) break;
              call_r3(uVar7 - 0xcf,param_1,pMVar11,*(undefined4 *)(iVar1 + 0x38));
            }
            if (0xb0 < uVar7) break;
            pMVar11->wait = (&UNK_080031f0)[uVar7];
          }
          param_1->cmd = (u8)(uVar7 - 0xb1);
          call_r3(param_1,pMVar11,pbVar6,
                  *(undefined4 *)(*(s32 *)(iVar1 + 0x34) + (uVar7 - 0xb1) * 4));
        } while (pMVar11->flags != '\0');
      }
_081DD998:
      if (uVar2 - 1 == 0 || (s32)uVar2 < 1) goto _081DD9A4;
      pMVar11 = pMVar11 + 1;
      uVar8 = uVar8 << 1;
      uVar2 = uVar2 - 1;
    } while( true );
  }
  pMVar11 = param_1->tracks;
  uVar2 = (u32)param_1->trackCount;
  do {
    if (((pMVar11->flags & 0x80) != 0) && ((pMVar11->flags & 0xf) != 0)) {
      TrkVolPitSet(param_1,pMVar11);
      pSVar10 = pMVar11->chan;
      while (pSVar10 != (SoundChannel *)0x0) {
        if ((pSVar10->statusFlags & 199) == 0) {
          ClearChain(pSVar10);
        }
        else {
          bVar5 = pSVar10->type;
          if (((pMVar11->flags & 3) != 0) && (ChnVolSetAsm(), (bVar5 & 7) != 0)) {
            *(u8 *)((s32)&pSVar10->fw + 1) = *(u8 *)((s32)&pSVar10->fw + 1) | 1;
          }
          if ((pMVar11->flags & 0xc) != 0) {
            iVar3 = (u32)pSVar10->key + (s32)(char)pMVar11->keyM;
            if (iVar3 < 0) {
              iVar3 = 0;
            }
            if ((bVar5 & 7) == 0) {
              uVar4 = MidiKeyToFreq(pSVar10->wav,(u8)iVar3,pMVar11->pitM);
              pSVar10->frequency = uVar4;
            }
            else {
              uVar4 = call_r3(bVar5 & 7,iVar3,pMVar11->pitM,*(undefined4 *)(iVar1 + 0x30));
              pSVar10->frequency = uVar4;
              *(u8 *)((s32)&pSVar10->fw + 1) = *(u8 *)((s32)&pSVar10->fw + 1) | 2;
            }
          }
        }
        pSVar10 = (SoundChannel *)pSVar10->nextChannelPointer;
      }
      pMVar11->flags = pMVar11->flags & 0xf0;
    }
  } while ((uVar2 - 1 != 0 && 0 < (s32)uVar2) &&
          (bVar12 = SCARRY4((s32)pMVar11,0x50), pMVar11 = pMVar11 + 1, uVar2 = uVar2 - 1,
          pMVar11 != (MusicPlayerTrack *)0x0 && (s32)pMVar11 < 0 == bVar12));
  goto _081DDA6C;
_081DD9A4:
  param_1->clock = param_1->clock + 1;
  if (uVar9 == 0) {
    param_1->status = 0x80000000;
    goto _081DDA6C;
  }
  param_1->status = uVar9;
  uVar2 = param_1->tempoC - 0x96;
  goto _081DD9BC;
}



void call_r3(void)

{
  return;
}



undefined4 TrackStop(undefined4 param_1,u8 *param_2)

{
  char *pcVar1;
  undefined4 in_lr;
  
  if ((*param_2 & 0x80) != 0) {
    pcVar1 = *(char **)(param_2 + 0x20);
    while (pcVar1 != (char *)0x0) {
      if (*pcVar1 != '\0') {
        if ((pcVar1[1] & 7U) != 0) {
          call_r3();
        }
        *pcVar1 = '\0';
      }
      *(undefined4 *)(pcVar1 + 0x2c) = 0;
      pcVar1 = *(char **)(pcVar1 + 0x34);
    }
    *(undefined4 *)(param_2 + 0x20) = 0;
  }
  return in_lr;
}

