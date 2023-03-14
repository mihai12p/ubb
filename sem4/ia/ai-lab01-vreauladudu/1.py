def MergeSort(List, Key = lambda el1, el2 : el1 <= el2) -> list:
    '''
    Sorts the List of elements using Key function as a comparison criteria.
    Time complexity: theta(nlogn)
    Space complexity: O(n)
    :params List: list -> list to be ordered
            Key: function -> comparison criteria
    :returns the sorted List
    '''
    
    assert type(List) == list

    if len(List) <= 1:
        return List

    mid = len(List) // 2
    LSublist = MergeSort(List[:mid], Key)
    RSublist = MergeSort(List[mid:], Key)

    i, j = 0, 0
    result = []

    while i < len(LSublist) and j < len(RSublist):
        if Key(LSublist[i], RSublist[j]):
            result.append(LSublist[i])
            i += 1
        else:
            result.append(RSublist[j])
            j += 1

    return result + LSublist[i:] + RSublist[j:]

def MergeSort_test() -> None:
    assert MergeSort([]) == []
    assert MergeSort([1]) == [1]
    assert MergeSort([2, 1]) == [1, 2]
    assert MergeSort(['Ana', 'are', 'mere', 'rosii', 'si', 'o', 'Zambila', 'neagra', 'si', 'galbena'], lambda el1, el2 : el1.lower() <= el2.lower()) == ['Ana', 'are', 'galbena', 'mere', 'neagra', 'o', 'rosii', 'si', 'si', 'Zambila']

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
    assert Split('Ana are mere rosii si o Zambila neagra si galbena') == ['Ana', 'are', 'mere', 'rosii', 'si', 'o', 'Zambila', 'neagra', 'si', 'galbena']

def GetLastWord(String) -> str:
    '''
    Solves the first task.
    Time complexity: theta(nlogn)
    Space complexity: theta(n)
    :params String: str -> input string
    :returns the last word according to the task requirements
    '''
    return MergeSort(Split(String), lambda el1, el2 : el1.lower() <= el2.lower())[-1]

if __name__ == "__main__":
    MergeSort_test()
    Split_test()

    print(GetLastWord("Ana are mere rosii si o Zambila neagra si galbena"))