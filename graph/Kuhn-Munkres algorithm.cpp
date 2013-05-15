bool match(int u)//匈牙利
{
    vx[u]=true;
    for(int i=1;i<=n;++i)
        if(lx[u]+ly[i]==g[u][i]&&!vy[i])
        {
            vy[i]=true;
            if(!d[i]||match(d[i]))
            {
                d[i]=u;
                return true;
            }
        }
    return false;
}
inline void update()//
{
    int i,j;
    int a=1<<30;
    for(i=1;i<=n;++i)if(vx[i])
        for(j=1;j<=n;++j)if(!vy[j])
            a=min(a,lx[i]+ly[j]-g[i][j]);
    for(i=1;i<=n;++i)
    {
        if(vx[i])lx[i]-=a;
        if(vy[i])ly[i]+=a;
    }
}
void km()
{
    int i,j;
    for(i=1;i<=n;++i)
    {
        lx[i]=ly[i]=d[i]=0;
        for(j=1;j<=n;++j)
            lx[i]=max(lx[i],g[i][j]);
    }
    for(i=1;i<=n;++i)
    {
        while(true)
        {
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            if(match(i))
                break;
            update();
        }
    }
    int ans=0;
    for(i=1;i<=n;++i)
        if(d[i]!=0)
            ans+=g[d[i]][i];
    printf("%d\n",ans);
}
int main()
{
    while(scanf("%d\n",&n)!=EOF)
    {
        for(int i=1;i<=n;++i)gets(s[i]);
        memset(g,0,sizeof(g));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(i!=j) g[i][j]=cal(s[i],s[j]);
        km();
    }
    return 0;
}


//bupt

//km算法：求二分图最佳匹配 n^3复杂度
int dfs(int u)//匈牙利求增广路
{
    int v;
    sx[u]=1;
    for ( v=1; v<=n; v++)
        if (!sy[v] && lx[u]+ly[v]==map[u][v])
        {
            sy[v]=1;
            if (match[v]==-1 || dfs(match[v]))
            {
                match[v]=u;
                return 1;
            }
        }
    return 0;
}

int bestmatch(void)//km求最佳匹配
{
    int i,j,u;
    for (i=1; i<=n; i++)//初始化顶标
    {
        lx[i]=-1;
        ly[i]=0;
        for (j=1; j<=n; j++)
            if (lx[i]<map[i][j])
                lx[i]=map[i][j];
    }
    memset(match, -1, sizeof(match));
    for (u=1; u<=n; u++)
    {
        while (true)
        {
            memset(sx,0,sizeof(sx));
            memset(sy,0,sizeof(sy));
            if (dfs(u))
                break;
            int dx=Inf;//若找不到增广路，则修改顶标~~
            for (i=1; i<=n; i++)
            {
                if (sx[i])
                    for (j=1; j<=n; j++)
                        if(!sy[j] && dx>lx[i]+ly[j]-map[i][j])
                            dx=lx[i]+ly[j]-map[i][j];
            }
            for (i=1; i<=n; i++)
            {
                if (sx[i])
                    lx[i]-=dx;
                if (sy[i])
                    ly[i]+=dx;
            }
        }
    }
    int sum=0;
    for (i=1; i<=n; i++)
        sum+=map[match[i]][i];  
    return sum;  
}
