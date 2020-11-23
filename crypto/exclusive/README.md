# exclusive

## 問題文
XORを使った暗号です🔐


## フラグ
`FLAG{xor_c1ph3r_is_vulnera6le_70_kn0wn_plain7ext_@ttack!}`

## 解法
XOR cipherでflagが暗号化されています。keyが予測されるようなもので無い限り復元は困難ですが、
- flagは"FLAG{"で始まる
- keyは先頭3文字の繰り返し 

であることからkeyを復元することができます。

この問題では先頭3文字だけ分かれば十分で、
(以下 `^` は XOR を表します)
- `ord('F') ^ ord('9') == ord('A')`
- `ord('L') ^ ord(';') == ord('B')`
- `ord('A') ^ ord('.') == ord('C')`

であることから、key は "ABCABCABCABC..." であることが分かります。

keyが分かったので、あとは`ciphertext == flag ^ key` より、 `flag == ciphertext ^ key` で flag が求まります。 



