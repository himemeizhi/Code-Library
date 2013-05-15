//矩阵快速幂
struct Matrix
{
    int a[52][52];
    Matrix operator * (const Matrix &b)const
    {
        Matrix res;
        for (int i = 0; i < 52; i++)
            for (int j = 0; j < 52; j++)
            {
                res.a[i][j] = 0;
                for (int k = 0; k < 52; k++)
                    res.a[i][j] += a[i][k] * b.a[k][j];
            }
        return res;
    }
    Matrix operator ^ (int y)const
    {
        Matrix res, x;
        for (int i = 0; i < 52; i++)
        {
            for (int j = 0; j < 52; j++)
                res.a[i][j] = 0, x.a[i][j] = a[i][j];
            res.a[i][i] = 1;
        }
        for (; y; y >>= 1, x = x * x)
            if (y & 1)
                res = res * x;
        return res;
    }
};
