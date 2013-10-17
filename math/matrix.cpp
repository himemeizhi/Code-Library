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

int inv(mat& a)
{
    int i,j,k,is[MAXN],js[MAXN];
    double t;
    if (a.n!=a.m)
        return 0;
    for (k=0;k<a.n;k++)
    {
        for (t=0,i=k;i<a.n;i++)
            for (j=k;j<a.n;j++)
                if (fabs(a.data[i][j])>t)
                    t=fabs(a.data[is[k]=i][js[k]=j]);
        if (zero(t))
            return 0;
        if (is[k]!=k)
            for (j=0;j<a.n;j++)
                t=a.data[k][j],a.data[k][j]=a.data[is[k]][j],a.data[is[k]][j]=t;
        if (js[k]!=k)
            for (i=0;i<a.n;i++)
                t=a.data[i][k],a.data[i][k]=a.data[i][js[k]],a.data[i][js[k]]=t;
        a.data[k][k]=1/a.data[k][k];
        for (j=0;j<a.n;j++)
            if (j!=k)
                a.data[k][j]*=a.data[k][k];
        for (i=0;i<a.n;i++)
            if (i!=k)
                for (j=0;j<a.n;j++)
                    if (j!=k)
                        a.data[i][j]-=a.data[i][k]*a.data[k][j];
        for (i=0;i<a.n;i++)
            if (i!=k)
                a.data[i][k]*=-a.data[k][k];
    }
    for (k=a.n-1;k>=0;k--)
    {
        for (j=0;j<a.n;j++)
            if (js[k]!=k)
                t=a.data[k][j],a.data[k][j]=a.data[js[k]][j],a.data[js[k]][j]=t;
        for (i=0;i<a.n;i++)
            if (is[k]!=k)
                t=a.data[i][k],a.data[i][k]=a.data[i][is[k]],a.data[i][is[k]]=t;
    }
    return 1;
}
double det(const mat& a)
{
    int i,j,k,sign=0;
    double b[MAXN][MAXN],ret=1,t;
    if (a.n!=a.m)
        return 0;
    for (i=0;i<a.n;i++)
        for (j=0;j<a.m;j++)
            b[i][j]=a.data[i][j];
    for (i=0;i<a.n;i++)
    {
        if (zero(b[i][i]))
        {
            for (j=i+1;j<a.n;j++)
                if (!zero(b[j][i]))
                    break;
            if (j==a.n)
                return 0;
            for (k=i;k<a.n;k++)
                t=b[i][k],b[i][k]=b[j][k],b[j][k]=t;
            sign++;
        }
        ret*=b[i][i];
        for (k=i+1;k<a.n;k++)
            b[i][k]/=b[i][i];
        for (j=i+1;j<a.n;j++)
            for (k=i+1;k<a.n;k++)
                b[j][k]-=b[j][i]*b[i][k];
    }
    if (sign&1)
        ret=-ret;
    return ret;
}

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
