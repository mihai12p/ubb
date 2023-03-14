from math import dist

def EuclidianDistance(X, Y) -> float:
    '''
    Calculates the euclidian distance of 2 vectors.
    Time complexity: O(n)
    Space complexity: O(1)
    :params X: list -> point 1 as vector
            Y: list -> point 2 as vector
    :returns the euclidian distance between X and Y
    '''

    return dist(X, Y)

def EuclidianDistance_test() -> None:
    assert EuclidianDistance([1, 2], [3, 6]) == 4.47213595499958
    assert EuclidianDistance([5, 5], [3, 6]) == 2.23606797749979
    assert EuclidianDistance([1, 5], [4, 1]) == 5.00000000000000

if __name__ == "__main__":
    EuclidianDistance_test()

    x = [1, 5]
    y = [4, 1]
    print("Distanta euclidiana dintre {} si {} este {}".format(x, y, EuclidianDistance(x, y)))