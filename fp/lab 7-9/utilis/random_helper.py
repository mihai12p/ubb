from random import choices, randint
from string import ascii_lowercase, ascii_uppercase

def randomNumber() -> int:
    return randint(0, 1000)

def randomString() -> str:
   letters = ascii_lowercase + ascii_uppercase

   return ''.join(choices(letters, k = randint(0, 15)))
