// not tested yet
#include<cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

#define min(a,b) (a>b?b:a)

long long d[10000], num[10000], dnm[10000];
long long i, p;
long long l1, l2;

void rr(double num)
{
    int sub = floor(num);
    d[i++] = sub;
    if (sub == num)
        return;
    if (i > 2000)
        return;
    rr(1 / (num - sub));
}

long long numerator(int n)
{
    if (num[n] != 0)
        return num[n];
    long long i = -1;
    if (n == 0)
        i = d[0];
    else
        if (n == 1)
            i = d[0] * d[1] + 1;
        else
            i =  numerator(n - 1) * d[n] + numerator(n - 2);
    num[n] = i;
    return i;

    if (i > p)
    {
        l1 = n - 1;
        i = 0;
        num[n] = 0;
    }
    else
        num[n] = i;
    return i;
}

long long denominator(int n)
{
    if (dnm[n] != 0)
        return dnm[n];
    long long i = -1;
    if (n == 0)
        i = 1;
    else 
        if (n == 1)
            i = d[1];
        else 
            i = denominator(n - 1) * d[n] + denominator(n - 2);
    dnm[n] = i;
    return i;

    if (i > p)
    {
        l2 = n - 1;
        i = 0;
        dnm[n] = 0;
    }
    else
        dnm[n] = i;
    return i;
}

int main()
{
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        if (n == 0)
            return 0;

        memset(num, 0, sizeof num);
        memset(dnm, 0, sizeof dnm);

        i = 0;
        rr(sqrt((double)n));

        numerator(25); 
        denominator(25);

        int f;
        for (f = 0; f < 25; ++f)
            printf("%lld/%lld\n",num[f],dnm[f]);
    }
    return 0;
}
