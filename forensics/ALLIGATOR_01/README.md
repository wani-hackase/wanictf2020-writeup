# ALLIGATOR_01

## 問題文

ワニ博士のPCでは，悪意のあるプロセスが実行されているみたいです。

取得したメモリダンプから、”evil.exe”が実行された日時を報告してください。

(注意: スペースはすべて半角のアンダースコアにしてください)

example: FLAG{1234-56-78_99:99:99_UTC+0000}

問題ファイル: [ALLIGATOR.zip](https://mega.nz/file/dHZWkTzA#9a-yHID2Fg_upTaVmYKhO_3-gu7Q0JbLiw-HSfarQyU)
(ミラー: [ALLIGATOR.zip](https://drive.google.com/file/d/1yb6Ojbl7xkgRYU-4DgNi-0iJWT6jO2uW/view?usp=sharing))

推奨ツール: [volatility](https://github.com/volatilityfoundation/volatility)


## FLAG
FLAG{2020-10-26_03:01:55_UTC+0000}

## 解法

環境によっては、volatilityを使えるようにすること自体が難しかった人もいるかもしれないですが、volatilityを使っていきます。


### ALLIGATOR_01-03共通
ひとまず最初は、`imageinfo`でprofileを調べる必要がある。

```
$ volatility -f ALLIGATOR.raw imageinfo
Volatility Foundation Volatility Framework 2.6
INFO    : volatility.debug    : Determining profile based on KDBG search...
          Suggested Profile(s) : Win7SP1x86_23418, Win7SP0x86, Win7SP1x86
                     AS Layer1 : IA32PagedMemoryPae (Kernel AS)
                     AS Layer2 : FileAddressSpace (/mnt/c/Users/ishioka/Desktop/ALLIGATOR.raw)
                      PAE type : PAE
                           DTB : 0x185000L
                          KDBG : 0x82754de8L
          Number of Processors : 1
     Image Type (Service Pack) : 1
                KPCR for CPU 0 : 0x80b96000L
             KUSER_SHARED_DATA : 0xffdf0000L
           Image date and time : 2020-10-26 03:04:49 UTC+0000
     Image local date and time : 2020-10-25 20:04:49 -0700
```
今回は、`Win7SP1x86_23418`を使っていく。

### ALLIGATOR_01

volatilityを用いてプロセスを確認するには、`pstree`を用いる。

```
$ volatility -f ALLIGATOR.raw --profile=Win7SP1x86_23418 pstree
Volatility Foundation Volatility Framework 2.6
Name                                                  Pid   PPid   Thds   Hnds Time
-------------------------------------------------- ------ ------ ------ ------ ----
 0x84a54ab0:csrss.exe                                 328    320      9    411 2020-10-26 19:00:23 UTC+0000
. 0x84aeab70:conhost.exe                              336    328      2     33 2020-10-26 03:00:28 UTC+0000
 0x843da208:wininit.exe                               364    320      3     77 2020-10-26 19:00:23 UTC+0000
. 0x84a5c7a8:services.exe                             460    364      6    211 2020-10-26 19:00:23 UTC+0000
.. 0x84aded20:svchost.exe                             768    460     20    455 2020-10-26 03:00:25 UTC+0000
... 0x84b2fd20:audiodg.exe                           1008    768      6    122 2020-10-26 03:00:25 UTC+0000
.. 0x84c5a9d8:svchost.exe                            1164    460     16    365 2020-10-26 03:00:26 UTC+0000
.. 0x84b35030:svchost.exe                            1040    460      7    135 2020-10-26 03:00:25 UTC+0000
.. 0x84b22030:svchost.exe                             920    460     16    344 2020-10-26 03:00:25 UTC+0000
.. 0x84abc030:VBoxService.ex                          660    460     12    116 2020-10-26 19:00:24 UTC+0000
.. 0x84f0d9c0:SearchIndexer.                         2332    460     11    688 2020-10-26 03:00:33 UTC+0000
... 0x83f211a8:SearchFilterHo                        2660   2332      5     99 2020-10-26 03:03:33 UTC+0000
... 0x84f32030:SearchProtocol                        2400   2332      6    279 2020-10-26 03:00:33 UTC+0000
.. 0x84e7f258:svchost.exe                            2052    460      5     92 2020-10-26 03:00:29 UTC+0000
.. 0x84b11710:svchost.exe                             880    460     18    414 2020-10-26 03:00:25 UTC+0000
... 0x84d05570:dwm.exe                               1544    880      3     68 2020-10-26 03:00:26 UTC+0000
... 0x84f49300:dwm.exe                               2948    880      3     72 2020-10-26 03:01:43 UTC+0000
.. 0x84ce78f0:taskhost.exe                           1444    460      8    163 2020-10-26 03:00:26 UTC+0000
.. 0x84d3d798:svchost.exe                            1628    460     12    216 2020-10-26 03:00:26 UTC+0000
.. 0x84aa0448:svchost.exe                             944    460     34    962 2020-10-26 03:00:25 UTC+0000
... 0x83ee7d20:wuauclt.exe                           2212    944      5     93 2020-10-26 03:03:31 UTC+0000
.. 0x84ac6810:svchost.exe                             712    460      8    276 2020-10-26 03:00:25 UTC+0000
.. 0x8493e578:svchost.exe                            3912    460     13    379 2020-10-26 03:02:30 UTC+0000
.. 0x84cad2c8:svchost.exe                            1340    460     18    309 2020-10-26 03:00:26 UTC+0000
.. 0x84a4bd20:taskhost.exe                           2884    460     10    250 2020-10-26 03:01:43 UTC+0000
.. 0x84aa58b8:svchost.exe                             596    460      9    354 2020-10-26 19:00:24 UTC+0000
... 0x84e6a910:WmiPrvSE.exe                          1108    596      7    161 2020-10-26 03:03:16 UTC+0000
... 0x83f3ac68:WmiPrvSE.exe                          3376    596      8    117 2020-10-26 03:04:27 UTC+0000
.. 0x84d14a80:svchost.exe                            1572    460     10    144 2020-10-26 03:00:26 UTC+0000
.. 0x84dbbd20:cygrunsrv.exe                          1840    460      6    101 2020-10-26 03:00:27 UTC+0000
... 0x84dc8030:cygrunsrv.exe                         1772   1840      0 ------ 2020-10-26 03:00:28 UTC+0000
.... 0x84aa1510:sshd.exe                              856   1772      4    100 2020-10-26 03:00:28 UTC+0000
.. 0x84e024e8:wlms.exe                               2024    460      4     46 2020-10-26 03:00:27 UTC+0000
.. 0x84d1d458:sppsvc.exe                             1908    460      4    146 2020-10-26 03:00:29 UTC+0000
.. 0x84c9e668:spoolsv.exe                            1300    460     13    294 2020-10-26 03:00:26 UTC+0000
. 0x84a89850:lsass.exe                                476    364      7    601 2020-10-26 19:00:23 UTC+0000
. 0x84a5f250:lsm.exe                                  484    364     10    170 2020-10-26 19:00:23 UTC+0000
 0x83d3ac58:System                                      4      0     82    541 2020-10-26 19:00:20 UTC+0000
. 0x84429020:smss.exe                                 252      4      2     32 2020-10-26 19:00:20 UTC+0000
 0x84435030:explorer.exe                             2964   2932     34   1091 2020-10-26 03:01:43 UTC+0000
. 0x84dd6b28:evil.exe                                3632   2964      1     21 2020-10-26 03:01:55 UTC+0000
. 0x84dd8030:VBoxTray.exe                            3108   2964     13    143 2020-10-26 03:01:43 UTC+0000
. 0x83f52d20:MRCv120.exe                             3740   2964     16    356 2020-10-26 03:04:32 UTC+0000
. 0x8494c030:cmd.exe                                 3728   2964      1     19 2020-10-26 03:02:09 UTC+0000
 0x849c0220:winlogon.exe                              408    356      3    110 2020-10-26 19:00:23 UTC+0000
 0x84a66030:csrss.exe                                 376    356      8    145 2020-10-26 19:00:23 UTC+0000
 0x84d12be0:explorer.exe                             1564   1532     18    644 2020-10-26 03:00:26 UTC+0000
. 0x84dc8a38:VBoxTray.exe                            1880   1564     12    142 2020-10-26 03:00:27 UTC+0000
 0x8448eb18:csrss.exe                                2676   2656      7    218 2020-10-26 03:01:39 UTC+0000
. 0x83eb8d20:conhost.exe                             3736   2676      2     53 2020-10-26 03:02:09 UTC+0000
 0x84a22710:winlogon.exe                             2700   2656      3    107 2020-10-26 03:01:39 UTC+0000
```

したがって、
```
. 0x84dd6b28:evil.exe                                3632   2964      1     21 2020-10-26 03:01:55 UTC+0000
```
フォーマットに合わせてフラグを作る。