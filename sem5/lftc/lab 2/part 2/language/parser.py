from language.specification import Specification
from util.list import LexiTable

class Parser:
    def __init__(self) -> None:
        self.__specification = Specification()

        self.__reserved_words = self.__specification.get_reserved_words()
        self.__separators = self.__specification.get_separators()
        self.__operators = self.__specification.get_operators()

    def __extract_atoms(self) -> list:
        atoms = {}

        i = 2
        for index, line in enumerate(self.__lines):
            words = line.split()
            for word in words:
                if word == '':
                    continue

                if self.__is_reserved_word(word) or self.__is_separator(word) or self.__is_operator(word):
                    atoms[word] = i
                    i += 1
                elif self.__is_identifier(word):
                    atoms[word] = 0
                elif self.__is_constant(word):
                    atoms[word] = 1
                else:
                    raise Exception('Error at line {}: {}'.format(index + 1, word))
    
        return atoms
    
    def get_symbols_table(self) -> dict:
        symbols_table = LexiTable()

        for line in self.__lines:
            words = line.split()
            for word in words:
                if word == '':
                    continue

                if self.__is_reserved_word(word) or self.__is_separator(word) or self.__is_operator(word):
                    continue

                symbols_table.append(word)

        return symbols_table.get_elements()

    def get_program_internal_form_table(self) -> list:
        internal_form_table = []

        atoms = self.__extract_atoms()
        symbols_table = self.get_symbols_table()

        for index, line in enumerate(self.__lines):
            words = line.split()
            for word in words:
                if word == '':
                    continue

                if self.__is_reserved_word(word) or self.__is_separator(word) or self.__is_operator(word):
                    internal_form_table.append([atoms[word], 0])
                    continue

                if self.__is_identifier(word) or self.__is_constant(word):
                    internal_form_table.append([atoms[word], symbols_table[word]])
                else:
                    raise Exception('Error at line {}: {}'.format(index + 1, word))

        return internal_form_table

    def __is_reserved_word(self, word: str) -> bool:
        return word in self.__reserved_words
    
    def __is_separator(self, word: str) -> bool:
        return word in self.__separators
    
    def __is_operator(self, word: str) -> bool:
        return word in self.__operators
    
    def __is_identifier(self, word: str) -> bool:
        if self.__is_constant(word[0]):
            return False
        
        return word.isalnum() and len(word) <= 8

    def __is_constant(self, word: str) -> bool:
        is_float = is_integer = False

        try:
            float(word)
            is_float = True
        except:
            pass
        
        try:
            int(word)
            is_integer = True
        except:
            pass

        return is_float or is_integer