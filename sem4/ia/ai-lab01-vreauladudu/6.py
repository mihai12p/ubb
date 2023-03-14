def GetMajor(List) -> int:
    '''
    Identifies the value that appears more than n / 2 in the List.
    Time complexity: theta(n^2)
    Space complexity: O(n)
    :params List: list -> list with numbers
    :returns the value that appears more than n / 2 in the List
    '''

    assert type(List) == list
    assert len(List) >= 2

    values = {}

    for value in List:
        values[value] = List.count(value)

    maximumAppearances = max(values.values())
    if maximumAppearances > len(List) // 2:
        for k, v in values.items():
            if v == maximumAppearances:
                return k
            
    return None

def GetMajor_test() -> None:
    assert GetMajor([1, 2, 1]) == 1
    assert GetMajor([1, 4, 1, 4, 1]) == 1
    assert GetMajor([1, 1]) == 1
    assert GetMajor([2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]) == 2

if __name__ == "__main__":
    GetMajor_test()

    print(GetMajor([2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]))