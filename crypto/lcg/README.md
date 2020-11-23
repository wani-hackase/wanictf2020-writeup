# LCG crack

## 問題文

安全な暗号は安全な乱数から  
`nc lcg.wanictf.org 50001`

## フラグ

`FLAG{y0u_sh0uld_buy_l0tt3ry_t1ck3ts}`

## 解法

この問題では線形合同法（Linear Congruential Generator; LCG) を用いて乱数が生成されています。
生成式は  

![X_{n+1} \equiv (A X_n + B) \mod M](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+X_%7Bn%2B1%7D+%5Cequiv+%28A+X_n+%2B+B%29+%5Cmod+M)  

で与えられ、簡単に乱数列を生成することができます。  
その反面、十分な長さの乱数列から生成式のパラメータを解読することができ、次の乱数を予測することができます。そのためセキュリティ用途で、このように生成された乱数を用いてはいけません。  


&nbsp;
具体的な解法の1つは以下の通りです。
![A,B,M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A%2CB%2CM)のパラメータを、乱数列 ![X = (X_0, X_1, X_2, ...)](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+X+%3D+%28X_0%2C+X_1%2C+X_2%2C+...%29) から求めることを目標にします。

まず、![A, M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A%2C+M) が既に分かっている場合を考えます。  
例えば ![X_1 \equiv AX_0 + B](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+X_1+%5Cequiv+AX_0+%2B+B) を利用すると、  

![B \equiv X_{1}-AX_{0} \mod M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+B+%5Cequiv+X_%7B1%7D-AX_%7B0%7D+%5Cmod+M)    

と変形することで ![B](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+B) を求めることができます。  

&nbsp;

次に、![M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+M) のみが分かっている場合を考えます。  

![A](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A) を求めます。連立合同式  
![\begin{eqnarray}
\begin{cases}
X_1 \equiv AX_0 + B \mod M  \\
X_2 \equiv AX_1 + B \mod M
\end{cases}
\nonumber
\end{eqnarray}](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Beqnarray%7D%0A%5Cbegin%7Bcases%7D%0AX_1+%5Cequiv+AX_0+%2B+B+%5Cmod+M++%5C%5C%0AX_2+%5Cequiv+AX_1+%2B+B+%5Cmod+M%0A%5Cend%7Bcases%7D%0A%5Cnonumber%0A%5Cend%7Beqnarray%7D)  
を解くと、
![A \equiv (X_2 - X_1)(X_1-X_0)^{-1} \mod M](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+A+%5Cequiv+%28X_2+-+X_1%29%28X_1-X_0%29%5E%7B-1%7D+%5Cmod+M)    
が得られます。![A](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A) が求まったので、上記の方法で ![A, M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A%2C+M)から![B](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+B) も求まります。  

&nbsp;
  
最後に、全てのパラメータが不明である場合を考えます。  
![Y_i = X_{i+1}-X_i \ \ \ \  (i = 0, 1, \dots, 4)](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+Y_i+%3D+X_%7Bi%2B1%7D-X_i+%5C+%5C+%5C+%5C++%28i+%3D+0%2C+1%2C+%5Cdots%2C+4%29) を考えると、  
![\begin{eqnarray*}
\begin{cases}
Y_1 \equiv A Y_0 \mod M \\
Y_2 \equiv A Y_1 \equiv A^2 Y_0 \mod M \\
Y_3 \equiv A Y_2 \equiv A^3 Y_0 \mod M \\
Y_4 \equiv A Y_3 \equiv A^4 Y_0 \mod M \\
\end{cases}
\nonumber
\end{eqnarray*}](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Beqnarray%2A%7D%0A%5Cbegin%7Bcases%7D%0AY_1+%5Cequiv+A+Y_0+%5Cmod+M+%5C%5C%0AY_2+%5Cequiv+A+Y_1+%5Cequiv+A%5E2+Y_0+%5Cmod+M+%5C%5C%0AY_3+%5Cequiv+A+Y_2+%5Cequiv+A%5E3+Y_0+%5Cmod+M+%5C%5C%0AY_4+%5Cequiv+A+Y_3+%5Cequiv+A%5E4+Y_0+%5Cmod+M+%5C%5C%0A%5Cend%7Bcases%7D%0A%5Cnonumber%0A%5Cend%7Beqnarray%2A%7D)  
となります。ここで、  
![\begin{eqnarray*}
\begin{cases}
Y_3Y_1 - Y_2^2 \equiv 0 \mod M  \\
Y_4Y_2 - Y_3^2 \equiv 0 \mod M
\end{cases}
\nonumber
\end{eqnarray*}](https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cbegin%7Beqnarray%2A%7D%0A%5Cbegin%7Bcases%7D%0AY_3Y_1+-+Y_2%5E2+%5Cequiv+0+%5Cmod+M++%5C%5C%0AY_4Y_2+-+Y_3%5E2+%5Cequiv+0+%5Cmod+M%0A%5Cend%7Bcases%7D%0A%5Cnonumber%0A%5Cend%7Beqnarray%2A%7D)  
が成り立つので、![Y_3Y_1 - Y_2^2](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+Y_3Y_1+-+Y_2%5E2) と ![Y_4Y_2 - Y_3^2](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+Y_4Y_2+-+Y_3%5E2) のいずれも![M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+M)の倍数となります。 
よって、この2つの値に対して最大公約数を計算すると、![M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+M)が得られます。ただし一定確率でMの倍数が得られる場合があるので、乱数列を長めに取得し、より多くの値に対して最大公約数を計算すれば確実です。  
また、![A](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A) を求める際に、パラメータによっては ![(X_1-X_0)^{-1} \mod M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+%28X_1-X_0%29%5E%7B-1%7D+%5Cmod+M) が存在しないため失敗することがあります。この場合は成功するパラメータになるまで接続しなおせばOKです。5回くらい試せば十分成功すると思います。  
 
 
以上の方法を利用して![M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+M)から順に![A,B,M](https://render.githubusercontent.com/render/math?math=%5Ctextstyle+A%2CB%2CM)がそれぞれ求まるので、生成式を利用して次の乱数を算出できます。


> ご指摘を頂いて気づいたのですが、作問ミスがありました…　  
> 数字じゃない値を入力した際のエラー処理が不適切で、数字以外の文字を10回打てば通ります。  
> 正規の方法で通された方申し訳ありません。  
