from numpy import dot

def DotProduct(X, Y) -> int | list:
    '''
    Calculates the dot (scalar) product of 2 vectors.
    :params X: list -> point 1 as vector
            Y: list -> point 2 as vector
    :returns the dot product for X and Y
    '''

    return dot(X, Y)

def DotProduct_test() -> None:
    assert DotProduct([1, 2], [3, 6]) == 15
    assert DotProduct([5, 5], [3, 6]) == 45
    assert DotProduct([1, 0, 2, 0, 3], [1, 2, 0, 3, 1]) == 4

if __name__ == "__main__":
    DotProduct_test()

    x = [1, 0, 2, 0, 3]
    y = [1, 2, 0, 3, 1]
    print("Produsul scalar al celor 2 vectori rari {} si {} este {}".format(x, y, DotProduct(x, y)))