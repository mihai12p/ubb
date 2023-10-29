#include <iostream>
#include <fstream>
#include <thread>

#define MAX_LINES       1010
#define MAX_COLUMNS     1010
#define CONV_MAX_K      5
#define MAX_P           16

int n, m, k, p;

void
ReadInputDataStatic(
    _Inout_  int&        Displacement,
    _Outptr_ int         Matrix[][MAX_COLUMNS],
    _Outptr_ int         ConvMatrix[][CONV_MAX_K],
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
ReadInputDataDynamic(
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
PrintDataStatic(
    _In_ int  Displacement,
    _In_ int  ResultMatrix[][MAX_COLUMNS],
    _In_ bool IsSequential
)
{
    char outputFileName[256] = "data.out";
    if (IsSequential)
    {
        strcat_s(outputFileName, ".sequential");
    }
    std::ofstream fout("data.out");

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
PrintDataDynamic(
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
}

void
CalculateConvSequentialStatic(
    _Outptr_ int ResultMatrix[][MAX_COLUMNS],
    _In_     int Displacement,
    _In_     int Matrix[][MAX_COLUMNS],
    _In_     int ConvMatrix[][CONV_MAX_K],
    _In_     int StartLine,
    _In_     int StopLine,
    _In_     int StartColumn,
    _In_     int StopColumn
)
{
    for (int i = StartLine; i <= StopLine; ++i)
    {
        for (int j = StartColumn; j <= StopColumn; ++j)
        {
            for (int p = i - Displacement; p < i + k - Displacement; ++p)
            {
                for (int q = j - Displacement; q < j + k - Displacement; ++q)
                {
                    ResultMatrix[i][j] += Matrix[p][q] * ConvMatrix[p + Displacement - i][q + Displacement - j];
                }
            }
        }
    }
}

void
CalculateConvSequentialDynamic(
    _Outptr_ int** ResultMatrix,
    _In_     int   Displacement,
    _In_     int** Matrix,
    _In_     int** ConvMatrix,
    _In_     int   StartLine,
    _In_     int   StopLine,
    _In_     int   StartColumn,
    _In_     int   StopColumn
)
{
    for (int i = StartLine; i <= StopLine; ++i)
    {
        for (int j = StartColumn; j <= StopColumn; ++j)
        {
            for (int p = i - Displacement; p < i + k - Displacement; ++p)
            {
                for (int q = j - Displacement; q < j + k - Displacement; ++q)
                {
                    ResultMatrix[i][j] += Matrix[p][q] * ConvMatrix[p + Displacement - i][q + Displacement - j];
                }
            }
        }
    }
}

void
CalculateConvParralelStatic(
    _Outptr_ int  ResultMatrix[][MAX_COLUMNS],
    _In_     int  Displacement,
    _In_     int  Matrix[][MAX_COLUMNS],
    _In_     int  ConvMatrix[][CONV_MAX_K],
    _In_     bool CountColumnAsTask
)
{
    int TotalNumberOfTasks = n;  // by default, a task is a line
    if (CountColumnAsTask)
    {
        TotalNumberOfTasks = m;
    }

    int taskCountPerThread = TotalNumberOfTasks / p;
    int remainder = TotalNumberOfTasks % p;
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

    std::thread threads[MAX_P]{ };
    int i = 1;
    int threadId = 0;

    while (i <= TotalNumberOfTasks)
    {
        int StartLine = i + Displacement - 1;
        int StopLine = i + Displacement - 1 + taskCountForThread[threadId] - 1;
        int StartColumn = Displacement;
        int StopColumn = m + Displacement - 1;

        if (CountColumnAsTask)
        {
            StartLine = Displacement;
            StopLine = n + Displacement - 1;
            StartColumn = i + Displacement - 1;
            StopColumn = i + Displacement - 1 + taskCountForThread[threadId] - 1;
        }

        threads[threadId] = std::thread(CalculateConvSequentialStatic, ResultMatrix, Displacement, Matrix, ConvMatrix, StartLine, StopLine, StartColumn, StopColumn);

        i += taskCountForThread[threadId];
        ++threadId;
    }

    for (int i = 0; i < threadId; ++i)
    {
        threads[i].join();
    }
}

void
CalculateConvParralelDynamic(
    _Outptr_ int** ResultMatrix,
    _In_     int   Displacement,
    _In_     int** Matrix,
    _In_     int** ConvMatrix,
    _In_     bool  CountColumnAsTask
)
{
    int TotalNumberOfTasks = n;  // by default, a task is a line
    if (CountColumnAsTask)
    {
        TotalNumberOfTasks = m;
    }

    int taskCountPerThread = TotalNumberOfTasks / p;
    int remainder = TotalNumberOfTasks % p;
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

    std::thread threads[MAX_P]{ };
    int i = 1;
    int threadId = 0;

    while (i <= TotalNumberOfTasks)
    {
        int StartLine = i + Displacement - 1;
        int StopLine = i + Displacement - 1 + taskCountForThread[threadId] - 1;
        int StartColumn = Displacement;
        int StopColumn = m + Displacement - 1;

        if (CountColumnAsTask)
        {
            StartLine = Displacement;
            StopLine = n + Displacement - 1;
            StartColumn = i + Displacement - 1;
            StopColumn = i + Displacement - 1 + taskCountForThread[threadId] - 1;
        }

        threads[threadId] = std::thread(CalculateConvSequentialDynamic, ResultMatrix, Displacement, Matrix, ConvMatrix, StartLine, StopLine, StartColumn, StopColumn);

        i += taskCountForThread[threadId];
        ++threadId;
    }

    for (int i = 0; i < threadId; ++i)
    {
        threads[i].join();
    }
}

int main(int argc, char** argv)
{
    if (argc != 6)
    {
        std::cout << "Use <filename> <static/dynamic> <sequential/parralel> <p> <line/column>\n";
        return -1;
    }

    const char* fileName = argv[1];
    bool isStatic = !strcmp(argv[2], "static");
    bool isSequential = !strcmp(argv[3], "sequential");
    p = atoi(argv[4]);
    bool countColumnAsTask = !strcmp(argv[5], "column");

    srand((unsigned int)time(NULL));

    int displacement = 0;

    if (isStatic)
    {
        int matrix[MAX_LINES][MAX_COLUMNS] = { 0 };
        int convMatrix[CONV_MAX_K][CONV_MAX_K] = { 0 };
        int resultMatrix[MAX_LINES][MAX_COLUMNS] = { 0 };

        ReadInputDataStatic(displacement, matrix, convMatrix, fileName);

        if (isSequential)
        {
            CalculateConvSequentialStatic(resultMatrix, displacement, matrix, convMatrix, displacement, n + displacement - 1, displacement, m + displacement - 1);
        }
        else
        {
            CalculateConvParralelStatic(resultMatrix, displacement, matrix, convMatrix, countColumnAsTask);
        }

        PrintDataStatic(displacement, resultMatrix, isSequential);
    }
    else
    {
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

        int** resultMatrix = new int* [MAX_LINES]();
        for (int i = 0; i < MAX_LINES; ++i)
        {
            resultMatrix[i] = new int[MAX_COLUMNS]();
        }

        ReadInputDataDynamic(displacement, matrix, convMatrix, fileName);

        if (isSequential)
        {
            CalculateConvSequentialDynamic(resultMatrix, displacement, matrix, convMatrix, displacement, n + displacement - 1, displacement, m + displacement - 1);
        }
        else
        {
            CalculateConvParralelDynamic(resultMatrix, displacement, matrix, convMatrix, countColumnAsTask);
        }

        PrintDataDynamic(displacement, resultMatrix, isSequential);

        for (int i = 0; i < MAX_LINES; ++i)
        {
            delete[] resultMatrix[i];
        }
        delete[] resultMatrix;

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
    }

    return 0;
}