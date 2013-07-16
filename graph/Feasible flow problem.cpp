#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXX (255)
#define inf 0x3f3f3f3f

int cap[MAXX][MAXX];
int h[MAXX];
int last[MAXX];
int source,sink;

int mat[MAXX][MAXX][2];
bool bg,flag;

int n;

inline bool bfs()
{
    static int q[MAXX],*qf,*qb,i;
    memset(h,-1,sizeof h);
    qf=qb=q;
    for(h[*qb++=source]=0;qf!=qb;++qf)
        for(i=1;i<=n;++i)
            if(cap[*qf][i] && h[i]==-1)
            {
                h[*qb++=i]=h[*qf]+1;
                if(i==sink)
                    return true;
            }
    return false;
}

int dfs(int now,int maxcap)
{
    if(now==sink)
        return maxcap;
    for(int i(last[now]),f;i<=n;++i)
        if(cap[now][i] && h[i]==h[now]+1 && (f=dfs(i,std::min(maxcap,cap[now][i]))))
        {
            cap[now][i]-=f;
            cap[i][now]+=f;
            return f;
        }
    return 0;
}

int T;
int m,i,j,k,c;
int s,t,a,b;
int sr[MAXX],sc[MAXX];
char buf[11];

inline void gao(int x,int y)
{
    switch(buf[0])
    {
        case '>':
            mat[x][y][0]=std::max(mat[x][y][0],k+1);
            if(mat[x][y][0]>mat[x][y][1])
                flag=true;
            break;
        case '=':
            if(k<mat[x][y][0] || k>mat[x][y][1])
                flag=true;
            mat[x][y][0]=mat[x][y][1]=k;
            break;
        case '<':
            mat[x][y][1]=std::min(mat[x][y][1],k-1);
            if(mat[x][y][0]>mat[x][y][1])
                flag=true;
            break;
    }
}

int main()
{
    bg=true;
    scanf("%d",&T);
    while(T--)
    {
        if(!bg)
            puts("");
        memset(mat,0,sizeof mat);
        scanf("%d %d",&n,&m);
        for(i=1;i<=n;++i)
            scanf("%d",sr+i);
        for(i=1;i<=m;++i)
            scanf("%d",sc+i);
        s=n+m+1;
        t=s+1;
        source=t+1;
        sink=source+1;
        for(i=1;i<=n;++i)
            for(j=1;j<=m;++j)
            {
                mat[i][j+n][0]=0;
                mat[i][j+n][1]=inf;
            }
        bg=flag=false;
        scanf("%d",&c);
        while(c--)
        {
            scanf("%d %d %s %d",&i,&j,buf,&k);
            if(i)
                if(j)
                    gao(i,j+n);
                else
                    for(j=1;j<=m;++j)
                        gao(i,j+n);
            else
                if(j)
                    for(i=1;i<=n;++i)
                        gao(i,j+n);
                else
                    for(i=1;i<=n;++i)
                        for(j=1;j<=m;++j)
                            gao(i,j+n);
        }
        if(flag)
        {
            puts("IMPOSSIBLE");
            continue;
        }
        memset(cap,0,sizeof cap);
        for(i=1;i<=n;++i)
            mat[s][i][0]=mat[s][i][1]=sr[i];
        for(i=1;i<=m;++i)
            mat[i+n][t][0]=mat[i+n][t][1]=sc[i];

        a=0;
        for(i=1;i<=t;++i)
        {
            b=0;
            for(j=1;j<=t;++j)
            {
                b+=mat[j][i][0]-mat[i][j][0];
                cap[i][j]=mat[i][j][1]-mat[i][j][0];
            }
            if(b>0)
                a+=(cap[source][i]=b);
            else
                cap[i][sink]=-b;
        }
        cap[t][s]=inf;
        c=n;
        n=sink;
        for(i=1;i<=n;++i)
            last[i]=1;
        for(b=0;bfs();b+=dfs(source,inf));

//        printf("%d %d\n",a,b);
        if(a!=b)
            puts("IMPOSSIBLE");
        else
        {
            n=c;
            for(i=1;i<=n;++i)
            {
                for(j=1;j<=m;++j)
                    printf("%d ",cap[j+n][i]+mat[i][j+n][0]);
                puts("");
            }
        }
    }
    return 0;
}
