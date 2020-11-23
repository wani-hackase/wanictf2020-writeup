#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int local_198[48];
  local_198[0] = 0x63c1d9cb;
  local_198[1] = 0x383f1bb2;
  local_198[2] = 0x4107dd90;
  local_198[3] = 0x34841fb5;
  local_198[4] = 0x3ebdf538;
  local_198[5] = 0x31565585;
  local_198[6] = 0x4def055e;
  local_198[7] = 0x1bfdeb79;
  local_198[8] = 0x24118ff9;
  local_198[9] = 0x272298e8;
  local_198[10] = 0x7abcb5e2;
  local_198[11] = 0x9466371;
  local_198[12] = 0x7799b008;
  local_198[13] = 0x172289a0;
  local_198[14] = 0x401a25a3;
  local_198[15] = 0x39ce61b8;
  local_198[16] = 0x56ec69a8;
  local_198[17] = 0x106f1fbc;
  local_198[18] = 0x77fc40dd;
  local_198[19] = 0x4828ae9d;
  local_198[20] = 0x2252bab7;
  local_198[21] = 0x45935dcc;
  local_198[22] = 0x7565bd9a;
  local_198[23] = 0x5ae240c0;
  local_198[24] = 0x20edd601;
  local_198[25] = 0x47362402;
  local_198[26] = 0xb61fcc7;
  local_198[27] = 0x7c7607b7;
  local_198[28] = 0x6cf7737d;
  local_198[29] = 0x522262fa;
  local_198[30] = 0x5ee1319b;
  local_198[31] = 0x50b94ca2;
  local_198[32] = 0xa617e04;
  local_198[33] = 0x1fe90f3c;
  local_198[34] = 0x53d6c81;
  local_198[35] = 0x491f731d;
  local_198[36] = 0x513f6544;
  local_198[37] = 0x532c71b5;
  local_198[38] = 0x651d5efb;
  local_198[39] = 0x7550f572;
  local_198[40] = 0x7a4f0aff;
  local_198[41] = 0x5fda144e;
  local_198[42] = 0x7e975877;
  local_198[43] = 0x71e8ba89;
  local_198[44] = 0x76fc9db7;
  local_198[45] = 0x3eb17e6f;
  local_198[46] = 0x2bb71c42;
  local_198[47] = 0x4de907f2;

  char flag[49];
  srand(19640503);
  for (int i = 0; i < 48; i++)
  {
    flag[i] = local_198[i] ^ rand();
  }
  flag[48] = 0;
  printf("Flag is FLAG{%s}\n", flag);
  return 0;
}
