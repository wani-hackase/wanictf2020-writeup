import random
import os
from math import gcd

from Crypto.Util.number import *

from const import flag, logo, description, menu


def log(message):
    character_color = "\x1b[34m"
    reset = "\x1b[0m"
    print(f"{character_color} - {message}{reset}")


class RNG:
    def __init__(self, seed, a, b, m):
        self.a = a
        self.b = b
        self.m = m
        self.x = seed % m

    def next(self):
        self.x = (self.a * self.x + self.b) % self.m
        return self.x


def show_menu():
    print(menu)
    log(description)
    while not (choice := input("> ")) in "123":
        print("Invalid choice.")

    return int(choice)


if __name__ == "__main__":
    print(logo)
    seed = random.getrandbits(64)
    a = random.getrandbits(64)
    b = random.getrandbits(64)
    m = getPrime(64, os.urandom)
    rng = RNG(seed, a, b, m)

    while True:
        choice = show_menu()
        # Print
        if choice == 1:
            print(rng.next())

        # Guess
        elif choice == 2:
            for cnt in range(1, 11):
                log(f"[{cnt}/10] Guess the next number!")
                try:
                    guess = int(input("> "))
                except ValueError:
                    print("Please enter an integer\n\n\n")
                    continue
                if guess == rng.next():
                    log(f"Correct! ")
                    cnt += 1
                else:
                    log(f"Wrong... Try again!")
                    break
            else:
                print(f"Congratz!  {flag}")
                break

        # Exit
        else:
            print("Bye :)")
            break
