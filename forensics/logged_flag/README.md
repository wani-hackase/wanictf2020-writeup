# logged_flag

## 問題文

ワニ博士が問題を作っていたので、作っているところをキーロガーで勝手に記録してみました。

先に公開してしまいたいと思います。

(ワニ博士は英字配列のキーボードを使っています)

## FLAG
FLAG{k3y_l0gg3r_1s_v3ry_d4ng3r0us}

## 解法

### 解法1
###### ワニ博士にとっての解法1。今回の想定解ではない。
steghideを使っているのでパスワードが分かる。

大文字の場合は、shiftが押されるので注意。
(例えば、"F"は"shift + F"を探す感じ)

配布の`key_log.txt`から、steghideによって`flag.txt`が`original.jpg`に隠されて、`secret.jpg`が生成されていることが分かる。

ログからパスワードは`machikanetamachikanesai`と分かるので、steghideを利用して、配布の画像からFLAGを抽出する。

`steghide extract -sf secret.jpg -p machikanetamachikanesai`

### 解法2
flag.txtの作成がログの中で行われているので、logを眺めてFLAGを探す。

大文字の場合は、shiftが押されるので注意。
(例えば、"F"は"shift + F"を探す感じ)

該当部分はここ
```
11：50：15　[E]
11：50：15　[C]
11：50：15　[H]
11：50：15　[O]
11：50：16　[Space]
11：50：23　[Shift]
11：50：24　[F]
11：50：26　[Shift]
11：50：26　[L]
11：50：27　[Shift]
11：50：27　[A]
11：50：28　[Shift]
11：50：28　[G]
11：50：29　[Shift]
11：50：29　[[]
11：50：31　[K]
11：50：32　[3]
11：50：33　[Y]
11：50：35　[Shift]
11：50：35　[-]
11：50：36　[L]
11：50：36　[0]
11：50：37　[G]
11：50：38　[G]
11：50：38　[3]
11：50：38　[R]
11：50：41　[Shift]
11：50：41　[-]
11：50：41　[1]
11：50：42　[S]
11：50：43　[Shift]
11：50：43　[-]
11：50：44　[V]
11：50：45　[3]
11：50：47　[R]
11：50：47　[Y]
11：50：47　[Shift]
11：50：47　[-]
11：50：49　[D]
11：50：49　[4]
11：50：50　[N]
11：50：51　[G]
11：50：52　[3]
11：50：52　[R]
11：50：53　[0]
11：50：54　[U]
11：50：54　[S]
11：50：55　[Shift]
11：50：55　[]]
11：50：56　[Space]
11：50：57　[Shift]
11：50：57　[.]
11：50：57　[Space]
11：50：58　[F]
11：50：58　[L]
11：50：58　[A]
11：50：58　[G]
11：50：59　[.]
11：50：59　[T]
11：51：00　[X]
11：51：00　[T]
11：51：03　[Enter]
```

(steghideを知らなかった人は、折角なのでちゃんと画像からflag取れることも確認してみてください。)