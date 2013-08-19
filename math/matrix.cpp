struct Matrix
{
    const int N(52);
    int a[N][N];
    inline Matrix operator*(const Matrix &b)const //`比照着公式来会快一点常数…… qnmlgb的zoj3289……`
    {
        static Matrix re;
        static int i,j,k;
        for(i=0;i<n;++i)
            for(j=0;j<n;++j)
                re.a[i][j]=0;
        for(k=0;k<n;++k)
            for(i=0;i<n;++i)
                if(a[i][k])
                    for(j=0;j<n;++j)
                        if(b.a[k][j])
                            re.a[i][j]=(re.a[i][j]+a[i][k]*b.a[k][j])%mod;
        return re;
    }
    inline Matrix operator^(int y)const
    {
        static Matrix re,x;
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
        return re;
    }
};

Fibonacci Matrix
`$\begin{matrix}
1 & 1\\
      1 & 0
      \end{matrix}$`
