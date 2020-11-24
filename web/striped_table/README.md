# striped table

## 問題文
```
テーブルの行の背景色をストライプにする作業をしてもらったら、こんなことになってしまいました!

ページにjavascript`alert(19640503)`を埋め込み実行させるとフラグが得られます。

<https://striped.wanictf.org/?source>にアクセスするとソースが閲覧できます。

<https://striped.wanictf.org>

writer : suuhito
```

## フラグ
```
FLAG{simple_cross_site_scripting}
```

## 解法
* `index.php`を見ると、`index`の偶奇で`tr`の色を変えているのが分かるが、黒のほう(偶数の方)はメモの`td`に対して`htmlspecialchars`をつけ忘れている。
* これにより、`xss`による攻撃が可能となる。
* 偶数行にスクリプトを埋め込むため、新規作成画面から2回以下のデータを送信する
  * タイトル: 適当
  * メモ: `<script>alert(19640503)</script>`
* スクリプトが実行され、Flagが得られる。
