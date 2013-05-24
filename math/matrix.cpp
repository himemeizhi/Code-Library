struct Matrix
{
    const int N(52);
    int a[N][N];
    inline Matrix operator*(const Matrix &b)const
    {
        static Matrixres;
        static int i,j,k;
        for(i=0;i<N;++i)
            for(j=0;j<N;++j)
            {
                res.a[i][j]=0;
                for(k=0;k<N;++k)
                    res.a[i][j]+=a[i][k]*b.a[k][j];
            }
        return res;
    }
    inline Matrix operator^(int y)const
    {
        static Matrix res,x;
        static int i,j;
        for(i=0;i<N;++i)
        {
            for(j=0;j<N;++j)
            {
                res.a[i][j]=0;
                x.a[i][j]=a[i][j];
            }
            res.a[i][i]=1;
        }
        for(;y;y>>=1,x=x*x)
            if(y&1)
                res=res*x;
        return res;
    }
};

Fibonacci Matrix
[1 1]
[1 0]
