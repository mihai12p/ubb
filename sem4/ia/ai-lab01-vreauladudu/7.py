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
    assert MergeSort([7, 4, 6, 3, 9, 1], lambda el1, el2 : el1 >= el2) == [9, 7, 6, 4, 3, 1]

def GetBiggestNth(List, K) -> int:
    '''
    Finds the Kth biggest element in the List.
    Time complexity: theta(nlogn)
    Space complexity: O(n)
    :params List: list -> input list
            K: int -> Kth biggest element wanted
    :returns the Kth biggest element
    '''

    assert type(List) == list
    assert type(K) == int
    assert 0 < K < len(List)

    return MergeSort(List, lambda el1, el2 : el1 >= el2)[K - 1]

def GetBiggestNth_test() -> None:
    assert GetBiggestNth([1, 2], 1) == 2
    assert GetBiggestNth([7, 4, 6, 3, 9, 1], 4) == 4
    assert GetBiggestNth([7, 4, 6, 3, 9, 1], 2) == 7

if __name__ == "__main__":
    MergeSort_test()
    GetBiggestNth_test()

    print(GetBiggestNth([7, 4, 6, 3, 9, 1], 2))