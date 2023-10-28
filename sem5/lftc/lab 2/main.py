from util.af import FiniteAutomaton

if __name__ == '__main__':
    automaton = FiniteAutomaton()
    automaton.read_from_file('af_tema.txt')
    automaton.display()
    while True:
        print('----------------------------------------')
        sequence = input("Enter a sequence: ")
        if automaton.is_sequence_accepted(sequence):
            print('The sequence {} is accepted'.format(sequence))
        else:
            print('The sequence {} is not accepted'.format(sequence))
            print('The longest accepted subsequence is {}'.format(automaton.longest_accepted_prefix(sequence)))