#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2.Using dynamic memory allocation where is the case, solve the following:
// For a list of students, each having name, registration_number and 5 marks for current semester, 
// sort them in descending order of the average of the 5 marks, and display the students with identical average in alphabetical order.

#define N 3

typedef struct
{
    char* name;
    int reg_num;
    int* marks;
} student;

void sort(student* pstudent)
{
    float average[N];
    for (int i = 0; i < N; ++i)
    {
        int sum = 0;
        for (int j = 0; j < 5; ++j) sum += pstudent[i].marks[j];
        average[i] = sum / 5.0;
    }

    for (int i = 0; i < N - 1; ++i)
        for (int j = i + 1; j < N; ++j)
            if ((average[i] < average[j]) || (average[i] == average[j] && strcmp(pstudent[i].name, pstudent[j].name) > 0))
            {
                student swap = pstudent[i];
                pstudent[i] = pstudent[j];
                pstudent[j] = swap;
            }
}

int main()
{
    student* pstudent = malloc(N * sizeof(student));
    for (int i = 0; i < N; ++i)
    {
        pstudent[i].name = malloc(26 * sizeof(char));
        scanf("%s", pstudent[i].name);

        pstudent[i].reg_num = i + 1;

        pstudent[i].marks = malloc(5 * sizeof(int));
        for (int j = 0; j < 5; ++j)
            scanf("%d", &pstudent[i].marks[j]);
    }

    sort(pstudent);

    for (int i = 0; i < N; ++i)
    {
        printf("#%d ID: %d Nume: %s | Note: ", i + 1, pstudent[i].reg_num, pstudent[i].name);
        for (int j = 0; j < 5; ++j)
            printf("%d ", pstudent[i].marks[j]);
        printf("\n");

        free(pstudent[i].name);
        free(pstudent[i].marks);
    }

    free(pstudent);

    return 0;
}