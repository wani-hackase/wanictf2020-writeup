# simple_memo

## 問題文

```
flag.txtというファイルに私の秘密を隠したが、
完璧にサニタイズしたため辿りつける訳がない。

(Hint)
ディレクトリトラバーサルという脆弱性です。

writer : okmt
```

## フラグ

```
FLAG{y0u_c4n_get_hi5_5ecret_fi1e}
```

## 解法

```
/index.php?file=重要なメモ.txt

を見ることでflag.txtというファイルを検索するといいのかなと思うはずです。

/index.php?file=../flag.txt

とすると「../」は丸々消えてしまいます。

これは、reader.phpを見ると「../」がサニタイズされていることが分かる。

ただし、str_replace は再帰的にはサニタイズしない。

つまり、

/index.php?file=....//flag.txt

などで上の階層のファイルを見ることができる。
```
