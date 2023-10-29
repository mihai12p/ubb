#include <iostream>
#include <fstream>
#include <thread>
#include <barrier>

#define MAX_LINES       10010
#define MAX_COLUMNS     10010
#define CONV_MAX_K      3
#define MAX_P           16

int n, m, k, p;

struct ThreadData
{
    int* DataLineAbove;
    int* DataLineBelow;
};

void
ReadInputData(
    _Inout_  int&        Displacement,
    _Outptr_ int**       Matrix,
    _Outptr_ int**       ConvMatrix,
    _In_     const char* FileName
)
{
    std::ifstream fin(FileName);
    fin >> k;

    Displacement = k / 2;

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            fin >> ConvMatrix[i][j];
        }
    }

    fin >> n >> m;

    for (int i = Displacement; i < n + Displacement; ++i)
    {
        for (int j = Displacement; j < m + Displacement; ++j)
        {
            fin >> Matrix[i][j];
        }
    }

    fin.close();

    for (int c = 1; c <= Displacement; ++c)
    {
        for (int i = Displacement; i < m + Displacement; ++i)
        {
            Matrix[Displacement - c][i] = Matrix[Displacement][i];
            Matrix[n + Displacement - 1 + c][i] = Matrix[n + Displacement - 1][i];
        }
        for (int i = Displacement; i < n + Displacement; ++i)
        {
            Matrix[i][Displacement - c] = Matrix[i][Displacement];
            Matrix[i][m + Displacement - 1 + c] = Matrix[i][m + Displacement - 1];
        }
    }

    for (int p = 0; p < Displacement; ++p)
    {
        for (int q = 0; q < Displacement; ++q)
        {
            Matrix[p][q] = Matrix[Displacement][Displacement];
            Matrix[p][m + Displacement + q] = Matrix[Displacement][m + Displacement - 1];
            Matrix[n + Displacement + p][q] = Matrix[n + Displacement - 1][Displacement];
            Matrix[n + Displacement + p][m + Displacement + q] = Matrix[n + Displacement - 1][m + Displacement - 1];
        }
    }
}

void
PrintData(
    _In_ int   Displacement,
    _In_ int** ResultMatrix,
    _In_ bool  IsSequential
)
{
    char outputFileName[256] = "data.out";
    if (IsSequential)
    {
        strcat_s(outputFileName, ".sequential");
    }
    std::ofstream fout(outputFileName);

    for (int i = Displacement; i <= n + Displacement - 1; ++i)
    {
        for (int j = Displacement; j <= m + Displacement - 1; ++j)
        {
            fout << ResultMatrix[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
}

void
CalculateConvSequential(
    _In_ int                                   Displacement,
    _In_ int**                                 Matrix,
    _In_ int**                                 ConvMatrix,
    _In_ int                                   StartLine,
    _In_ int                                   StopLine,
    _In_ int                                   StartColumn,
    _In_ int                                   StopColumn,
    _In_ std::barrier<void(*)(void) noexcept>* Barrier = nullptr
)
{
    if (StartLine > StopLine)  // if we specify more threads than the total number of tasks then some threads may have taskCountForThread[threadId] = 0
    {                          // and therefore StartLine would be greater than StopLine
        return;
    }

    ThreadData threadData = { 0 };
    threadData.DataLineAbove = new int[m + Displacement * 2]();
    threadData.DataLineBelow = new int[m + Displacement * 2]();

    for (int j = StartColumn - Displacement; j <= StopColumn + Displacement; ++j)
    {
        threadData.DataLineAbove[j] = Matrix[StartLine - 1][j];
        threadData.DataLineBelow[j] = Matrix[StopLine + 1][j];
    }

    if (Barrier)
    {
        Barrier->arrive_and_wait();
    }

    for (int i = StartLine; i <= StopLine; ++i)
    {
        int valueFromLeft = Matrix[i][StartColumn - 1];
        for (int j = StartColumn; j <= StopColumn; ++j)
        {
            int matrixValue = 0;
            for (int p = i - Displacement; p < i + k - Displacement; ++p)
            {
                for (int q = j - Displacement; q < j + k - Displacement; ++q)
                {
                    int value = 0;
                    if (p == i && q == j - 1)  // use the value on the left before it was previously modified
                    {
                        value = valueFromLeft;
                    }
                    else if (p == i - 1)  // use the values above before they were modified
                    {
                        value = threadData.DataLineAbove[q];
                    }
                    else if (p == StopLine + 1)  // use the values below before they were modified
                    {
                        value = threadData.DataLineBelow[q];
                    }
                    else
                    {
                        value = Matrix[p][q];
                    }

                    matrixValue += value * ConvMatrix[p + Displacement - i][q + Displacement - j];
                }
            }

            threadData.DataLineAbove[j - 1] = valueFromLeft;
            valueFromLeft = Matrix[i][j];
            Matrix[i][j] = matrixValue;
        }

        threadData.DataLineAbove[StopColumn] = valueFromLeft;
        threadData.DataLineAbove[StopColumn + 1] = Matrix[i][StopColumn + 1];
    }

    delete[] threadData.DataLineAbove;
    delete[] threadData.DataLineBelow;
}

void
CalculateConvParralel(
    _In_ int   Displacement,
    _In_ int** Matrix,
    _In_ int** ConvMatrix
)
{
    int TotalNumberOfTasks = n;  // by default, a task is a line

    int taskCountPerThread = TotalNumberOfTasks / p;
    int remainder = TotalNumberOfTasks % p;
    int totalThreadCount = taskCountPerThread ? p : remainder;

    int taskCountForThread[MAX_P] = { 0 };
    for (int i = 0; i < p; ++i)
    {
        taskCountForThread[i] = taskCountPerThread;
    }

    bool taskIncreasedForThread[MAX_P] = { false };
    for (int i = 0; i < remainder; ++i)
    {
        int threadId = rand() % p;
        while (taskIncreasedForThread[threadId])
        {
            threadId = rand() % p;
        }
        taskIncreasedForThread[threadId] = true;
        ++taskCountForThread[threadId];
    }

    std::barrier<void(*)(void) noexcept>* barrier = new std::barrier<void(*)(void) noexcept>(totalThreadCount, []() noexcept {});
    std::thread threads[MAX_P]{ };
    int i = 1;
    int threadId = 0;
    int StartLine = i + Displacement - 1;
    int StopLine = i + Displacement - 1 + taskCountForThread[threadId] - 1;
    int StartColumn = Displacement;
    int StopColumn = m + Displacement - 1;

    while (i <= TotalNumberOfTasks)
    {
        StartLine = i + Displacement - 1;
        StopLine = i + Displacement - 1 + taskCountForThread[threadId] - 1;

        threads[threadId] = std::thread(CalculateConvSequential, Displacement, Matrix, ConvMatrix, StartLine, StopLine, StartColumn, StopColumn, barrier);

        i += taskCountForThread[threadId];
        ++threadId;
    }

    for (int i = 0; i < threadId; ++i)
    {
        threads[i].join();
    }

    delete barrier;
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cout << "Use <filename> <sequential/parralel> <p>\n";
        return -1;
    }

    const char* fileName = argv[1];
    bool isSequential = !strcmp(argv[2], "sequential");
    p = atoi(argv[3]);

    srand((unsigned int)time(NULL));

    int displacement = 0;

    int** matrix = new int* [MAX_LINES]();
    for (int i = 0; i < MAX_LINES; ++i)
    {
        matrix[i] = new int[MAX_COLUMNS]();
    }

    int** convMatrix = new int* [CONV_MAX_K]();
    for (int i = 0; i < CONV_MAX_K; ++i)
    {
        convMatrix[i] = new int[CONV_MAX_K]();
    }

    ReadInputData(displacement, matrix, convMatrix, fileName);

    if (isSequential)
    {
        CalculateConvSequential(displacement, matrix, convMatrix, displacement, n + displacement - 1, displacement, m + displacement - 1);
    }
    else
    {
        CalculateConvParralel(displacement, matrix, convMatrix);
    }

    PrintData(displacement, matrix, isSequential);

    for (int i = 0; i < CONV_MAX_K; ++i)
    {
        delete[] convMatrix[i];
    }
    delete[] convMatrix;

    for (int i = 0; i < MAX_LINES; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}