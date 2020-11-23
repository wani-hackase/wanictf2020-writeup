# strings

この問題では Linux の ELF 実行ファイル(バイナリ)である「strings」が配布されています。このバイナリは入力文字列をチェックし、正しいものかどうか判定する機能をもっています。

試しに`FAKE{this_is_fake}`と入力すると`Incorrect`と表示され、間違っている入力文字列であると示してくれます。

このバイナリが「正しい」と判定してくれる文字列を見つけ出してください。

ヒント：バイナリ解析のはじめの一歩は「表層解析」という手法です。

(このファイルを実行するためには Linux 環境が必要となりますので WSL や VirtualBox で用意してください)

```
$ file strings
strings: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=78a1aa79cb6ab262c29bc2302ac50dc5f29e4d78, not stripped

$ sudo chmod +x strings

$ ./strings
input flag : FAKE{this_is_fake_flag}
Incorrect
```

## フラグ

`FLAG{s0me_str1ngs_rem4in_1n_t7e_b1nary}`

## 解法

配布されたバイナリに対して strings コマンドを実行します。

strings コマンドはファイルの中の printable な文字列を表示するコマンドで、バイナリを解析するときにまず最初に実行するコマンドです。

```
$ strings strings
/lib64/ld-linux-x86-64.so.2
libc.so.6
strncmp
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
%z
%r
%j
=Y
AWAVI
AUATL
[]A\A]A^A_
input flag :
Incorrect
FLAG{s0me_str1ngs_rem4in_1n_t7e_b1nary}
Correct! Flag is %s
;*3$"
GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
...
```

フラグ `FLAG{s0me_str1ngs_rem4in_1n_t7e_b1nary}` を取れました。

この問題ではフラグの文字列をそのままソースコードに直書きしているので strings コマンドで取得できます。

```c
#include <stdio.h>
#include <string.h>

#define FLAG "FLAG{s0me_str1ngs_rem4in_1n_t7e_b1nary}"

int main(void)
{
  char input[50];
  printf("input flag : ");
  scanf("%s", input);

  if (strlen(input) != 39)
  {
    puts("Incorrect");
    return 1;
  }

  if (strncmp(input, FLAG, 39) == 0)
  {
    printf("Correct! Flag is %s\n", input);
  }
  else
  {
    puts("Incorrect");
  }
  return 0;
}
```
