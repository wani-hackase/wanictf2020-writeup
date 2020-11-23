import random
import os

from Crypto.Util.number import getPrime

from const import description, flag, logo


def log(message):
    character_color = "\x1b[34m"
    reset = "\x1b[0m"
    print(f"{character_color}[+] {message}{reset}")


def rsa_0():
    while True:
        p, q = random.getrandbits(512), random.getrandbits(512)
        print(f"{p = }")
        print(f"{q = }")
        try:
            n = int(input("[n?] > "))
        except ValueError:
            log("Please enter an integer\n\n\n")
            continue

        if p * q == n:
            log(f"Correct! Proceed to the next challenge ->")
            return

        else:
            log("Wrong... Try again!\n\n\n")
            continue


def rsa_1():
    while True:
        p, q = getPrime(512, randfunc=os.urandom), getPrime(512, randfunc=os.urandom)
        m = random.getrandbits(128)
        e = 0x10001
        n = p * q
        print(f"{m = }")
        print(f"{e = }")
        print(f"{n = }")

        try:
            c = int(input("[c?] > "))
        except ValueError:
            log("Please enter an integer\n\n\n")
            continue

        if pow(m, e, n) == c:
            log(f"Correct! Proceed to the final challenge!")
            return

        else:
            log("Wrong... Try again!\n\n\n")
            continue


def rsa_2():
    while True:
        p, q = getPrime(512, randfunc=os.urandom), getPrime(512, randfunc=os.urandom)
        e = 0x10001
        n = p * q
        d = pow(e, -1, (p - 1) * (q - 1))
        m = random.getrandbits(128)
        while pow(pow(m, e, n), d, n) != m:
            m = random.getrandbits(128)
        c = pow(m, e, n)

        print(f"{p = }")
        print(f"{q = }")
        print(f"{e = }")
        print(f"{c = }")
        try:
            decrypted = int(input("[m?] > "))
        except ValueError:
            log("Please enter an integer\n\n\n")
            continue

        if m == decrypted:
            log(f"Correct! Here's your reward: {flag}")
            return

        else:
            log("Wrong... Try again!\n\n\n")
            continue


if __name__ == "__main__":

    print(logo)
    challenges = [rsa_0, rsa_1, rsa_2]
    for challenge_index in range(3):
        print(description[challenge_index])
        challenges[challenge_index]()
        print("\n")
