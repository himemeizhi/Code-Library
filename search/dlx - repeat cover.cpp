#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXN 110
#define MAXM 1000000
#define INF 0x7FFFFFFF

using namespace std;

int G[MAXN][MAXN];
int L[MAXM], R[MAXM], U[MAXM], D[MAXM];
int size, ans, S[MAXM], H[MAXM], C[MAXM];
bool vis[MAXN * 100];
void Link(int r, int c)
{
    U[size] = c;
    D[size] = D[c];
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
    C[size++] = c;
}
void Remove(int c)
{
    int i;
    for (i = D[c]; i != c; i = D[i])
    {
        L[R[i]] = L[i];
        R[L[i]] = R[i];
    }
}
void Resume(int c)
{
    int i;
    for (i = D[c]; i != c; i = D[i])
        L[R[i]] = R[L[i]] = i;
}
int A()
{
    int i, j, k, res;
    memset(vis, false, sizeof(vis));
    for (res = 0, i = R[0]; i; i = R[i])
    {
        if (!vis[i])
        {
            res++;
            for (j = D[i]; j != i; j = D[j])
            {
                for (k = R[j]; k != j; k = R[k])
                    vis[C[k]] = true;
            }
        }
    }
    return res;
}
void Dance(int now)
{
    if (R[0] == 0)
        ans = min(ans, now);
    else if (now + A() < ans)
    {
        int i, j, temp, c;
        for (temp = INF,i = R[0]; i; i = R[i])
        {
            if (temp > S[i])
            {
                temp = S[i];
                c = i;
            }
        }
        for (i = D[c]; i != c; i = D[i])
        {
            Remove(i);
            for (j = R[i]; j != i; j = R[j])
                Remove(j);
            Dance(now + 1);
            for (j = L[i]; j != i; j = L[j])
                Resume(j);
            Resume(i);
        }
    }
}
void Init(int m)
{
    int i;
    for (i = 0; i <= m; i++)
    {
        R[i] = i + 1;
        L[i + 1] = i;
        U[i] = D[i] = i;
        S[i] = 0;
    }
    R[m] = 0;
    size = m + 1;
}
