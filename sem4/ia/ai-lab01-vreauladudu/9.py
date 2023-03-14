def SubmatrixSum(Matrix, N, M) -> None:
    '''
    Pre-compute submatrix with sums of Matrix.
    Time complexity: O(N*M)
    Space complexity: O(N*M)
    :params Matrix: list -> initial matrix
            N: int -> number of rows
            M: int -> number of columns
    :returns submatrix with sums from (0, 0) to (N - 1, M - 1)
    '''

    assert type(Matrix) == list

    SumMatrix = [[0 for i in range(M)] for j in range(N)]

    for i in range(M):
        SumMatrix[0][i] = Matrix[0][i]
 
    for i in range(1, N):
        for j in range(M):
            SumMatrix[i][j] = Matrix[i][j] + SumMatrix[i - 1][j]
 
    for i in range(N):
        for j in range(1, M):
            SumMatrix[i][j] += SumMatrix[i][j - 1]

    return SumMatrix

def SumQuery(SumMatrix, Points) -> int:
    '''
    Calculates the sum of the submatrix.
    Time complexity: O(1)
    Space complexity: O(1)
    :params SumMatrix: list -> sum matrix computed
            Points: list -> list with 2 points as vector of the queried submatrix
    :returns the sum of the queried submatrix
    '''

    assert type(SumMatrix) == list
    assert type(Points) == list

    x, y = Points[0], Points[1]

    res = SumMatrix[y[0]][y[1]]
 
    if x[0] > 0:
        res -= SumMatrix[x[0] - 1][y[1]]
 
    if x[1] > 0:
        res -= SumMatrix[y[0]][x[1] - 1]
 
    if x[0] > 0 and x[1] > 0:
        res += SumMatrix[x[0] - 1][x[1] - 1]
 
    return res

def SumQuery_test() -> None:
    Matrix = [[0, 2, 5, 4, 1],
              [4, 8, 2, 3, 7],
              [6, 3, 4, 6, 2],
              [7, 3, 1, 8, 3],
              [1, 5, 7, 9, 4]]
    
    rows = len(Matrix)
    columns = len(Matrix[0])
    
    sumMatrix = SubmatrixSum(Matrix, rows, columns)

    assert SumQuery(sumMatrix, [[1, 1], [3, 3]]) == 38
    assert SumQuery(sumMatrix, [[2, 2], [4, 4]]) == 44

if __name__ == "__main__":
    SumQuery_test()

    Matrix = [[0, 2, 5, 4, 1],
              [4, 8, 2, 3, 7],
              [6, 3, 4, 6, 2],
              [7, 3, 1, 8, 3],
              [1, 5, 7, 9, 4]]
    
    rows = len(Matrix)
    columns = len(Matrix[0])
    
    sumMatrix = SubmatrixSum(Matrix, rows, columns)
    print(SumQuery(sumMatrix, [[1, 1], [3, 3]]))