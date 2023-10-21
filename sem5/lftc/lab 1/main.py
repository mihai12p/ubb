from language.parser import Parser

if __name__ == '__main__':
    file_name = input('Insert file name: ')
    parser = Parser(file_name + '.txt')

    program_internal_form_table = parser.get_program_internal_form_table()
    print('Forma interna a programului')
    print('{:>4} {:>24}'.format('Cod', 'Pozitie in TS'))
    for data in program_internal_form_table:
        print('{:>4} {:>24}'.format(data[0], data[1] if data[1] else ''))
    print()
    symbols_table = parser.get_symbols_table()
    print('Tabela de simboluri')
    print('{:>4} {:>24}'.format('Pozitie', 'Atom lexical'))
    for atom, position in symbols_table.items():
        print('{:>4} {:>24}'.format(position, atom))