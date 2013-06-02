#define N

inline int ge(int a[N][N],int n) // 返回系数矩阵的秩
{
    static int i,j,k,l;
    for(j=i=0;j<n;++j) //第i行,第j列
    {
        for(k=i;k<n;++k)
            if(a[k][j])
                break;
        if(k==n)
            continue;
        for(l=0;l<=n;++l)
            std::swap(a[i][l],a[k][l]);
        for(l=0;l<=n;++l)
            if(l!=i && a[l][j])
                for(k=0;k<=n;++k)
                    a[l][k]^=a[i][k];
        ++i;
    }
    for(j=i;j<n;++j)
        if(a[j][n])
            return -1; //无解
    return i;
}
/*
 */

void dfs(int v)
{
    if(v==n)
    {
        static int x[MAXX],ta[MAXX][MAXX];
        static int tmp;
        memcpy(x,ans,sizeof(x));
        memcpy(ta,a,sizeof(ta));
        for(i=l-1;i>=0;--i)
        {
            for(j=i+1;j<n;++j)
                ta[i][n]^=(x[j]&&ta[i][j]); //迭代消元求解
            x[i]=ta[i][n];
        }
        for(tmp=i=0;i<n;++i)
            if(x[i])
                ++tmp;
        cnt=std::min(cnt,tmp);
        return;
    }
    ans[v]=0;
    dfs(v+1);
    ans[v]=1;
    dfs(v+1);
}

inline int ge(int a[N],[N],int n)
{
    static int i,j,k,l;
    for(i=j=0;j<n;++j)
    {
        for(k=i;k<n;++k)
            if(a[k][i])
                break;
        if(k<n)
        {
            for(l=0;l<=n;++l)
                std::swap(a[i][l],a[k][l]);
            for(k=0;k<n;++k)
                if(k!=i && a[k][i])
                    for(l=0;l<=n;++l)
                        a[k][l]^=a[i][l];
            ++i;
        }
        else //将不定元交换到后面去
        {
            l=n-1-j+i;
            for(k=0;k<n;++k)
                std::swap(a[k][l],a[k][i]);
        }
    }
    if(i==n)
    {
        for(i=cnt=0;i<n;++i)
            if(a[i][n])
                ++cnt;
        printf("%d\n",cnt);
        continue;
    }
    for(j=i;j<n;++j)
        if(a[j][n])
            break;
    if(j<n)
        puts("impossible");
    else
    {
        memset(ans,0,sizeof(ans));
        cnt=111;
        dfs(l=i);
        printf("%d\n",cnt);
    }
}

/*
 */

inline void ge(int a[N][N],int m,int n)
{
    static int i,j,k,l,b,c;
    for(i=j=0;i<m && j<n;++j)
    {
        for(k=i;k<m;++k)
            if(a[k][j])
                break;
        if(k==m)
            continue;
        for(l=0;l<=n;++l)
            std::swap(a[i][l],a[k][l]);
        for(k=0;k<m;++k)
            if(k!=i && a[k][j])
            {
                b=a[k][j];
                c=a[i][j];
                for(l=0;l<=n;++l)
                    a[k][l]=((a[k][l]*c-a[i][l]*b)%7+7)%7;
            }
        ++i;
    }
    for(j=i;j<m;++j)
        if(a[j][n])
            break;
    if(j<m)
    {
        puts("Inconsistent data.");
        return;
    }
    if(i<n)
        puts("Multiple solutions.");
    else
    {
        memset(ans,0,sizeof(ans));
        for(i=n-1;i>=0;--i)
        {
            k=a[i][n];
            for(j=i+1;j<n;++j)
                k=((k-a[i][j]*ans[j])%7+7)%7;
            while(k%a[i][i])
                k+=7;
            ans[i]=(k/a[i][i])%7;
        }
        for(i=0;i<n;++i)
            printf("%d%c",ans[i],i+1==n?'\n':' ');
    }
}
