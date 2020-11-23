# ALLIGATOR_03

## 問題文

Dr.WANIはいつも同じパスワードを使うらしいです。

Dr.WANIのパソコンから入手したパス付のzipファイルを開けて、博士の秘密を暴いてしまいましょう。

(ALLIGATOR_01で配布されているファイルを使ってください)


## FLAG
FLAG{The_Machikane_Crocodylidae}

## 解法

### ALLIGATOR_03

配布したzipにはパスワードがかかっている。

同じパスワードを使っているとのことなので、メモリからパスワードを入手してzipを開けることになる。

windowsでは、パスワードのハッシュ値（LMとNTLM）が保存されている．

hivelistから、`\REGISTRY\MACHINE\SYSTEM`と`\SystemRoot\System32\Config\SAM`を使って復元する。

```
$ volatility -f ALLIGATOR.raw --profile=Win7SP1x86_23418 hivelist
Volatility Foundation Volatility Framework 2.6
Virtual    Physical   Name
---------- ---------- ----
0x96833008 0x29f35008 \??\C:\System Volume Information\Syscache.hve
0x9a37a008 0x0edcf008 \??\C:\Users\ALLIGATOR\ntuser.dat
0x9a37c008 0x0eed1008 \??\C:\Users\ALLIGATOR\AppData\Local\Microsoft\Windows\UsrClass.dat
0x8780a6b8 0x282fb6b8 [no name]
0x8781a008 0x28349008 \REGISTRY\MACHINE\SYSTEM
0x87838218 0x28367218 \REGISTRY\MACHINE\HARDWARE
0x8b0599c8 0x248859c8 \??\C:\Windows\ServiceProfiles\LocalService\NTUSER.DAT
0x8cb07008 0x26f46008 \Device\HarddiskVolume1\Boot\BCD
0x8e7f7008 0x26313008 \SystemRoot\System32\Config\SOFTWARE
0x904655f8 0x225685f8 \??\C:\Users\IEUser\ntuser.dat
0x9144b5c0 0x260205c0 \SystemRoot\System32\Config\DEFAULT
0x937338d0 0x250778d0 \SystemRoot\System32\Config\SECURITY
0x93791458 0x1d940458 \SystemRoot\System32\Config\SAM
0x937b79c8 0x248899c8 \??\C:\Users\IEUser\AppData\Local\Microsoft\Windows\UsrClass.dat
0x937fb758 0x248dd758 \??\C:\Windows\ServiceProfiles\NetworkService\NTUSER.DAT
0x96449458 0x03f4f458 \??\C:\Users\sshd_server\ntuser.dat
0x9645d3d8 0x2830b3d8 \??\C:\Users\sshd_server\AppData\Local\Microsoft\Windows\UsrClass.dat
```
今回使うのは

`\SystemRoot\System32\Config\SAM`の`0x93791458`

と

`\REGISTRY\MACHINE\SYSTEM`の`0x8781a008`

```
$ volatility -f ALLIGATOR.raw --profile=Win7SP1x86_23418 hashdump -s 0x93791458 -y 0x8781a008
Volatility Foundation Volatility Framework 2.6
Administrator:500:aad3b435b51404eeaad3b435b51404ee:fc525c9683e8fe067095ba2ddc971889:::
Guest:501:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
IEUser:1000:aad3b435b51404eeaad3b435b51404ee:fc525c9683e8fe067095ba2ddc971889:::
sshd:1001:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
sshd_server:1002:aad3b435b51404eeaad3b435b51404ee:8d0a16cfc061c3359db455d00ec27035:::
ALLIGATOR:1003:aad3b435b51404eeaad3b435b51404ee:5e7a211fee4f7249f9db23e4a07d7590:::
```

john the ripperやhashcat、[crackstation](https://crackstation.net/)を利用してNTLM hashからパスワードを復元する。

パスワードは`ilovewani`とわかる。

`unzip -P ilovewani wani_secret.zip`

flag.txtが手に入る

``` flag.txt
【正式名称】
大阪大学　公式マスコットキャラクター「ワニ博士」
【プロフィール】
名前：  ワニ博士（わにはかせ）
誕生日：        5 月 3 日
性別：  オス
出身地：        大阪府　豊中市　待兼山町
【性格】
温厚，好奇心旺盛，努力型，お茶目，社交的，たまに天然，賢い
【趣味】
・阪大キャンパスでコーヒーを飲みながら学生としゃべる
・粉もん屋めぐり
・化石集め。(いつか自分の仲間に会うために)
・CTF: FLAG{The_Machikane_Crocodylidae}
```
これであなたもワニ博士博士。