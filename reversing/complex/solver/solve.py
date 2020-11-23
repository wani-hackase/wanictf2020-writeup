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
