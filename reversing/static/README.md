# static

バイナリを注意深く見てみよう

ビルド環境 ubuntu 18.04 gcc latest

ヒント：まずは表層解析をして気になる文字列が見つかれば調べてみましょう

## フラグ

`FLAG{rc4_4nd_3tatic_1ink_4nd_s7ripp3d_p1us_upx_pack3d}`

## 解法

まず `strings` コマンドで表層解析をします。

```
$ strings static
...
$Info: This file is packed with the UPX executable packer http://upx.sf.net $
$Id: UPX 3.96 Copyright (C) 1996-2020 the UPX Team. All Rights Reserved. $
...
```

するとこのバイナリは[UPX](https://github.com/upx/upx) という Packer でパックされていることがわかります。

Executable Packer とは実行ファイルを実行可能なままで圧縮する技術で、ファイル容量の削減であったり、難読化を目的として使用されることもあります。

> 難しめの CTF 大会の Reversing 問題では作問者オリジナルの Packer を使用した問題が出題されることがあります。

### UPX unpack

このファイルに使用されている[UPX](https://github.com/upx/upx) は pack 及び unpack の機能が備わっているので

<https://github.com/upx/upx/releases/>

こちらのページから UPX の実行ファイルを落としてきて、以下のコマンドで unpack することで元のファイルへ復元できます。

```
$ upx -d static
```

### 静的リンクされた関数の特定

unpack したバイナリを `file` コマンドで調べてみると

```
$ file static
static: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), statically linked, for GNU/Linux 3.2.0, BuildID[sha1]=b511e4b318031c1be104cd6b3c0724e70d63e1ec, stripped
```

static link + stripped なバイナリのようです。

static link とは一般的に Linux においては共有ライブラリ glibc を実行ファイルに含めることを表しており、また strip とはシンボル情報を削除することを意味しています。

この 2 つによってデバッグ時に「ユーザが定義した関数名」と「共有ライブラリの関数名」がわからなくなります。Ghidra で解析しようとしても Symbol Tree の Functions は「FUN_004012a0」のように名前がわからなくなっていてどのような動作をするのか解析するのが困難です。

なので glibc の関数を Ghidra 上で sig-database から特定してみます。

[Reversing Statically-Linked Binaries with Function Signatures - bin 0x2D](https://www.youtube.com/watch?v=CgGha_zLqlo)

ApplySig.py を Script Manager から実行して `sig-database/ubuntu/libc6/18.04 (bionic)/amd64/libc6_2.27-3ubuntu1_amd64.sig`を適用すると`[ 685 / 1346 ]` 個の関数名を特定でき、Decompiler Window でもいくつかの関数名が表示されるようになりました。

### コードを読む

entry 関数を見ると「FUN_00400f23」がメイン関数である事がわかります。

```cpp
void entry(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 in_stack_00000000;

  FUN_004012a0(FUN_00400f23,in_stack_00000000,&stack0x00000008,__libc_csu_fini,FUN_00401da0,param_3)
  ;
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}
```

> 何度もバイナリ解析をしていると大体どこでどんな関数が呼ばれているか分かってきます。ここでは「FUN_004012a0」が `__libc_start_main` で「FUN_00400f23」がメイン関数になると経験でわかります

main 関数では「FUN_00400c4e」がフラグ判定を行っています。

```cpp
ulong FUN_00400f23(void)

{
  int iVar1;
  long in_FS_OFFSET;
  undefined local_78 [48];
  undefined local_48 [5];
  undefined auStack67 [51];
  long local_10;

  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  __printf("input flag : ");
  __isoc99_scanf(&DAT_004b06a4,local_48);
  iVar1 = FUN_00400bb7(local_48);
  if (iVar1 != 0) {
    FUN_00400b9d();
  }
  iVar1 = FUN_00400be3(local_48);
  if (iVar1 != 0) {
    FUN_00400b9d();
  }
  iVar1 = FUN_00400c19(local_48);
  if (iVar1 != 0) {
    FUN_00400b9d();
  }
  thunk_FUN_0040050e(local_78,auStack67,0x30,local_78);
  iVar1 = FUN_00400c4e(local_78);
  if (iVar1 != 0) {
    _IO_puts("Incorrect");
  }
  else {
    __printf("Correct! Flag is %s\n",local_48);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (ulong)(iVar1 == 0);
}
```

「FUN_00400c4e」は `__random(0x12bb0b7)` つまり `srand(19640503);` で初期化した `rand()` を 0x30 個キーとして XOR する RC4 風チェック関数のようです。

```cpp
ulong FUN_00400c4e(long param_1)

{
  byte bVar1;
  uint uVar2;
  long in_FS_OFFSET;
  int local_1a0;
  int local_19c;
  uint local_198 [48];
  uint auStack216 [50];
  long local_10;

  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = 0;
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
  __random(0x12bb0b7);
  local_1a0 = 0;
  while (local_1a0 < 0x30) {
    uVar2 = rand();
    auStack216[local_1a0] = uVar2;
    local_1a0 = local_1a0 + 1;
  }
  local_19c = 0;
  while (local_19c < 0x30) {
    if (((uint)*(byte *)(param_1 + local_19c) ^ auStack216[local_19c]) != local_198[local_19c]) {
      bVar1 = 1;
    }
    local_19c = local_19c + 1;
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (ulong)bVar1;
}
```

今回は `rand` 関数を使っているので C 言語で FLAG を特定するコードを書きます。

```cpp
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
```

```
$ gcc solve.c ; ./a.out
Flag is FLAG{rc4_4nd_3tatic_1ink_4nd_s7ripp3d_p1us_upx_pack3d}
```
