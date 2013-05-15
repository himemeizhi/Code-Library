const int PermSize = 12;
int fac[PermSize] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800};

inline int Cantor(int a[])
{
    int i, j, cnt;
    int res = 0;
    for (i = 0; i < PermSize; ++i)
    {
        cnt = 0;
        for (j = i + 1; j < PermSize; ++j)
            if (a[i] > a[j])
                ++cnt;
        res = res + cnt * fac[PermSize - i - 1];
    }
    return res;
}

bool h[13];

inline void UnCantor(int x, int res[])
{
    int i,j,l,t;
    for (i = 1;i <= 12;i++)
        h[i] = false;
    for (i = 1; i <= 12; i++)
    {
        t = x / fac[12 - i];
        x -= t * fac[12 - i];
        for (j = 1, l = 0; l <= t; j++)
            if (!h[j])
                l++;
        j--;
        h[j] = true;
        res[i - 1] = j;
    }
}
