def parse_grammar_from_file(file_path: str) -> list:
    nonterminals = set()
    terminals = set()
    productions = []
    start_symbol = None
    epsilon = 'epsilon'

    try:
        with open(file_path, 'r') as file:
            for line in file:
                line = line.strip()
                if '->' in line:
                    left, right = line.split('->')
                    left = left.strip()
                    right = right.strip()

                    if start_symbol is None:
                        start_symbol = left
                    nonterminals.add(left)

                    productions.append((left, right))

            file.seek(0, 0)
            for line in file:
                line = line.strip()
                if '->' in line:
                    left, right = line.split('->')
                    left = left.strip()
                    right = right.strip()

                    for symbols in right.split(" | "):
                        if symbols == epsilon:
                            continue

                        for symbol in symbols:
                            if symbol not in nonterminals:
                                terminals.add(symbol)

        return nonterminals, terminals, start_symbol, productions

    except FileNotFoundError:
        print(f"Fisierul nu a fost gasit: {file_path}")
        return None
    except Exception as e:
        print(f"A aparut o eroare: {e}")
        return None

if __name__ == '__main__':
    file_path = 'gramatica.txt'
    nonterminals, terminals, start_symbol, productions = parse_grammar_from_file(file_path)
    print('Neterminale:', nonterminals)
    print('Terminale:', terminals)
    print('Simbol de start:', start_symbol)
    print('Reguli de productie:', productions)
