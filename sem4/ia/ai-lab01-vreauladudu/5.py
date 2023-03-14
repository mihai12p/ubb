def GetDuplicate(List) -> int:
    '''
    Identifies the value that appears twice in the List.
    Time complexity: theta(n)
    Space complexity: O(1)
    :params List: list -> list with numbers
    :returns the value that appears twice in the List
    '''

    assert type(List) == list
    assert len(List) >= 2

    listLenWithoutDuplicates = len(List) - 1

    return sum(List) - listLenWithoutDuplicates * (listLenWithoutDuplicates + 1) // 2

def GetDuplicate_test() -> None:
    assert GetDuplicate([1, 2, 1]) == 1
    assert GetDuplicate([1, 4, 5, 3, 2, 4]) == 4
    assert GetDuplicate([1, 1]) == 1
    assert GetDuplicate([1, 2, 3, 4, 2]) == 2

if __name__ == "__main__":
    GetDuplicate_test()

    print(GetDuplicate([1, 2, 3, 4, 2]))