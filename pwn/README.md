# 問題リスト

portは基本 9000
1. [done] netcat :9001
    + netcatコマンドの使い方
2. [done] 変数書き換え var-rewrite :9002
    + 学ぶこと
        + BoFで変数の書き換え
        + 文字列 ⇔ 10進数 ⇔ 16進数の変換
    + ターミナルからでも
    + stack dump
3. [done] 文字列の場所 binsh-address: 9003
    + ヒント
        + `strings -tx ./chall | less`
4. [done] GOTアドレス書き換え got-rewriter :9004
    + 範囲制限
    + GOT table dump
    + 601038    
    + 400807
    + winのアドレスは与える
    + 学ぶこと
        + global offset talbe
        + objdumpの使い方
        + 関数アドレスの調べ方
    + ヒント
       + global offset table
       + `objdump -d -M intel ./chall | less`
    + 使用ツール例
       + objdump
5. [done] リターンアドレス書き換え return-rewrite :9005
    + この辺からテキストの入力だけでは厳しい
    + stack dump
    + 学ぶこと
        + スタック上のリターンアドレス
        + バイナリの入力の仕方
        + objdumpの使い方
    + ヒント
        + スタック上の戻り番地
        + `(echo -e "\x01\x02\x03\x04\x05\x06\x07\x08"; cat ) | nc `
    + 使用ツール例
       + netcat, objdump
6. ROPで関数呼び出し: rop-func-call: 9006
    + stack dump
    + 学ぶこと
        + return oriented programming
        + アセンブリでの関数呼び出しの仕方
    + ヒント
       + return oriented programming (ROP)
       + x64の関数呼び出し
       + pwntoolsを使ったputs呼び出しのROP
       + bin shのアドレスや
    + 使用ツール例
       + objdump, strings, pwntools, ROPgadget
7. ROPリークからのone gadget :9007
    + ヒント
       + one-gadget RCE
       + GOTでリーク
    + 使用ツール例
       + objdump, pwntools, ROPgadget, one_gadget
8. heap問題 :9008
    + GOT書き換え禁止
    + ヒント
       + なし
    + [t-cache poisoning: FireShell CTF 2019 babyheap - ふるつき](https://furutsuki.hatenablog.com/entry/2019/02/26/112207)
9. httpサーバー :9009
    + ヒント
        + ghidra

# BoF 身に着けるべきテクニック

1. netcat
2. shを実行しても何も値が出てないこと
3. 変数書き換え canary無効
4. returnアドレス書き換えてsuccess canary無効
5. (canaryをリークさせてcanaryを書き換え)
6. (スタックにシェルコード送り込んで実行) NX無効
7. ROPでsystem呼び出し
8. ropでputs呼んでリーク
9. スタックピボット
10. libcのone gadget RCE
    + libcのリーク ROP ONE GADGET
11. GOTアドレスの書き換え
12. GOTアドレスを使ってリーク
13. ぐるぐる回して少しずつ書き換え

# アイディア

+ memory rewriter
+ http server
+ stackの中身表示

# メモ

+ PIE → リーク
+ canary → 任意アドレスの書き換え、ROP、リーク
+ NX → シェルコード
+ gdb-pedaの使い方のレクチャーをしたい
+ `gcc -Wl,-z,lazy,-z,relro main.c -o chall -no-pie -fno-stack-protector`

[gccでインラインアセンブリを使用せずにレジスタにアクセス](https://stackoverrun.com/ja/q/2116956)
```
#include<stdio.h>

void foo(void)
{
       register long rsp asm ("rsp");
       printf("RSP: %lx\n", rsp);
}

int main()
{
       register long rsp asm ("rsp");
       printf("RSP: %lx\n", rsp);
       foo();
       return 0;
}
```


# 初心者向け 環境構築

Ubuntuでやっているという前提で

## netcat

```
apt-get install netcat
```

でインストールできます。

## minicondaのインストール

https://docs.conda.io/en/latest/miniconda.html
からLinux用の
Miniconda3 Linux 64-bit
をダウンロードしてくる
例えば今であれば
https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
ダウンロードしたものをbash Miniconda3-latest-Linux-x86_64.shで実行してインストール


## pwntools構築用

```
conda create --name pwn python=3.8
conda activate pwn
pip install pwntools
conda deactivate
```

## ropgadget

```
pip install ropgadget
```

ROPgadget --binary filename

とするとROP gadgetを見ることができます。


## BoFで使うツール

+ netcat
+ pwntools
+ strings
+ 

## いろいろロードアドレスを調べる

+ `readelf -S chall | less`


## インストール用メモ
+ docker-compose up -d
+ docker-compose down
+ docmer-compose down --rmi all
+ docker exec -it one-gadget-rce bash