#include <stdio.h>
#include <string.h>

int check_0(const unsigned char *flag)
{
  char key[37] = "1547555923155852010426444205662718566";
  char res[37] = "YTQZTAZ[@R_V]QTmBTC@SU_kU@YFBYUR_]A_U";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_1(const unsigned char *flag)
{
  char key[37] = "9956685905780470658139164491341218634";
  char res[37] = "PWQ_EKZUFTUTUZRCEjRPD[CSU_P_TkW^PV]VF";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_2(const unsigned char *flag)
{
  char key[37] = "9629683025019206458785880652901551293";
  char res[37] = "I^KJY_RCFGYBTmSWVYQY_jP]DSG]]QRAL]]L@";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_3(const unsigned char *flag)
{
  char key[37] = "0873005709115565808026815869435903238";
  char res[37] = "CYCZC@TDCP^_jRSZLU[D]ZWVLgZLLFYPQ][G]";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_4(const unsigned char *flag)
{
  char key[37] = "4448235012181623401466311495792630694";
  char res[37] = "W[Z[ZJYYWWCWDEmQQ^K[GCZ_^LXY^WWi_USRM";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_5(const unsigned char *flag)
{
  char key[37] = "6988051115511856497732968456020876239";
  char res[37] = "UQWTUQ^RYZYXEPZB[TNhC@VQJUXiV@_OVDV_@";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_6(const unsigned char *flag)
{
  char key[37] = "4432001287038078835611419396562864941";
  char res[37] = "ZQF@_@]SKZYPgSXV_VTZPS]]PG@iYO]USFVAB";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_7(const unsigned char *flag)
{
  char key[37] = "6722845425837765752759180182628632051";
  char res[37] = "T[]AK[XMmFM_G_YG^V[YZUTQSnV]XQJSRFYCT";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_8(const unsigned char *flag)
{
  char key[37] = "5421656359639102992467788142374055195";
  char res[37] = "TW[U_S_PjT_W]]UAIU[@BREgJTAFZ[]JTAXV[";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_9(const unsigned char *flag)
{
  char key[37] = "4435192147821594612257024117237077247";
  char res[37] = "_U_PX]]BWXH[RTUkWA]F@E]WFXRhA]V[R@[GR";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_10(const unsigned char *flag)
{
  char key[37] = "6386065848163684127653481945456442174";
  char res[37] = "_W]XD_AAkQ_BVDJQAW[ZP]@gRVA[@PD@]WCTQ";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_11(const unsigned char *flag)
{
  char key[37] = "9119033221145465710238849190326316957";
  char res[37] = "K^^JUEV^FXPZj]DC^_WW@IMQfPWY@][J^RV@D";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_12(const unsigned char *flag)
{
  char key[37] = "7448208968332080869112832541586732886";
  char res[37] = "GFU]Q_J]_YlPWB]RJYIPC[]GSYkP[L^EJ^]VS";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_13(const unsigned char *flag)
{
  char key[37] = "7631491152978154664681564351104854247";
  char res[37] = "S_WnMVDnGWX[THjW^SW]gE]SkAPEDBZgCU^AR";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 1;
    }
  }
  return 2;
}
int check_14(const unsigned char *flag)
{
  char key[37] = "2762300137072970027179285555771840927";
  char res[37] = "[T^F[I_SRCBVQQ^Q^mZPTX@WZ[jPDXAPUWPAZ";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_15(const unsigned char *flag)
{
  char key[37] = "4891687154756648453430131849054966479";
  char res[37] = "GM[TZWYVT@RjFWFWYZ_[TYPl[YWX]TFXZUMXW";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_16(const unsigned char *flag)
{
  char key[37] = "5639083857567176576598584086930304062";
  char res[37] = "VDRWYW_WR^VW[]Ni[RYEUYAWZYK[fGQDTQBSV";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_17(const unsigned char *flag)
{
  char key[37] = "0115028725995430452014430727586319052";
  char res[37] = "RXEAU@PRSQfXA@RYZTPY]]@JoZ[DW]PZEMY[U";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_18(const unsigned char *flag)
{
  char key[37] = "6023476250489460175259978042377211048";
  char res[37] = "ZQAZUYBZZEGgPZBUCDAWGPU^LIkBGRE]ATWAU";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}
int check_19(const unsigned char *flag)
{
  char key[37] = "0028706797915793420205181509889562483";
  char res[37] = "_BUYY_XXT^ZnZZWZW@UVEYXLHj@XL]UY_T[J^";
  for (int j = 0; j < 37; j++)
  {
    if ((key[j] ^ flag[j]) != res[j])
    {
      return 0;
    }
  }
  return 1;
}


int check(const int i, const unsigned char *flag)
{
  int res;
  switch (i)
  {
  case 0:
    res = check_0(flag);
    return res;
  case 1:
    res = check_1(flag);
    return res;
  case 2:
    res = check_2(flag);
    return res;
  case 3:
    res = check_3(flag);
    return res;
  case 4:
    res = check_4(flag);
    return res;
  case 5:
    res = check_5(flag);
    return res;
  case 6:
    res = check_6(flag);
    return res;
  case 7:
    res = check_7(flag);
    return res;
  case 8:
    res = check_8(flag);
    return res;
  case 9:
    res = check_9(flag);
    return res;
  case 10:
    res = check_10(flag);
    return res;
  case 11:
    res = check_11(flag);
    return res;
  case 12:
    res = check_12(flag);
    return res;
  case 13:
    res = check_13(flag);
    return res;
  case 14:
    res = check_14(flag);
    return res;
  case 15:
    res = check_15(flag);
    return res;
  case 16:
    res = check_16(flag);
    return res;
  case 17:
    res = check_17(flag);
    return res;
  case 18:
    res = check_18(flag);
    return res;
  case 19:
    res = check_19(flag);
    return res;

  }
}

int main(void)
{
  char input[0x2b];
  char flag[0x25];
  int result;
  printf("input flag : ");
  scanf("%s", input);

  if (strlen(input) != 0x2b || strncmp(input, "FLAG{", 5) != 0 || strcmp(&input[0x2a], "}") != 0)
  {
    puts("Incorrect");
    return 1;
  }
  strncpy(flag, input + 5, 0x25);
  for (int i = 0; i < 20; i++)
  {
    result = check(i, flag);
    if (result == 0)
    {
      continue;
    }
    if (result == 1)
    {
      puts("Incorrect");
      return 1;
    }
    if (result == 2)
    {
      printf("Correct! Flag is %s\n", input);
      return 0;
    }
  }
  return 0;
}
