#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define NA 7
#define NB 4

int matrix_A[NA + (NB - 1)][NA + (NB - 1)];
int matrix_B[NB][NB];
int output_matrix[NA][NA];

struct thread_args
{
    int i;
    int j;
};

void *calculate_sum(void *_args)
{
    struct thread_args *args = (struct thread_args *)_args;
    int sum = 0;
    for (int m = 0; m < NB; m++)
    {
        for (int n = 0; n < NB; n++)
        {
            sum += matrix_A[m + args->i][n + args->j] * matrix_B[m][n];
        }
    }
    output_matrix[args->i][args->j] = sum;
    free(args);
    pthread_exit(NULL);
}

void print_result()
{
    printf("Output Matrix:\n\n");
    for (int i = 0; i < NA; i++)
    {
        for (int j = 0; j < NA; j++)
        {
            printf("%d\t", output_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("---------------------------------------------------");
    printf("\n");
}

int main()
{
    srand(time(0));
    const int MIN = 1, MAX = 9;
    pthread_t th[NA * NA];

    // Fill matrix A
    for (int i = 0; i < NA + (NB - 1); i++)
    {
        for (int j = 0; j < NA + (NB - 1); j++)
        {
            if (i < NA && j < NA)
            {
                int randomNumber = rand() % (MAX + 1 - MIN) + MIN;
                matrix_A[i][j] = randomNumber;
            }
            else
            {
                matrix_A[i][j] = 0;
            }
        }
    }

    // Fill matrix B
    for (int i = 0; i < NB; i++)
    {
        for (int j = 0; j < NB; j++)
        {
            int randomNumber = rand() % (MAX + 1 - MIN) + MIN;
            matrix_B[i][j] = randomNumber;
        }
    }

    // Fill output matrix
    for (int i = 0; i < NA; i++)
    {
        for (int j = 0; j < NA; j++)
        {
            output_matrix[i][j] = -1;
        }
    }

    printf("\nMatrix A:\n\n");

    // Print matrix A
    for (int i = 0; i < NA; i++)
    {
        for (int j = 0; j < NA; j++)
        {
            printf("%d\t", matrix_A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n\n");

    // Print matrix B
    for (int i = 0; i < NB; i++)
    {
        for (int j = 0; j < NB; j++)
        {
            printf("%d\t", matrix_B[i][j]);
        }
        printf("\n");
    }

    printf("\nOutput Matrix:\n\n");

    // Print output matrix
    for (int i = 0; i < NA; i++)
    {
        for (int j = 0; j < NA; j++)
        {
            printf("%d\t", output_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("---------------------------------------------------");
    printf("\n");

    // Calculate result
    for (int i = 0; i < NA; i++)
    {
        for (int j = 0; j < NA; j++)
        {
            struct thread_args *args = malloc(sizeof(struct thread_args));
            args->i = i;
            args->j = j;
            printf("\n");
            pthread_create(&th[i + j], NULL, calculate_sum, args);
            printf("Thread (%d, %d) has started.\n", i, j);
            pthread_join(th[i + j], NULL);
            printf("Thread (%d, %d) has finished execution.\n\n", i, j);
            print_result();
        }
    }
}
