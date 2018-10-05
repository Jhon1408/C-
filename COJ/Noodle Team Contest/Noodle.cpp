#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define infinite 2147483647

void Merge(int A[], int p, int q, int r) {
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1 + 1], R[n2 + 1];

    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];

    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];

    L[n1 + 1] = infinite;
    R[n2 + 1] = infinite;
    i = 1;
    j = 1;

    for (k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void Merge_Sort(int A[], int p, int r) {
    if (p < r) {
        int q = floor((p + r) / 2);
        Merge_Sort(A, p, q);
        Merge_Sort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}
//-------------------------------------------------------------------------
int main()
{
    int n;
    int cookers, T1, T2;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cookers);
        int Q[cookers + 5], result, sum = 0;
        for (int i = 1; i <= cookers; i++) {
            scanf("%d %d", &T1, &T2);
            sum += T1;
            Q[i] = T2;
        }
        Merge_Sort(Q,1,cookers);
        sum += Q[1];
        printf("%d\n", sum);
    }
    return 0;
}
