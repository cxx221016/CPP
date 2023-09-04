/*
* author 崔向向
* ID 521021911118
*/

/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define SIZE 17
/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 )
    {
        int _0, _1, _2, _3, _4, _5, _6, _7;

        for (int m = 0; m < 32; m += 8)
        {
            for (int n = 0; n < 32; n += 8)
            {
                if (m != n)
                {
                    for (int i = m; i < m + 8; ++i)
                    {
                        for (int j = n; j < n + 8; ++j)
                        {
                            B[j][i] = A[i][j];
                        }
                    }
                }
                else
                {
                    for (int i = m; i < m + 8; ++i)
                    {
                        _0 = A[i][n];
                        _1 = A[i][n + 1];
                        _2 = A[i][n + 2];
                        _3 = A[i][n + 3];
                        _4 = A[i][n + 4];
                        _5 = A[i][n + 5];
                        _6 = A[i][n + 6];
                        _7 = A[i][n + 7];

                        B[i][n] = _0;
                        B[i][n + 1] = _1;
                        B[i][n + 2] = _2;
                        B[i][n + 3] = _3;
                        B[i][n + 4] = _4;
                        B[i][n + 5] = _5;
                        B[i][n + 6] = _6;
                        B[i][n + 7] = _7;
                    }

                    for (int i = m; i < m + 8; ++i)
                    {
                        for (int j = n + (i - m + 1); j < n + 8; ++j)
                        {
                            if (i != j)
                            {
                                _0 = B[i][j];
                                B[i][j] = B[j][i];
                                B[j][i] = _0;
                            }
                        }
                    }
                }
            }
        }
    }

    if (M == 64 )
    { 
        int t, _0, _1, _2, _3, _4, _5, _6, _7;
        for (int i = 0; i < M; i += 8)
            for (int j = 0; j < N; j += 8) // blocking
            {
                //leftup
                for (t = i; t < i + 4; ++t)
                {
                    _0 = A[t][j];
                    _1 = A[t][j + 1];
                    _2 = A[t][j + 2];
                    _3 = A[t][j + 3];
                    _4 = A[t][j + 4];
                    _5 = A[t][j + 5];
                    _6 = A[t][j + 6];
                    _7 = A[t][j + 7];

                    B[j][t] = _0;
                    B[j + 1][t] = _1;
                    B[j + 2][t] = _2;
                    B[j + 3][t] = _3;
                    B[j][t + 4] = _4;
                    B[j + 1][t + 4] = _5;
                    B[j + 2][t + 4] = _6;
                    B[j + 3][t + 4] = _7;
                }
                //leftdown rightup
                for (t = j; t < j + 4; ++t)
                {
                    _0 = A[i + 4][t];
                    _1 = A[i + 5][t];
                    _2 = A[i + 6][t];
                    _3 = A[i + 7][t];
                    _4 = B[t][i + 4];
                    _5 = B[t][i + 5];
                    _6 = B[t][i + 6];
                    _7 = B[t][i + 7];

                    B[t][i + 4] = _0;
                    B[t][i + 5] = _1;
                    B[t][i + 6] = _2;
                    B[t][i + 7] = _3;
                    B[t + 4][i] = _4;
                    B[t + 4][i + 1] = _5;
                    B[t + 4][i + 2] = _6;
                    B[t + 4][i + 3] = _7;
                }
                //rightdown
                for (t = i + 4; t < i + 8; ++t)
                {
                    _0 = A[t][j + 4];
                    _1 = A[t][j + 5];
                    _2 = A[t][j + 6];
                    _3 = A[t][j + 7];
                    B[j + 4][t] = _0;
                    B[j + 5][t] = _1;
                    B[j + 6][t] = _2;
                    B[j + 7][t] = _3;
                }
            }
    }
    else if (M == 61)
    {
        for (int m = 0; m < 67; m += 17)
        {
            for (int n = 0; n < 61; n += 4)
            {
                for (int i = m; i < min(m + 17, 67); ++i)
                {
                    for (int j = n; j < min(n + 4, 61); ++j)
                    {
                        B[j][i] = A[i][j];
                    }
                }
            }
        }
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_simple_desc[] = "Baseline: Simple row-wise scan transpose";
void trans_simple(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
