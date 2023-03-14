def MostElementsOf1(Matrix) -> list:
    '''
    Finds the index of the line that contains the greatest number of 1s.
    Time complexity: theta(N*M)
    Space complexity: O(1)
    :params Matrix: list -> input matrix
    :returns the index of the required line
    '''
    
    assert type(Matrix) == list

    idx, maximum = -1, 0

    for index, row in enumerate(Matrix):
        countValues = row.count(1)
        if countValues > maximum:
            maximum = countValues
            idx = index + 1

    return idx

if __name__ == "__main__":
    Matrix = [[0, 0, 0, 1, 1],
              [0, 1, 1, 1, 1],
              [0, 0, 1, 1, 1]]

    print(MostElementsOf1(Matrix))