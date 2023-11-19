from util.af import FiniteAutomaton
from language.specification import Specification
from util.list import LexiTable

class Util:
    def __init__(self) -> None:
        self.__specification = Specification()

        self.__reserved_words = self.__specification.get_reserved_words()
        self.__separators = self.__specification.get_separators()
        self.__operators = self.__specification.get_operators()

    def is_reserved_word(self, word: str) -> bool:
        return word in self.__reserved_words
    
    def is_separator(self, word: str) -> bool:
        return word in self.__separators
    
    def is_operator(self, word: str) -> bool:
        return word in self.__operators
    
    def is_identifier(self, word: str) -> bool:
        if self.is_constant(word[0]):
            return False
        
        return word.isalnum() and len(word) <= 8

    def is_constant(self, word: str) -> bool:
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

if __name__ == '__main__':
    file_name = input('Insert file name: ')

    identifier_automaton = FiniteAutomaton(r'util\af_identificator.txt')
    integer_automaton = FiniteAutomaton(r'util\af_constanta_intreaga.txt')
    float_automaton = FiniteAutomaton(r'util\af_constanta_reala.txt')
    delimiter_automaton = FiniteAutomaton(r'util\af_spatiu.txt')
    include_automaton = FiniteAutomaton(r'util\af_include.txt')
    symbols_automaton = FiniteAutomaton(r'util\af_simboluri.txt')

    util = Util()
    symbols_table = LexiTable()
    internal_form_table = []
    alls = []

    atoms = {}
    i = 2

    with open(file_name + '.txt', 'r') as f:
        lines = f.readlines()
        for index, line in enumerate(lines):
            if line == '\n':
                continue

            print('----------------------------------------')
            sequence = line.rstrip().strip()

            print('Working on {}'.format(sequence))

            last_accepted_pos = -1
            last_accepted_pos_inner = 0
            while True:

                is_constant = False
                is_identifier = False

                subsequence = sequence[last_accepted_pos+1:]
                longest_accepted_subseq, last_accepted_pos_inner = float_automaton.longest_accepted_prefix(subsequence)
                if last_accepted_pos_inner == -1:
                    longest_accepted_subseq, last_accepted_pos_inner = integer_automaton.longest_accepted_prefix(subsequence)
                    if last_accepted_pos_inner == -1:
                        longest_accepted_subseq, last_accepted_pos_inner = identifier_automaton.longest_accepted_prefix(subsequence)
                        if last_accepted_pos_inner == -1:
                            longest_accepted_subseq, last_accepted_pos_inner = delimiter_automaton.longest_accepted_prefix(subsequence)
                            if last_accepted_pos_inner == -1:
                                longest_accepted_subseq, last_accepted_pos_inner = include_automaton.longest_accepted_prefix(subsequence)
                                if last_accepted_pos_inner == -1:
                                    longest_accepted_subseq, last_accepted_pos_inner = symbols_automaton.longest_accepted_prefix(subsequence)
                        else:
                            is_identifier = True
                    else:
                        is_constant = True
                else:
                    is_constant = True

                if last_accepted_pos == -1:
                    last_accepted_pos = last_accepted_pos_inner
                else:
                    last_accepted_pos += last_accepted_pos_inner + 1

                if longest_accepted_subseq == ' ':
                    continue

                if last_accepted_pos_inner == -1:
                    break

                if util.is_reserved_word(longest_accepted_subseq) or util.is_separator(longest_accepted_subseq) or util.is_operator(longest_accepted_subseq):
                    atoms[longest_accepted_subseq] = i
                    i += 1
                elif is_identifier and util.is_identifier(longest_accepted_subseq):
                    atoms[longest_accepted_subseq] = 0
                    symbols_table.append(longest_accepted_subseq)
                elif is_constant and util.is_constant(longest_accepted_subseq):
                    atoms[longest_accepted_subseq] = 1
                    symbols_table.append(longest_accepted_subseq)
                else:
                    raise Exception('Error at line {}: {}'.format(index + 1, longest_accepted_subseq))

                alls.append(longest_accepted_subseq)
                print('The longest accepted subsequence is {}'.format(longest_accepted_subseq))

    symbols_table = symbols_table.get_elements()
    for word in alls:
        if util.is_reserved_word(word) or util.is_separator(word) or util.is_operator(word):
            internal_form_table.append([atoms[word], 0])
            continue

        if util.is_identifier(word) or util.is_constant(word):
            internal_form_table.append([atoms[word], symbols_table[word]])
        else:
            raise Exception('Error at line {}: {}'.format(index + 1, word))

    print('Forma interna a programului')
    print('{:>4} {:>24}'.format('Cod', 'Pozitie in TS'))
    for data in internal_form_table:
        print('{:>4} {:>24}'.format(data[0], data[1] if data[1] else ''))
    print()

    print('Tabela de simboluri')
    print('{:>4} {:>24}'.format('Pozitie', 'Atom lexical'))
    for atom, position in symbols_table.items():
        print('{:>4} {:>24}'.format(position, atom))