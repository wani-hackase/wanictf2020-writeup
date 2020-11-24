def encrypt(s1, s2):
    assert len(s1) == len(s2)

    result = ""
    for c1, c2 in zip(s1, s2):
        result += chr(ord(c1) ^ ord(c2))

    return result


key = "ABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC"

with open("output.txt", "r") as f:
    flag = f.read()

plaintext = encrypt(key, flag)
print(plaintext)
