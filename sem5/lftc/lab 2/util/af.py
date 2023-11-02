class FiniteAutomaton:
    def __init__(self) -> None:
        self.__states = set()
        self.__alphabet = set()
        self.__transitions = {}
        self.__initial_state = None
        self.__final_states = set()

    def read_from_file(self, filename: str) -> None:
        with open(filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line.startswith('STATES:'):
                    self.__states = set(line[len('STATES: '):].split(','))
                    self.__initial_state = sorted(self.__states)[0]
                elif line.startswith('ALPHABET:'):
                    self.__alphabet = set(line[len('ALPHABET: '):].split(','))
                elif line.startswith('TRANSITIONS:'):
                    transition_parts = line[len('TRANSITIONS: '):].split(',')
                    for part in transition_parts:
                        start, symbol, end = part.split('>')
                        if start not in self.__transitions:
                            self.__transitions[start] = {}
                        self.__transitions[start][symbol] = end
                elif line.startswith('FINAL:'):
                    self.__final_states = set(line[len('FINAL: '):].split(','))

    def read_from_keyboard(self) -> None:
        self.__states = set(input('Enter states separated by commas: ').split(','))
        self.__initial_state = input('Enter the initial state: ')
        self.__alphabet = set(input('Enter alphabet symbols separated by commas: ').split(','))
        transition_list = input('Enter transitions in format (state>symbol>state) separated by commas: ').split(',')
        for part in transition_list:
            start, symbol, end = part.split('>')
            if start not in self.__transitions:
                self.__transitions[start] = {}
            self.__transitions[start][symbol] = end
        self.__final_states = set(input('Enter final states separated by commas: ').split(','))

    def display(self) -> None:
        print('States:', self.__states)
        print('Initial State:', self.__initial_state)
        print('Alphabet:', self.__alphabet)
        print('Transitions:', self.__transitions)
        print('Final States:', self.__final_states)
        print('Is deterministic:', self.__is_deterministic())

    def is_sequence_accepted(self, sequence: str) -> bool:
        assert self.__is_deterministic(), 'The AF is not deterministic, will not check the sequence'

        current_state = self.__initial_state

        for symbol in sequence:
            if symbol not in self.__transitions[current_state]:
                return False
            current_state = self.__transitions[current_state][symbol]
        return current_state in self.__final_states

    def longest_accepted_prefix(self, sequence: str) -> str:
        current_state = self.__initial_state
        last_accepted_pos = -1

        for index, symbol in enumerate(sequence):
            if symbol not in self.__transitions[current_state]:
                break
            current_state = self.__transitions[current_state][symbol]
            if current_state in self.__final_states:
                last_accepted_pos = index

        if last_accepted_pos != -1:
            return sequence[:last_accepted_pos+1]
        elif self.__initial_state in self.__final_states:
            return 'epsilon'

        return ''

    def __is_deterministic(self) -> bool:
        if not self.__initial_state:
            return False

        for state in self.__states:
            for symbol in self.__alphabet:
                if state not in self.__transitions:
                    return False

                if symbol not in self.__transitions[state] or type(self.__transitions[state][symbol]) == list:
                    return False

        return True