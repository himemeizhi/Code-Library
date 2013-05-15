#include<cstdio>

#define INF 0x7FFFFFFF
#define MAXN 1000010

int n, m, size;
int L[MAXN], R[MAXN], U[MAXN], D[MAXN], H[MAXN];
int S[MAXN], C[MAXN], X[MAXN], Q[MAXN];

void Init()
{
    int i;
    for (i = 0; i <= m; i++)
    {
        S[i] = 0;
        L[i + 1] = i;
        R[i] = i + 1;
        U[i] = D[i] = i;
    }
    R[m] = 0;
    size = m + 1;
}
void Remove(int c)
{
    int i, j;
    R[L[c]] = R[c];
    L[R[c]] = L[c];
    for (i = D[c]; i != c; i = D[i])
    {
        for (j = R[i]; j != i; j = R[j])
        {
            D[U[j]] = D[j];
            U[D[j]] = U[j];
            S[C[j]]--;
        }
    }
}
void Resume(int c)
{
    int i, j;
    R[L[c]] = c;
    L[R[c]] = c;
    for (i = D[c]; i != c; i = D[i])
    {
        for (j = R[i]; j != i; j = R[j])
        {
            U[D[j]] = j;
            D[U[j]] = j;
            S[C[j]]++;
        }
    }
}
void Link(int r, int c)
{
    D[size] = D[c];
    U[size] = c;
    U[D[c]] = size;
    D[c] = size;
    if (H[r] < 0)
        H[r] = L[size] = R[size] = size;
    else
    {
        L[size] = H[r];
        R[size] = R[H[r]];
        L[R[H[r]]] = size;
        R[H[r]] = size;
    }
    S[c]++;
    C[size] = c;
    X[size++] = r;
}
bool Dance(int now)
{
    int i, j, c, temp;
    if (R[0] == 0)
        return true;
    for (temp = INF, i = R[0]; i; i = R[i])
    {
        if (S[i] < temp)
        {
            c = i;
            temp = S[i];
        }
    }
    Remove(c);
    for (i = D[c]; i != c; i = D[i])
    {
        for (j = R[i]; j != i; j = R[j])
            Remove(C[j]);
        if (Dance(now + 1))
            return true;
        for (j = L[i]; j != i; j = L[j])
            Resume(C[j]);
    }
    Resume(c);
    return false;
}
