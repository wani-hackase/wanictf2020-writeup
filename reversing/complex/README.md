# complex

この問題は「simple」問題よりも複雑なようです。

ツールの使い方をさらに調べつつ、トライしてください!

## フラグ

`FLAG{did_you_really_check_the_return_value}`

## 解法

Ghidra で見ていきます。

### main 関数

```c
undefined8 main(void)

{
  int iVar1;
  size_t sVar2;
  char local_78 [48];
  char local_48 [5];
  char acStack67 [37];
  char acStack30 [14];
  int local_10;
  uint local_c;

  printf("input flag : ");
  __isoc99_scanf(&DAT_00101dc2,local_48);
  sVar2 = strlen(local_48);
  if (((sVar2 != 0x2b) || (iVar1 = strncmp(local_48,"FLAG{",5), iVar1 != 0)) ||
     (iVar1 = strcmp(acStack30,"}"), iVar1 != 0)) {
    puts("Incorrect");
    return 1;
  }
  strncpy(local_78,acStack67,0x25);
  local_c = 0;
  do {
    if (0x13 < (int)local_c) {
      return 0;
    }
    local_10 = check((ulong)local_c,local_78,local_78);
    if (local_10 != 0) {
      if (local_10 == 1) {
        puts("Incorrect");
        return 1;
      }
      if (local_10 == 2) {
        printf("Correct! Flag is %s\n",local_48);
        return 0;
      }
    }
    local_c = local_c + 1;
  } while( true );
}
```

- 入力文字列の長さは 0x2b 、最初の 5 文字は `FLAG{` 、最後の一文字は `}`

- local_c を 0x0 から 0x13 までループしながら check 関数(第 1 引数は local_c 、第 2 引数は入力文字列の `FLAG{` と `}` に囲まれた 0x25 個の文字列)を呼ぶ

- check 関数の戻り値が 0 ならループを継続、1 なら不正解、２なら正解

という処理を行っているようなので check 関数を更に詳しく見ていきます。

### check 関数

```c
void check(undefined4 param_1,undefined8 param_2)

{
  switch(param_1) {
  case 0:
    check_0(param_2);
    break;
  case 1:
    check_1(param_2);
    break;
  case 2:
    check_2(param_2);
    break;
  case 3:
    check_3(param_2);
    break;
  case 4:
    check_4(param_2);
    break;
  case 5:
    check_5(param_2);
    break;
  case 6:
    check_6(param_2);
    break;
  case 7:
    check_7(param_2);
    break;
  case 8:
    check_8(param_2);
    break;
  case 9:
    check_9(param_2);
    break;
  case 10:
    check_10(param_2);
    break;
  case 0xb:
    check_11(param_2);
    break;
  case 0xc:
    check_12(param_2);
    break;
  case 0xd:
    check_13(param_2);
    break;
  case 0xe:
    check_14(param_2);
    break;
  case 0xf:
    check_15(param_2);
    break;
  case 0x10:
    check_16(param_2);
    break;
  case 0x11:
    check_17(param_2);
    break;
  case 0x12:
    check_18(param_2);
    break;
  case 0x13:
    check_19(param_2);
  }
  return;
}
```

第 1 引数の switch 文で `check_0` から `check_19` までをループで呼んで、それぞれの `check_*` 関数の戻り値を返す処理をしています。

それぞれの `check_*` 関数の動作を見てみます。

### check\_\* 関数

まずは check_0 関数を見てみます。

```c
undefined8 check_0(long param_1)

{
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_48;
  undefined local_44;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined4 local_18;
  undefined local_14;
  int local_c;

  local_38 = 0x3935353537343531;
  local_30 = 0x3235383535313332;
  local_28 = 0x3434363234303130;
  local_20 = 0x3732363635303234;
  local_18 = 0x36353831;
  local_14 = 0x36;
  local_68 = 0x5b5a41545a515459;
  local_60 = 0x6d54515d565f5240;
  local_58 = 0x6b5f555340435442;
  local_50 = 0x5255594246594055;
  local_48 = 0x5f415d5f;
  local_44 = 0x55;
  local_c = 0;
  while( true ) {
    if (0x24 < local_c) {
      return 1;
    }
    if (((int)*(char *)((long)&local_38 + (long)local_c) ^ (uint)*(byte *)(param_1 + local_c)) !=
        (int)*(char *)((long)&local_68 + (long)local_c)) break;
    local_c = local_c + 1;
  }
  return 0;
}
```

local_38 ~ local_14 と引数の文字列を 1 文字ずつ XOR を取り、local_68 ~ local_44 と等しいか確認し、もし不一致なら `return 0;` 、一致したなら `return 1;`を返しています。

ここで main 関数と check 関数の処理を振り返ると

> check 関数の戻り値が 0 ならループを継続、1 なら不正解、２なら正解
>
> この check 関数ではそれぞれの `check_*` 関数の戻り値を返す

であるのでこの check*0 関数は 0 と 1 しか戻り値がないのでフラグとは関係がない関数だとわかります。よって２を戻り値とする `check*\*` 関数を探すと、 check_13 関数のみとなっているのでこの中から本当の FLAG を取得できるはずです。

```c
undefined8 check_13(long param_1)

{
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_48;
  undefined local_44;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined4 local_18;
  undefined local_14;
  int local_c;

  local_38 = 0x3131393431333637;
  local_30 = 0x3435313837393235;
  local_28 = 0x3635313836343636;
  local_20 = 0x3834303131353334;
  local_18 = 0x34323435;
  local_14 = 0x37;
  local_68 = 0x6e44564d6e575f53;
  local_60 = 0x576a48545b585747;
  local_58 = 0x535d45675d57535e;
  local_50 = 0x675a42444550416b;
  local_48 = 0x415e5543;
  local_44 = 0x52;
  local_c = 0;
  while( true ) {
    if (0x24 < local_c) {
      return 2;
    }
    if (((int)*(char *)((long)&local_38 + (long)local_c) ^ (uint)*(byte *)(param_1 + local_c)) !=
        (int)*(char *)((long)&local_68 + (long)local_c)) break;
    local_c = local_c + 1;
  }
  return 1;
}
```

これから２を戻り値とする引数文字列を求めるスクリプトを書くと

```python
import binascii


def add_stack(data):
    return binascii.unhexlify(data)[::-1].decode()


local_38 = "3131393431333637"
local_30 = "3435313837393235"
local_28 = "3635313836343636"
local_20 = "3834303131353334"
local_18 = "34323435"
local_14 = "37"

key = ""
key += add_stack(local_38)
key += add_stack(local_30)
key += add_stack(local_28)
key += add_stack(local_20)
key += add_stack(local_18)
key += add_stack(local_14)

local_68 = "6e44564d6e575f53"
local_60 = "576a48545b585747"
local_58 = "535d45675d57535e"
local_50 = "675a42444550416b"
local_48 = "415e5543"
local_44 = "52"

res = ""
res += add_stack(local_68)
res += add_stack(local_60)
res += add_stack(local_58)
res += add_stack(local_50)
res += add_stack(local_48)
res += add_stack(local_44)

flag = ""

for i in range(len(key)):
    flag += chr(ord(key[i]) ^ ord(res[i]))

print("FLAG{" + flag + "}")

# FLAG{did_you_really_check_the_return_value}
```

フラグ `FLAG{did_you_really_check_the_return_value}` を取得できました。

## おまけ

シンボリック実行解析ツール [angr](https://github.com/angr/angr) でもフラグを取得するとができます。

Ghidra の逆コンパイル画面から到達してほしい箇所 `printf("Correct! Flag is %s\n",local_48);` のアドレスと到達してほしくない箇所 `puts("Incorrect");` のアドレスを指定して解析するとフラグを自動で解析してくれます。

```python
import angr

proj = angr.Project("./complex")

target_addr = 0x401cb9
avoid_addr = 0x401c94

state = proj.factory.entry_state()
simgr = proj.factory.simgr(state)
simgr.explore(find=target_addr, avoid=avoid_addr)
state = simgr.found[0]
print(state.posix.dumps(0))
```
