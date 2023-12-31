# https://en.wikipedia.org/wiki/Rabin_cryptosystem

from sympy import isprime
import random

class Cipher:
    def __init__(self) -> None:
        raise NotImplementedError('Can not instantiate an abstract class')

    def encrypt(self, plaintext: str) -> None:
        raise NotImplementedError('Encrypt method not implemented')

    def decrypt(self, ciphertext: str) -> None:
        raise NotImplementedError('Decrypt method not implemented')


class RabinCipher(Cipher):
    def __init__(self) -> None:
        self.__alphabet = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        self.__char_to_num = {char: i for i, char in enumerate(self.__alphabet)}
        self.__num_to_char = {i: char for i, char in enumerate(self.__alphabet)}
        self.__public_key, self.__private_key = self.__keypair(64)

    def __generate_large_prime(self, keysize: int) -> int:
        while True:
            num = random.randrange(2 ** (keysize - 1), 2 ** (keysize))
            if isprime(num) and num % 4 == 3:  # ensure the prime number is of form 4n + 3
                return num

    def __keypair(self, bit_length: int) -> tuple[int]:
        # generate a pair of distinct large primes (p, q)
        p = self.__generate_large_prime(bit_length)
        q = self.__generate_large_prime(bit_length)
        while p == q:
            p = self.__generate_large_prime(bit_length)
            q = self.__generate_large_prime(bit_length)
        n = p * q
        return (n), (p, q)

    def __text_to_number(self, text: str) -> int:
        number = 0
        length = len(text)
        for i, char in enumerate(text):
            power = length - 1 - i
            number += self.__char_to_num[char] * (len(self.__alphabet) ** power)
        return number

    def __number_to_text(self, number: int) -> str:
        text = ''
        while number > 0:
            number, char_num = divmod(number, len(self.__alphabet))
            text = self.__num_to_char[char_num] + text

        return text

    def __validate_plaintext(self, plaintext: str) -> bool:
        return all(char in self.__alphabet for char in plaintext)

    def encrypt(self, plaintext: str) -> int:
        if not self.__validate_plaintext(plaintext):
            raise ValueError('Invalid plaintext. Only characters in the alphabet are allowed.')

        if any(self.__char_to_num[char] >= self.__public_key for char in plaintext):
            raise ValueError('Public key is too small for the given plaintext.')

        return pow(self.__text_to_number(plaintext), 2, self.__public_key)

    def __validate_ciphertext(self, ciphertext: int) -> bool:
        return 0 <= ciphertext < self.__public_key

    def decrypt(self, ciphertext: str) -> list[str]:
        if not self.__validate_ciphertext(ciphertext):
            raise ValueError('Invalid ciphertext. It must be a non-negative integer smaller than the public key.')

        decrypted_texts = []

        p, q = self.__private_key
        n = p * q

        # compute modular inverses
        y_p = pow(p, -1, q)
        y_q = pow(q, -1, p)

        # compute the square roots
        m_p = pow(ciphertext, (p + 1) // 4, p)
        m_q = pow(ciphertext, (q + 1) // 4, q)

        # calculate the four possible plaintexts
        r1 = (y_p * p * m_q + y_q * q * m_p) % n
        r2 = n - r1
        r3 = (y_p * p * m_q - y_q * q * m_p) % n
        r4 = n - r3

        roots = [r1, r2, r3, r4]
        for root in roots:
            decrypted_texts.append(self.__number_to_text(root))

        return decrypted_texts

if __name__ == '__main__':
    plaintext = 'HELLO WORLD'
    print('Plaintext:', plaintext)

    cipher = RabinCipher()
    try:
        ciphertext = cipher.encrypt(plaintext)
        print('Ciphertext:', ciphertext)
        decrypted = cipher.decrypt(ciphertext)
        print('Decrypted:', decrypted)
    except ValueError as e:
        print(f'Cipher error: {e}')