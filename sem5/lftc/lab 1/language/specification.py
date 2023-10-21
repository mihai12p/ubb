class Specification:
    def __init__(self) -> None:
        self.__separators = ['{', '}', '(', ')', ';', ':', ',', '"']
        self.__operators = ['+', '-', '*', '/', '%', '&&', '||', '==', '!=', '<', '<=', '>', '>=', '<<', '>>', '=']
        self.__reserved_words = ['return', '#include', '<iostream>', 'main', 'const', 'int', 'double', 'struct', 'TipSpecial',
                                 'while', 'std::cin', 'std::cout', 'if', 'else', 'switch', 'case', 'default', 'break']
        self.__auxiliary = ['ID', 'CONST']
        
        self.__atoms = self.__auxiliary + self.__separators + self.__operators + self.__reserved_words
        self.__condification = dict([(self.__atoms[i], i) for i in range(len(self.__atoms))])

    def get_codification(self) -> dict:
        return self.__condification
    
    def get_separators(self) -> list:
        return self.__separators
    
    def get_reserved_words(self) -> list:
        return self.__reserved_words
    
    def get_operators(self) -> list:
        return self.__operators