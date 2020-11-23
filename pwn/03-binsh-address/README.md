# binsh address [pwn]
## 問題文

```
nc binsh.wanictf.org 9003
```
+ 文字列はメモリのどこかに配置されています。
+ `strings -tx ./chall | less`

### 使用ツール例
+ [netcat (nc)](https://github.com/wani-hackase/memo-setup-pwn-utils#netcat)
+ [strings](https://github.com/wani-hackase/memo-setup-pwn-utils#strings)

### セキュリティ保護


+ Full RELocation ReadOnly (RELRO)
+ Stack Smash Protection (SSP)有効
+ No eXecute bit(NX)有効
+ Position Independent Executable (PIE)有効

## FLAG
```
FLAG{cAn-f1nd-str1ng-us1ng-str1ngs}
```
## 解法

まずはコードを読みます。
ポイントはグローバル変数の
```
char str_head[] = "Please input \"";
char binsh[] = "/bin/sh";
```
の部分と、vuln関数の中の

```
    p = (char *) val;
    if(p == binsh){
        puts("Congratulation!");
        system(p);
        exit(0);
    }else{
        puts("You are wrong.\n\n");
    }
```
の部分です。
自分が入力したアドレスとbinshのアドレスが一致していればOKです。

また、接続時にstr_headのアドレスが出力されています。
stringsコマンドで調べると
```
   2010 Please input "
   2020 /bin/sh
```
のように連続して配置されていて、/bin/shのアドレスはstr_headのアドレスの0x10バイト後ろにあるだけです。
というわけで出力された`Please input "`のアドレスに0x10を足して入力すると解けます。
PIEとASLRが有効なので実行する度にアドレスが変わりますが、例えば
```
$ ./pwn03
The address of "input  " is 0x7f6d72402010.
Please input "/bin/sh" address as a hex number:
```
と出力された場合は0x7f6d72402010 + 0x10 = 0x7f6d72402020なので`0x7f6d72402020`を入力すればシェルを取れます。
