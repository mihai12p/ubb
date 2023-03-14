def Fill(Matrix, X, Y, Rows, Columns):
    if Matrix[X][Y] in [1, 3]:
        return

    Matrix[X][Y] = 3

    if X + 1 < Rows:
        Fill(Matrix, X + 1, Y, Rows, Columns)

    if X - 1 >= 0:
        Fill(Matrix, X - 1, Y, Rows, Columns)

    if Y + 1 < Columns:
        Fill(Matrix, X, Y + 1, Rows, Columns)

    if Y - 1 >= 0:
        Fill(Matrix, X, Y - 1, Rows, Columns)

def InitAndFill(Matrix) -> list:
    '''
    Replaces all the occurences of null values which are completly encircled by positive values with 1s.
    Time complexity: O(max{N,M}^3)
    Space complexity: O((N+2)*(M+2))
    :params Matrix: list -> input matrix
    :returns the modified matrix with size of (N+2)*(M+2)
    '''
    
    assert type(Matrix) == list

    rows = len(Matrix)
    columns = len(Matrix[0])

    ModifiedMatrix = [[2 for i in range(columns + 2)] for j in range(rows + 2)]

    for i in range(1, rows + 1):
        for j in range(1, columns + 1):
            ModifiedMatrix[i][j] = Matrix[i - 1][j - 1]

    for i in range(0, rows + 2):
        Fill(ModifiedMatrix, i, 0, len(ModifiedMatrix), len(ModifiedMatrix[0]))
        Fill(ModifiedMatrix, i, len(ModifiedMatrix[0]) - 1, len(ModifiedMatrix), len(ModifiedMatrix[0]))

    for j in range(1, columns + 1):
        Fill(ModifiedMatrix, 0, j, len(ModifiedMatrix), len(ModifiedMatrix[0]))
        Fill(ModifiedMatrix, len(ModifiedMatrix) - 1, j, len(ModifiedMatrix), len(ModifiedMatrix[0]))

    for i in range(0, rows + 2):
        for j in range(0, columns + 2):
            if ModifiedMatrix[i][j] == 3:
                ModifiedMatrix[i][j] = 0
            elif not ModifiedMatrix[i][j]:
                ModifiedMatrix[i][j] = 1

    return ModifiedMatrix 

if __name__ == "__main__":
    Matrix = [[1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
              [1, 0, 0, 1, 1, 0, 1, 1, 1, 1],
              [1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
              [1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
              [1, 0, 0, 1, 1, 0, 1, 1, 0, 0],
              [1, 1, 0, 1, 1, 0, 0, 1, 0, 1],
              [1, 1, 1, 0, 1, 0, 1, 0, 0, 1],
              [1, 1, 1, 0, 1, 1, 1, 1, 1, 1]]

    rows = len(Matrix)
    columns = len(Matrix[0])

    ModifiedMatrix = InitAndFill(Matrix)

    for i in range(1, rows + 1):
        print(ModifiedMatrix[i][1:columns + 1])