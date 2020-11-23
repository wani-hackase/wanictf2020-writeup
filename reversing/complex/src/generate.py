import random, string

with open("/usr/share/dict/words", "r") as f:
    data = f.readlines()


def randomname(n):
    return "".join(random.choices(string.digits, k=n))


def genflag():
    while 1:
        a = data[random.randint(0, 200000)].strip().lower()
        b = data[random.randint(0, 200000)].strip().lower()
        c = data[random.randint(0, 200000)].strip().lower()
        flag = a + "_" + b + "_" + c
        if len(flag) == 37:
            return flag


def genkey(flag):
    while 1:
        key = randomname(37)
        res = ""
        for i in range(37):
            res += chr(ord(flag[i]) ^ ord(key[i]))
        if "\\" not in res:
            return key, res


count = 0

func = ""
case = ""

for _ in range(20):
    if count == 13:
        # FLAG{did_you_really_check_the_return_value}
        flag = "did_you_really_check_the_return_value"
        key, res = genkey(flag)

        code = "int check_%d(const unsigned char *flag)\n" % count
        code += "{\n"
        code += '  char key[37] = "%s";\n' % key
        code += '  char res[37] = "%s";\n' % res
        code += "  for (int j = 0; j < 37; j++)\n"
        code += "  {\n"
        code += "    if ((key[j] ^ flag[j]) != res[j])\n"
        code += "    {\n"
        code += "      return 1;\n"
        code += "    }\n"
        code += "  }\n"
        code += "  return 2;\n"
        code += "}\n"
        func += code
        count += 1

    else:
        flag = genflag()
        key, res = genkey(flag)
        code = "int check_%d(const unsigned char *flag)\n" % count
        code += "{\n"
        code += '  char key[37] = "%s";\n' % key
        code += '  char res[37] = "%s";\n' % res
        code += "  for (int j = 0; j < 37; j++)\n"
        code += "  {\n"
        code += "    if ((key[j] ^ flag[j]) != res[j])\n"
        code += "    {\n"
        code += "      return 0;\n"
        code += "    }\n"
        code += "  }\n"
        code += "  return 1;\n"
        code += "}\n"
        func += code
        count += 1

for i in range(count):
    code = "  case %d:\n" % i
    code += "    res = check_%d(flag);\n" % i
    code += "    return res;\n"
    case += code

with open("template.c", "r") as f:
    src = f.read()
src = src.replace("####", func)
src = src.replace("$$$$", case)
src = src.replace("%%%%", str(count))
with open("main.c", "w") as f:
    f.write(src)
