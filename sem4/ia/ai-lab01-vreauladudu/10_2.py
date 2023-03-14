def MostElementsOf1(Matrix) -> list:
    '''
    Finds the index of the line that contains the greatest number of 1s.
    Time complexity: O(N*M)
    Space complexity: O(1)
    :params Matrix: list -> input matrix
    :returns the index of the required line
    '''
    
    assert type(Matrix) == list

    rows = len(Matrix)
    columns = len(Matrix[0])

    rowNumber, columnNumber = 0, 0
    while not Matrix[rowNumber][columnNumber]:
        rowNumber += 1
        if rowNumber >= rows:
            rowNumber = 0
            columnNumber += 1
            if columnNumber >= columns:
                return -1

    return rowNumber + 1

if __name__ == "__main__":
    Matrix = [[0, 0, 0, 1, 1],
              [0, 1, 1, 1, 1],
              [0, 0, 1, 1, 1]]

    print(MostElementsOf1(Matrix))