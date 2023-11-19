#include <iostream>
#include <fstream>
#include <chrono>
#include <mpi.h> 

#define MAX_LINES       1010
#define MAX_COLUMNS     1010
#define CONV_K          3
#define MAX_P           21

struct ProcessData
{
    int* DataLineAbove;
    int* DataLineBelow;
};

void
ReadInputData(
    _Out_    int&  N,
    _Out_    int&  M,
    _Out_    int&  Displacement,
    _Outptr_ int** Matrix,
    _Outptr_ int** ConvMatrix,
    _In_     const char* FileName
)
{
    std::ifstream fin(FileName);

    for (int i = 0; i < CONV_K; ++i)
    {
        for (int j = 0; j < CONV_K; ++j)
        {
            fin >> ConvMatrix[i][j];
        }
    }

    fin >> N >> M;

    Displacement = CONV_K / 2;
    for (int i = Displacement; i < N + Displacement; ++i)
    {
        for (int j = Displacement; j < M + Displacement; ++j)
        {
            fin >> Matrix[i][j];
        }
    }

    fin.close();

    for (int c = 1; c <= Displacement; ++c)
    {
        for (int i = Displacement; i < M + Displacement; ++i)
        {
            Matrix[Displacement - c][i] = Matrix[Displacement][i];
            Matrix[N + Displacement - 1 + c][i] = Matrix[N + Displacement - 1][i];
        }
        for (int i = Displacement; i < N + Displacement; ++i)
        {
            Matrix[i][Displacement - c] = Matrix[i][Displacement];
            Matrix[i][M + Displacement - 1 + c] = Matrix[i][M + Displacement - 1];
        }
    }

    for (int p = 0; p < Displacement; ++p)
    {
        for (int q = 0; q < Displacement; ++q)
        {
            Matrix[p][q] = Matrix[Displacement][Displacement];
            Matrix[p][M + Displacement + q] = Matrix[Displacement][M + Displacement - 1];
            Matrix[N + Displacement + p][q] = Matrix[N + Displacement - 1][Displacement];
            Matrix[N + Displacement + p][M + Displacement + q] = Matrix[N + Displacement - 1][M + Displacement - 1];
        }
    }
}

void
PrintData(
    _In_ int   N,
    _In_ int   M,
    _In_ int   Displacement,
    _In_ int** ResultMatrix
)
{
    char outputFileName[256] = "data.out";
    std::ofstream fout(outputFileName);

    for (int i = Displacement; i <= N + Displacement - 1; ++i)
    {
        for (int j = Displacement; j <= M + Displacement - 1; ++j)
        {
            fout << ResultMatrix[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
}

void
CalculateConvSequential(
    _In_ int   Displacement,
    _In_ int** Matrix,
    _In_ int** ConvMatrix,
    _In_ int   StartLine,
    _In_ int   StopLine,
    _In_ int   StartColumn,
    _In_ int   StopColumn
)
{
    ProcessData processData = { 0 };
    processData.DataLineAbove = new int[MAX_COLUMNS + Displacement * 2]();
    processData.DataLineBelow = new int[MAX_COLUMNS + Displacement * 2]();

    for (int j = StartColumn - Displacement; j <= StopColumn + Displacement; ++j)
    {
        processData.DataLineAbove[j] = Matrix[StartLine - 1][j];
        processData.DataLineBelow[j] = Matrix[StopLine + 1][j];
    }

    for (int i = StartLine; i <= StopLine; ++i)
    {
        int valueFromLeft = Matrix[i][StartColumn - 1];
        for (int j = StartColumn; j <= StopColumn; ++j)
        {
            int matrixValue = 0;
            for (int p = i - Displacement; p < i + CONV_K - Displacement; ++p)
            {
                for (int q = j - Displacement; q < j + CONV_K - Displacement; ++q)
                {
                    int value = 0;
                    if (p == i && q == j - 1)  // use the value on the left before it was previously modified
                    {
                        value = valueFromLeft;
                    }
                    else if (p == i - 1)  // use the values above before they were modified
                    {
                        value = processData.DataLineAbove[q];
                    }
                    else if (p == StopLine + 1)  // use the values below before they were modified
                    {
                        value = processData.DataLineBelow[q];
                    }
                    else
                    {
                        value = Matrix[p][q];
                    }

                    matrixValue += value * ConvMatrix[p + Displacement - i][q + Displacement - j];
                }
            }

            processData.DataLineAbove[j - 1] = valueFromLeft;
            valueFromLeft = Matrix[i][j];
            Matrix[i][j] = matrixValue;
        }

        processData.DataLineAbove[StopColumn] = valueFromLeft;
        processData.DataLineAbove[StopColumn + 1] = Matrix[i][StopColumn + 1];
    }

    delete[] processData.DataLineAbove;
    delete[] processData.DataLineBelow;
}

int main(int argc, char** argv)
{
    const char* fileName = "d:\\facultate-repo\\sem5\\ppd\\lab 3\\utils\\data_1000_1000_3.in";

    int myid, numprocs, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME] = { 0 };

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // get current process id
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // get number of processes
    MPI_Get_processor_name(processor_name, &namelen);

    int** matrix = new int* [MAX_LINES]();
    for (int i = 0; i < MAX_LINES; ++i)
    {
        matrix[i] = new int[MAX_COLUMNS]();
    }

    int** convMatrix = new int* [CONV_K]();
    for (int i = 0; i < CONV_K; ++i)
    {
        convMatrix[i] = new int[CONV_K]();
    }

    int n, m, displacement;
    int startLine = 0;
    int stopLine = 0;
    int startColumn = 0;
    int stopColumn = 0;
    MPI_Status status;

    if (myid == 0)
    {
        // master code here
        ReadInputData(n, m, displacement, matrix, convMatrix, fileName);
    }

    for (int i = 0; i < CONV_K; ++i)
    {
        MPI_Bcast(convMatrix[i], CONV_K, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (myid == 0)
    {
        // master code here
        int totalNumberOfTasks = n;  // by default, a task is a line
        int taskCountPerProcess = totalNumberOfTasks / (numprocs - 1);

        int taskCountForProcess[MAX_P] = { 0 };
        for (int i = 1; i < numprocs; ++i)
        {
            taskCountForProcess[i] = taskCountPerProcess;
        }

        bool taskIncreasedForProcess[MAX_P] = { false };

        int i = 1;
        int processId = 1;
        startColumn = displacement;
        stopColumn = m + displacement - 1;

        while (i <= totalNumberOfTasks)
        {
            startLine = i + displacement - 1;
            stopLine = i + displacement - 1 + taskCountForProcess[processId] - 1;

            MPI_Send(&startLine, 1, MPI_INT, processId, 0, MPI_COMM_WORLD);
            MPI_Send(&stopLine, 1, MPI_INT, processId, 0, MPI_COMM_WORLD);
            MPI_Send(&startColumn, 1, MPI_INT, processId, 0, MPI_COMM_WORLD);
            MPI_Send(&stopColumn, 1, MPI_INT, processId, 0, MPI_COMM_WORLD);

            for (int p = startLine; p <= stopLine; ++p)
            {
                MPI_Send(matrix[p], stopColumn - startColumn + 3, MPI_INT, processId, 0, MPI_COMM_WORLD);
            }

            i += taskCountForProcess[processId];
            ++processId;
        }

        for (int i = 1; i < numprocs; ++i)
        {
            MPI_Send(&processId, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        MPI_Send(matrix[0], stopColumn - startColumn + 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(matrix[stopLine + 1], stopColumn - startColumn + 3, MPI_INT, processId - 1, 0, MPI_COMM_WORLD);

        double totalTimeTaken = 0;
        for (int i = 1; i < numprocs; ++i)
        {
            double timeTaken = 0;
            MPI_Recv(&timeTaken, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            totalTimeTaken += timeTaken;

            MPI_Recv(&startLine, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&stopLine, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&startColumn, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&stopColumn, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

            for (int p = startLine; p <= stopLine; ++p)
            {
                MPI_Recv(matrix[p] + startColumn, stopColumn - startColumn + 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            }
        }

        std::cout << totalTimeTaken;
        PrintData(n, m, displacement, matrix);
    }
    else
    {
        MPI_Recv(&startLine, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&stopLine, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&startColumn, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&stopColumn, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int p = startLine; p <= stopLine; ++p)
        {
            MPI_Recv(matrix[p], stopColumn - startColumn + 3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        }

        int processId = 0;
        MPI_Recv(&processId, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        if (myid == 1)
        {
            MPI_Recv(matrix[startLine - 1], stopColumn - startColumn + 3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        }
        if (myid == processId - 1)
        {
            MPI_Recv(matrix[stopLine + 1], stopColumn - startColumn + 3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        }

        if (myid % 2)
        {
            MPI_Send(matrix[stopLine], stopColumn - startColumn + 3, MPI_INT, myid + 1, 0, MPI_COMM_WORLD);
            if (myid > 1)
            {
                MPI_Recv(matrix[startLine - 1], stopColumn - startColumn + 3, MPI_INT, myid - 1, 0, MPI_COMM_WORLD, &status);
            }

            if (myid > 1)
            {
                MPI_Send(matrix[startLine], stopColumn - startColumn + 3, MPI_INT, myid - 1, 0, MPI_COMM_WORLD);
            }
            MPI_Recv(matrix[stopLine + 1], stopColumn - startColumn + 3, MPI_INT, myid + 1, 0, MPI_COMM_WORLD, &status);
        }
        else
        {
            MPI_Recv(matrix[startLine - 1], stopColumn - startColumn + 3, MPI_INT, myid - 1, 0, MPI_COMM_WORLD, &status);
            if (myid < processId - 1)
            {
                MPI_Send(matrix[stopLine], stopColumn - startColumn + 3, MPI_INT, myid + 1, 0, MPI_COMM_WORLD);
            }

            if (myid < processId - 1)
            {
                MPI_Recv(matrix[stopLine + 1], stopColumn - startColumn + 3, MPI_INT, myid + 1, 0, MPI_COMM_WORLD, &status);
            }
            MPI_Send(matrix[startLine], stopColumn - startColumn + 3, MPI_INT, myid - 1, 0, MPI_COMM_WORLD);
        }

        std::chrono::steady_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
        CalculateConvSequential(CONV_K / 2, matrix, convMatrix, startLine, stopLine, startColumn, stopColumn);
        std::chrono::steady_clock::time_point timeStop = std::chrono::high_resolution_clock::now();
        double elapsed_time_ns = std::chrono::duration<double>(timeStop - timeStart).count();

        MPI_Send(&elapsed_time_ns, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&startLine, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&stopLine, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&startColumn, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&stopColumn, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (int p = startLine; p <= stopLine; ++p)
        {
            MPI_Send(matrix[p] + startColumn, stopColumn - startColumn + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    for (int i = 0; i < CONV_K; ++i)
    {
        delete[] convMatrix[i];
    }
    delete[] convMatrix;

    for (int i = 0; i < MAX_LINES; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    MPI_Finalize();

    return 0;
}