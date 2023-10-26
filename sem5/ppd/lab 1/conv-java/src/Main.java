import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

public class Main
{
    static final int MAX_LINES = 10010;
    static final int MAX_COLUMNS = 10010;
    static final int CONV_MAX_K = 5;
    static final int MAX_P = 16;

    static int n, m, k, p;

    public static int ReadInputData(int[][] matrix, int[][] convMatrix, String fileName) throws FileNotFoundException
    {
        Scanner scanner = new Scanner(new File(fileName));
        k = scanner.nextInt();
        int displacement = k / 2;

        for (int i = 0; i < k; ++i)
        {
            for (int j = 0; j < k; ++j)
            {
                convMatrix[i][j] = scanner.nextInt();
            }
        }

        n = scanner.nextInt();
        m = scanner.nextInt();

        for (int i = displacement; i < n + displacement; ++i)
        {
            for (int j = displacement; j < m + displacement; ++j)
            {
                matrix[i][j] = scanner.nextInt();
            }
        }

        for (int c = 1; c <= displacement; ++c)
        {
            for (int i = displacement; i < m + displacement; ++i)
            {
                matrix[displacement - c][i] = matrix[displacement][i];
                matrix[n + displacement - 1 + c][i] = matrix[n + displacement - 1][i];
            }
            for (int i = displacement; i < n + displacement; ++i)
            {
                matrix[i][displacement - c] = matrix[i][displacement];
                matrix[i][m + displacement - 1 + c] = matrix[i][m + displacement - 1];
            }
        }

        for (int p = 0; p < displacement; ++p)
        {
            for (int q = 0; q < displacement; ++q)
            {
                matrix[p][q] = matrix[displacement][displacement];
                matrix[p][m + displacement + q] = matrix[displacement][m + displacement - 1];
                matrix[n + displacement + p][q] = matrix[n + displacement - 1][displacement];
                matrix[n + displacement + p][m + displacement + q] = matrix[n + displacement - 1][m + displacement - 1];
            }
        }

        scanner.close();

        return displacement;
    }

    public static void PrintData(int displacement, int[][] resultMatrix, boolean isSequential) throws FileNotFoundException
    {
        String outputFileName = "data.out";
        if (isSequential)
        {
            outputFileName += ".sequential";
        }

        PrintWriter writer = new PrintWriter(outputFileName);
        for (int i = displacement; i <= n + displacement - 1; ++i)
        {
            for (int j = displacement; j <= m + displacement - 1; ++j)
            {
                writer.print(resultMatrix[i][j] + " ");
            }
            writer.println();
        }
        writer.close();
    }

    public static void CalculateConvSequential(int[][] resultMatrix, int displacement, int[][] matrix, int[][] convMatrix, int startLine, int stopLine, int startColumn, int stopColumn)
    {
        for (int i = startLine; i <= stopLine; ++i)
        {
            for (int j = startColumn; j <= stopColumn; ++j)
            {
                for (int p = i - displacement; p < i + k - displacement; ++p)
                {
                    for (int q = j - displacement; q < j + k - displacement; ++q)
                    {
                        resultMatrix[i][j] += matrix[p][q] * convMatrix[p + displacement - i][q + displacement - j];
                    }
                }
            }
        }
    }

    public static void CalculateConvParallel(int[][] ResultMatrix, int Displacement, int[][] Matrix, int[][] ConvMatrix, boolean CountColumnAsTask)
    {
        int TotalNumberOfTasks = n;  // by default, a task is a line
        if (CountColumnAsTask)
        {
            TotalNumberOfTasks = m;
        }

        int taskCountPerThread = TotalNumberOfTasks / p;
        int remainder = TotalNumberOfTasks % p;
        int[] taskCountForThread = new int[MAX_P];
        for (int i = 0; i < p; ++i)
        {
            taskCountForThread[i] = taskCountPerThread;
        }

        boolean[] taskIncreasedForThread = new boolean[MAX_P];
        Random rand = new Random();
        for (int i = 0; i < remainder; ++i)
        {
            int threadId = rand.nextInt(p);
            while (taskIncreasedForThread[threadId])
            {
                threadId = rand.nextInt(p);
            }
            taskIncreasedForThread[threadId] = true;
            ++taskCountForThread[threadId];
        }

        Thread[] threads = new Thread[MAX_P];
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

            int finalStartLine = StartLine;
            int finalStopLine = StopLine;
            int finalStartColumn = StartColumn;
            int finalStopColumn = StopColumn;
            threads[threadId] = new Thread(() -> CalculateConvSequential(ResultMatrix, Displacement, Matrix, ConvMatrix, finalStartLine, finalStopLine, finalStartColumn, finalStopColumn));
            threads[threadId].start();

            i += taskCountForThread[threadId];
            ++threadId;
        }

        for (i = 0; i < threadId; ++i)
        {
            try
            {
                threads[i].join();
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws Exception
    {
        if (args.length != 4)
        {
            System.out.println("Use <filename> <sequential/parallel> <p> <line/column>");
            return;
        }

        String fileName = args[0];
        boolean isSequential = args[1].equals("sequential");
        p = Integer.parseInt(args[2]);
        boolean countColumnAsTask = args[3].equals("column");

        int[][] matrix = new int[MAX_LINES][MAX_COLUMNS];
        int[][] convMatrix = new int[CONV_MAX_K][CONV_MAX_K];
        int[][] resultMatrix = new int[MAX_LINES][MAX_COLUMNS];

        int displacement = ReadInputData(matrix, convMatrix, fileName);

        if (isSequential)
        {
            CalculateConvSequential(resultMatrix, displacement, matrix, convMatrix, displacement, n + displacement - 1, displacement, m + displacement - 1);
        }
        else
        {
            CalculateConvParallel(resultMatrix, displacement, matrix, convMatrix, countColumnAsTask);
        }

        PrintData(displacement, resultMatrix, isSequential);
    }
}