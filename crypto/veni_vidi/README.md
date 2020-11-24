# Veni, vidi

## 問題文
`SYNT{fvzcyr_pynffvpny_pvcure}`

## フラグ
`FLAG{simple_classical_cipher}`

## 解法
ROT13というシーザー暗号のシフト量を13に変更した暗号です。
暗号としての強度は全くありませんが、答えがうっかり見えないようにするための変換程度で用いられます。

問題文で与えられた暗号文内のアルファベットのみに注目して、各アルファベットを13文字後ろ（あるいは前）にシフトすることで復号することができます。暗号の種類が分かればオンラインの復号ツールを用いて簡単に復号できると思います。

手元でやるのであればこのような対応表を書くのがシンプルだと思います。
```
ABCDEFGHIJKLMNOPQRSTUVWXYZ
NOPQRSTUVWXYZABCDEFGHIJKLM
```

tr コマンドを利用する方法などもあります。
`echo SYNT{fvzcyr_pynffvpny_pvcure} | tr a-zA-Z n-za-mN-ZA-M`




