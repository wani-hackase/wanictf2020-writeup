# simple

「strings」問題は表層解析でフラグを見つけることができましたが、この問題では同じようにフラグは見つからないようです。

次の手法は「動的解析」と「静的解析」です。

Linux 実行ファイルの解析において動的解析の代表的なツールが「GDB」、静的解析の代表的なツールが「Ghidra」です。

それぞれ入門記事が多く公開されていますのでぜひ動的解析と静的解析にチャレンジしてみてください!

## フラグ

`FLAG{5imp1e_Revers1ng_4rray_5trings}`
## 解法

`strings` 問題のように `strings` コマンドを実行してみますが、フラグらしき文字列はありません。

```
$ strings simple
/lib64/ld-linux-x86-64.so.2
libc.so.6
__isoc99_scanf
puts
printf
strlen
__cxa_finalize
__libc_start_main
GLIBC_2.7
GLIBC_2.2.5
_ITM_deregisterTMCloneTable
__gmon_start__
_ITM_registerTMCloneTable
=i
5b
AWAVI
AUATL
[]A\A]A^A_
input flag :
incorrect
Incorrect
Correct! Flag is %s
;*3$"
GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
...
```

なので「動的解析」や「静的解析」を行っていきます。

### GDB を使って解く

GDB は apt 経由でインストールできます。また GDB をカラフルにしたり、便利なコマンドを追加できるプラグイン [peda](https://github.com/longld/peda) を導入しています。

> 自分は peda, pwndbg, gef をまとめて導入できる以下のスクリプトを使ってインストールしています。
>
> [apogiatzis/gdb-peda-pwndbg-gef](https://github.com/apogiatzis/gdb-peda-pwndbg-gef)

まずはバイナリを読み込みます

```
$ gdb-peda simple
Reading symbols from simple...(no debugging symbols found)...done.
```

関数一覧を表示

```
gdb-peda$ info function
All defined functions:

Non-debugging symbols:
0x00000000000005b8  _init
0x00000000000005e0  puts@plt
0x00000000000005f0  strlen@plt
0x0000000000000600  printf@plt
0x0000000000000610  __isoc99_scanf@plt
0x0000000000000620  __cxa_finalize@plt
0x0000000000000630  _start
0x0000000000000660  deregister_tm_clones
0x00000000000006a0  register_tm_clones
0x00000000000006f0  __do_global_dtors_aux
0x0000000000000730  frame_dummy
0x000000000000073a  main
0x0000000000000890  __libc_csu_init
0x0000000000000900  __libc_csu_fini
0x0000000000000904  _fini
```

main 関数を逆アセンブル

```
gdb-peda$ disas main
Dump of assembler code for function main:
   0x000000000000073a <+0>:	push   rbp
   0x000000000000073b <+1>:	mov    rbp,rsp
   0x000000000000073e <+4>:	sub    rsp,0x70
   0x0000000000000742 <+8>:	lea    rdi,[rip+0x1cb]        # 0x914
   0x0000000000000749 <+15>:	mov    eax,0x0
   0x000000000000074e <+20>:	call   0x600 <printf@plt>
   0x0000000000000753 <+25>:	lea    rax,[rbp-0x40]
   0x0000000000000757 <+29>:	mov    rsi,rax
   0x000000000000075a <+32>:	lea    rdi,[rip+0x1c1]        # 0x922
   0x0000000000000761 <+39>:	mov    eax,0x0
   0x0000000000000766 <+44>:	call   0x610 <__isoc99_scanf@plt>
   0x000000000000076b <+49>:	lea    rax,[rbp-0x40]
   0x000000000000076f <+53>:	mov    rdi,rax
   0x0000000000000772 <+56>:	call   0x5f0 <strlen@plt>
   0x0000000000000777 <+61>:	cmp    rax,0x24
   0x000000000000077b <+65>:	je     0x793 <main+89>
   0x000000000000077d <+67>:	lea    rdi,[rip+0x1a1]        # 0x925
   0x0000000000000784 <+74>:	call   0x5e0 <puts@plt>
   0x0000000000000789 <+79>:	mov    eax,0x1
   0x000000000000078e <+84>:	jmp    0x880 <main+326>
   0x0000000000000793 <+89>:	mov    BYTE PTR [rbp-0x70],0x46
   0x0000000000000797 <+93>:	mov    BYTE PTR [rbp-0x6f],0x4c
   0x000000000000079b <+97>:	mov    BYTE PTR [rbp-0x6e],0x41
   0x000000000000079f <+101>:	mov    BYTE PTR [rbp-0x6d],0x47
   0x00000000000007a3 <+105>:	mov    BYTE PTR [rbp-0x6c],0x7b
   0x00000000000007a7 <+109>:	mov    BYTE PTR [rbp-0x6b],0x35
   0x00000000000007ab <+113>:	mov    BYTE PTR [rbp-0x6a],0x69
   0x00000000000007af <+117>:	mov    BYTE PTR [rbp-0x69],0x6d
   0x00000000000007b3 <+121>:	mov    BYTE PTR [rbp-0x68],0x70
   0x00000000000007b7 <+125>:	mov    BYTE PTR [rbp-0x67],0x31
   0x00000000000007bb <+129>:	mov    BYTE PTR [rbp-0x66],0x65
   0x00000000000007bf <+133>:	mov    BYTE PTR [rbp-0x65],0x5f
   0x00000000000007c3 <+137>:	mov    BYTE PTR [rbp-0x64],0x52
   0x00000000000007c7 <+141>:	mov    BYTE PTR [rbp-0x63],0x65
   0x00000000000007cb <+145>:	mov    BYTE PTR [rbp-0x62],0x76
   0x00000000000007cf <+149>:	mov    BYTE PTR [rbp-0x61],0x65
   0x00000000000007d3 <+153>:	mov    BYTE PTR [rbp-0x60],0x72
   0x00000000000007d7 <+157>:	mov    BYTE PTR [rbp-0x5f],0x73
   0x00000000000007db <+161>:	mov    BYTE PTR [rbp-0x5e],0x31
   0x00000000000007df <+165>:	mov    BYTE PTR [rbp-0x5d],0x6e
   0x00000000000007e3 <+169>:	mov    BYTE PTR [rbp-0x5c],0x67
   0x00000000000007e7 <+173>:	mov    BYTE PTR [rbp-0x5b],0x5f
   0x00000000000007eb <+177>:	mov    BYTE PTR [rbp-0x5a],0x34
   0x00000000000007ef <+181>:	mov    BYTE PTR [rbp-0x59],0x72
   0x00000000000007f3 <+185>:	mov    BYTE PTR [rbp-0x58],0x72
   0x00000000000007f7 <+189>:	mov    BYTE PTR [rbp-0x57],0x61
   0x00000000000007fb <+193>:	mov    BYTE PTR [rbp-0x56],0x79
   0x00000000000007ff <+197>:	mov    BYTE PTR [rbp-0x55],0x5f
   0x0000000000000803 <+201>:	mov    BYTE PTR [rbp-0x54],0x35
   0x0000000000000807 <+205>:	mov    BYTE PTR [rbp-0x53],0x74
   0x000000000000080b <+209>:	mov    BYTE PTR [rbp-0x52],0x72
   0x000000000000080f <+213>:	mov    BYTE PTR [rbp-0x51],0x69
   0x0000000000000813 <+217>:	mov    BYTE PTR [rbp-0x50],0x6e
   0x0000000000000817 <+221>:	mov    BYTE PTR [rbp-0x4f],0x67
   0x000000000000081b <+225>:	mov    BYTE PTR [rbp-0x4e],0x73
   0x000000000000081f <+229>:	mov    BYTE PTR [rbp-0x4d],0x7d
   0x0000000000000823 <+233>:	mov    DWORD PTR [rbp-0x4],0x0
   0x000000000000082a <+240>:	jmp    0x85b <main+289>
   0x000000000000082c <+242>:	mov    eax,DWORD PTR [rbp-0x4]
   0x000000000000082f <+245>:	cdqe
   0x0000000000000831 <+247>:	movzx  edx,BYTE PTR [rbp+rax*1-0x40]
   0x0000000000000836 <+252>:	mov    eax,DWORD PTR [rbp-0x4]
   0x0000000000000839 <+255>:	cdqe
   0x000000000000083b <+257>:	movzx  eax,BYTE PTR [rbp+rax*1-0x70]
   0x0000000000000840 <+262>:	cmp    dl,al
   0x0000000000000842 <+264>:	je     0x857 <main+285>
   0x0000000000000844 <+266>:	lea    rdi,[rip+0xe4]        # 0x92f
   0x000000000000084b <+273>:	call   0x5e0 <puts@plt>
   0x0000000000000850 <+278>:	mov    eax,0x1
   0x0000000000000855 <+283>:	jmp    0x880 <main+326>
   0x0000000000000857 <+285>:	add    DWORD PTR [rbp-0x4],0x1
   0x000000000000085b <+289>:	mov    eax,DWORD PTR [rbp-0x4]
   0x000000000000085e <+292>:	cmp    eax,0x23
   0x0000000000000861 <+295>:	jbe    0x82c <main+242>
   0x0000000000000863 <+297>:	lea    rax,[rbp-0x40]
   0x0000000000000867 <+301>:	mov    rsi,rax
   0x000000000000086a <+304>:	lea    rdi,[rip+0xc8]        # 0x939
   0x0000000000000871 <+311>:	mov    eax,0x0
   0x0000000000000876 <+316>:	call   0x600 <printf@plt>
   0x000000000000087b <+321>:	mov    eax,0x0
   0x0000000000000880 <+326>:	leave
   0x0000000000000881 <+327>:	ret
End of assembler dump.
```

アセンブリを読むと

入力文字列の長さが 0x24 と等しいかチェックし、`[rbp-0x4]` を 0x0~0x23 までインクリメントしながら入力文字列 `[rbp+rax*1-0x40]` とスタックに代入した数値 `[rbp+rax*1-0x70]` を一文字ずつ比較し、すべて一致すれば 0x939 を printf する

という処理をしている事がわかります。(頑張って読むしかないです。命令を調べながらどこに何の値が入っているか把握しながら読み進めてください。)

> ```
> mov    eax,DWORD PTR [rbp-0x4]
> cdqe
> ```
>
> で rax に `[rbp-0x4]` の値が入るので `[rbp+rax*1-0x40]` と `[rbp+rax*1-0x70]` は一文字ずつ比較することができる

よってスタックに代入している数値を Python の `chr()` を使って文字列へ変換すると

```python
flag = [""] * 36

flag[0] = chr(0x46)
flag[1] = chr(0x4c)
flag[2] = chr(0x41)
flag[3] = chr(0x47)
flag[4] = chr(0x7b)
flag[5] = chr(0x35)
flag[6] = chr(0x69)
flag[7] = chr(0x6d)
flag[8] = chr(0x70)
flag[9] = chr(0x31)
flag[10] = chr(0x65)
flag[11] = chr(0x5f)
flag[12] = chr(0x52)
flag[13] = chr(0x65)
flag[14] = chr(0x76)
flag[15] = chr(0x65)
flag[16] = chr(0x72)
flag[17] = chr(0x73)
flag[18] = chr(0x31)
flag[19] = chr(0x6e)
flag[20] = chr(0x67)
flag[21] = chr(0x5f)
flag[22] = chr(0x34)
flag[23] = chr(0x72)
flag[24] = chr(0x72)
flag[25] = chr(0x61)
flag[26] = chr(0x79)
flag[27] = chr(0x5f)
flag[28] = chr(0x35)
flag[29] = chr(0x74)
flag[30] = chr(0x72)
flag[31] = chr(0x69)
flag[32] = chr(0x6e)
flag[33] = chr(0x67)
flag[34] = chr(0x73)
flag[35] = chr(0x7d)

print("".join(flag))

# FLAG{5imp1e_Revers1ng_4rray_5trings}
```

フラグ `FLAG{5imp1e_Revers1ng_4rray_5trings}` が取得できます。

### Ghidra を使って解く

[Ghidra](https://ghidra-sre.org/) はアメリカ国家安全保障局 NSA が開発しているリバースエンジニアリングツールです。

強力な逆コンパイラを無料で使うことができるのでとてもおすすめです。

バイナリを読み込んで main 関数の Decompile 画面を表示すると以下のコードが見れます。

```c
undefined8 main(void)

{
  size_t sVar1;
  undefined8 uVar2;
  char local_78 [48];
  char local_48 [60];
  uint local_c;

  printf("input flag : ");
  __isoc99_scanf(&DAT_00100922,local_48);
  sVar1 = strlen(local_48);
  if (sVar1 == 0x24) {
    local_78[0] = 'F';
    local_78[1] = 0x4c;
    local_78[2] = 0x41;
    local_78[3] = 0x47;
    local_78[4] = 0x7b;
    local_78[5] = 0x35;
    local_78[6] = 0x69;
    local_78[7] = 0x6d;
    local_78[8] = 0x70;
    local_78[9] = 0x31;
    local_78[10] = 0x65;
    local_78[11] = 0x5f;
    local_78[12] = 0x52;
    local_78[13] = 0x65;
    local_78[14] = 0x76;
    local_78[15] = 0x65;
    local_78[16] = 0x72;
    local_78[17] = 0x73;
    local_78[18] = 0x31;
    local_78[19] = 0x6e;
    local_78[20] = 0x67;
    local_78[21] = 0x5f;
    local_78[22] = 0x34;
    local_78[23] = 0x72;
    local_78[24] = 0x72;
    local_78[25] = 0x61;
    local_78[26] = 0x79;
    local_78[27] = 0x5f;
    local_78[28] = 0x35;
    local_78[29] = 0x74;
    local_78[30] = 0x72;
    local_78[31] = 0x69;
    local_78[32] = 0x6e;
    local_78[33] = 0x67;
    local_78[34] = 0x73;
    local_78[35] = 0x7d;
    local_c = 0;
    while (local_c < 0x24) {
      if (local_48[(int)local_c] != local_78[(int)local_c]) {
        puts("Incorrect");
        return 1;
      }
      local_c = local_c + 1;
    }
    printf("Correct! Flag is %s\n",local_48);
    uVar2 = 0;
  }
  else {
    puts("incorrect");
    uVar2 = 1;
  }
  return uVar2;
}
```

さっきアセンブリを頑張って読んだのに...という感じです。

さらに `local_78` の上で右クリックをして `Retype Variable` を選択し `char[48]` を入力、それぞれの変数の名前を `Rename Variable` で変更すると多少違うところもありますがソースコードとほぼ同様な疑似 C コードが取得できます。

```c
undefined8 main(void)

{
  size_t strlen_input;
  undefined8 ret;
  char flag [48];
  char input [60];
  uint i;

  printf("input flag : ");
  __isoc99_scanf(&DAT_00100922,input);
  strlen_input = strlen(input);
  if (strlen_input == 0x24) {
    flag[0] = 'F';
    flag[1] = 'L';
    flag[2] = 'A';
    flag[3] = 'G';
    flag[4] = '{';
    flag[5] = '5';
    flag[6] = 'i';
    flag[7] = 'm';
    flag[8] = 'p';
    flag[9] = '1';
    flag[10] = 'e';
    flag[11] = '_';
    flag[12] = 'R';
    flag[13] = 'e';
    flag[14] = 'v';
    flag[15] = 'e';
    flag[16] = 'r';
    flag[17] = 's';
    flag[18] = '1';
    flag[19] = 'n';
    flag[20] = 'g';
    flag[21] = '_';
    flag[22] = '4';
    flag[23] = 'r';
    flag[24] = 'r';
    flag[25] = 'a';
    flag[26] = 'y';
    flag[27] = '_';
    flag[28] = '5';
    flag[29] = 't';
    flag[30] = 'r';
    flag[31] = 'i';
    flag[32] = 'n';
    flag[33] = 'g';
    flag[34] = 's';
    flag[35] = '}';
    i = 0;
    while (i < 0x24) {
      if (input[(int)i] != flag[(int)i]) {
        puts("Incorrect");
        return 1;
      }
      i = i + 1;
    }
    printf("Correct! Flag is %s\n",input);
    ret = 0;
  }
  else {
    puts("incorrect");
    ret = 1;
  }
  return ret;
}
```

フラグは `FLAG{5imp1e_Revers1ng_4rray_5trings}` です。
