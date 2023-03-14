def GenerateBinaryWithLimitOf(N) -> list:
    '''
    Generates all the binary numbers between 1 and N.
    Time complexity: theta(n)
    Space complexity: theta(n)
    :params N: int -> upper limit
    :returns a list with the binary numbers wanted
    '''
    
    assert type(N) == int
    assert 0 < N

    return [bin(i)[2:] for i in range(1, N + 1)]

def GenerateBinaryWithLimitOf_test() -> None:
    assert GenerateBinaryWithLimitOf(1) == ['1']
    assert GenerateBinaryWithLimitOf(2) == ['1', '10']
    assert GenerateBinaryWithLimitOf(4) == ['1', '10', '11', '100']

if __name__ == "__main__":
    GenerateBinaryWithLimitOf_test()

    print(GenerateBinaryWithLimitOf(4))