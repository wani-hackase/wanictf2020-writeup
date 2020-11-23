# Basic RSA

## 問題文
RSA暗号の基本的な演算ができますか？  
`nc rsa.wanictf.org 50000`

## フラグ
`FLAG{y0uv3_und3rst00d_t3xtb00k_RSA}`

## 解法
多倍長整数＋剰余演算に意外と触れる機会は少なそうだ思ったのと、小さい整数でRSAの暗号化・復号をやってもあまりRSA暗号が機能している感じがしないと思ったので、大きめの整数でその演算を行う問題を作りました。

多倍長整数の演算をするならPythonが楽だと思います。
mod inverseなどの計算も組み込み関数だけで完結するのでおすすめです。

### Challenge #1
![p](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+p), ![q](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+q)が与えられるので ![n = pq](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+n+%3D+pq) を送ればいいです。
```python
n = p*q
```

### Challenge #2
![m](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+m), ![e](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+e), ![n](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+n) が与えられるので、![c = m^e \mod n](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+c+%3D+m%5Ee+%5Cmod+n)を求めます。
基本的なRSAにおいてこの演算は暗号化に相当します。
Pythonでは
```python
c = pow(m, e, n)
```
で計算することができます。


### Challenge #3

![p](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+p), ![q](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+q), ![e](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+e), ![c](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+c)が与えられるので、![m](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+m)を求めます。この演算は復号に相当します。


秘密鍵 ![d](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+d) は、
![d \equiv e^{-1} \mod (p-1)(q-1)](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+d+%5Cequiv+e%5E%7B-1%7D+%5Cmod+%28p-1%29%28q-1%29)
で表され、これを計算すればよいです。
Pythonで ![a^{-1} \mod n](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+a%5E%7B-1%7D+%5Cmod+n) は
```python
pow(a, -1, n)
```
で求めることが可能です。

これを利用して、
```python
d = pow(e, -1, (p-1)*(q-1))
m = pow(c, d, p*q)
```
で求めることができます。
