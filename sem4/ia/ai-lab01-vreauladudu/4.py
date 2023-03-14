def Split(String, Delimiter = " ") -> list:
    '''
    Splits the String into substrings using Delimiter as a delimiter.
    Time complexity: theta(n)
    Space complexity: theta(n)
    :params String: str -> string to be splitted
            Delimiter: str -> delimiter
    :returns a list with the splitted substrings
    '''

    assert type(String) == str
    assert type(Delimiter) == str

    result = []
    index, start = 0, 0

    for index, char in enumerate(String):
        if char == Delimiter:
            result.append(String[start:index])
            start = index + 1

    result.append(String[start:index + 1])
    return result

def Split_test() -> None:
    assert Split('') == ['']
    assert Split('a') == ['a']
    assert Split('abc', 'b') == ['a', 'c']
    assert Split('ana are ana are mere rosii ana') == ['ana', 'are', 'ana', 'are', 'mere', 'rosii', 'ana']

def Only1Appearance(String) -> list:
    '''
    Identifies words that appear only once in the String.
    Time complexity: theta(n^2)
    Space complexity: theta(n)
    :params String: str -> string to be verified
    :returns a list with the words that appear only once
    '''

    assert type(String) == str

    splittedString = Split(String)

    return [substring for substring in splittedString if splittedString.count(substring) == 1]

def Only1Appearance_test() -> None:
    assert Only1Appearance('') == ['']
    assert Only1Appearance('c c c') == []
    assert Only1Appearance('a b c') == ['a', 'b', 'c']
    assert Only1Appearance('ana are ana are mere rosii ana') == ['mere', 'rosii']

if __name__ == "__main__":
    Split_test()
    Only1Appearance_test()

    string = 'ana are ana are mere rosii ana'
    print("Cuvintele care apar o singura data in '{}' sunt {}".format(string, Only1Appearance(string)))