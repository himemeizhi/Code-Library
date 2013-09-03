template<int n>class Matrix
{
    long long a[n][n];
    inline Matrix<n> operator*(const Matrix<n> &b)const //`比照着公式来会快一点常数…… nmlgb的zoj3289……`
    {
        //`别忘了矩阵乘法虽然满足结合律但是不满足交换律……`
        static Matrix<n> re;
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
    inline Matrix<n> operator^(int y)const
    {
        static Matrix<n> re,x;
        static int i,j;
        for(i=0;i<n;++i)
        {
            for(j=0;j<n;++j)
            {
                re.a[i][j]=0;
                x.a[i][j]=a[i][j];
            }
            re.a[i][i]=1;
        }
        for(;y;y>>=1,x=x*x)
            if(y&1)
                re=re*x;
        return re;
    }
    long long det()
    {
        static int i,j,k;
        static long long ret,t;
        ret=1ll;
        for(i=0;i<n;++i)
            for(j=0;j<n;++j)
                a[i][j]%=mod;
        for(i=0;i<n;++i)
        {
            for(j=i+1;j<n;++j)
                while(a[j][i])
                {
                    t=a[i][i]/a[j][i];
                    for(k=i;k<n;++k)
                        a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                    for(k=i;k<n;++k)
                        std::swap(a[i][k],a[j][k]);
                    ret=-ret;
                }
            if(!a[i][i])
                return 0ll;
            ret=ret*a[i][i]%mod;
        }
        return (ret+mod)%mod;
    }
};

/*
Fibonacci Matrix
`$\begin{matrix}
1 & 1\\
      1 & 0
      \end{matrix}$`

org[0][j], trans[i][j]
 means
transform(org,1 times) -> org[0][j]=`$\sum\limits_{i=0}^n org[0][i]\times trans[i][j]$`
      */
