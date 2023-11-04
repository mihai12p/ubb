class Cipher:
    def __init__(self, key_word: str) -> None:
        raise NotImplementedError('Can not instantiate an abstract class')

    def encrypt(self, plaintext: str) -> None:
        raise NotImplementedError('Encrypt method not implemented')

    def decrypt(self, ciphertext: str) -> None:
        raise NotImplementedError('Decrypt method not implemented')


class PermutationCipher(Cipher):
    def __init__(self, key_word: str) -> None:
        self.__key_word = key_word if len(key_word) > 0 else 'abcde'
        self.__numeric_key = self.__generate_permutation_matrix(self.__key_word)
        self.__key_length = len(self.__numeric_key)

    def __generate_permutation_matrix(self, key_word: str) -> None:
        sorted_key = sorted(set(key_word))  # sort the characters alphabetically and make them unique
        sorted_key_order = {character: index for index, character in enumerate(sorted_key)}  # get the permutation

        return [sorted_key_order[char] for char in key_word]  # get the key using the order of characters from keyword

    def encrypt(self, plaintext: str) -> str:
        padding_length = (-len(plaintext)) % self.__key_length
        plaintext += '_' * padding_length  # pad the plaintext with '_' until the plaintext length is divisible by key_length

        ciphertext = ''

        for i in range(0, len(plaintext), self.__key_length):  # each iteration = 1 block of size key_length
            block = plaintext[i:i + self.__key_length]
            permuted_block = [''] * self.__key_length
            for permutation_index, permutation_value in enumerate(self.__numeric_key):  # permutation index is from the first line in the permutation matrix
                permuted_block[permutation_index] = block[permutation_value]            # permutation value is from the second line in the permutation matrix
            ciphertext += ''.join(permuted_block)

        return ciphertext

    def decrypt(self, ciphertext: str) -> str:
        plaintext = ''

        for i in range(0, len(ciphertext), self.__key_length):  # each iteration = 1 block of size key_length
            block = ciphertext[i:i + self.__key_length]
            permuted_block = [''] * self.__key_length
            for permutation_index, permutation_value in enumerate(self.__numeric_key):  # permutation index is from the first line in the permutation matrix
                permuted_block[permutation_value] = block[permutation_index]            # permutation value is from the second line in the permutation matrix
            plaintext += ''.join(permuted_block)

        return plaintext.rstrip('_')  # remove padded characters

if __name__ == '__main__':
    key_word = 'fpslb'
    plaintext = 'COMPUTATIONAL'
    print('Plaintext:', plaintext)

    cipher = PermutationCipher(key_word)
    ciphertext = cipher.encrypt(plaintext)
    print('Encrypted:', ciphertext)
    decrypted = cipher.decrypt(ciphertext)
    print('Decrypted:', decrypted)