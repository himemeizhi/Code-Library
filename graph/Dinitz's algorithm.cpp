#include<cstdio>
#include<algorithm>
#include<cstring>

#define MAXX 111
#define MAXM (MAXX*MAXX*4)
#define inf 0x3f3f3f3f

int n;
int w[MAXX],h[MAXX],q[MAXX];
int edge[MAXX],to[MAXM],cap[MAXM],nxt[MAXM],cnt;
int source,sink;

inline void add(int a,int b,int c)
{
    nxt[cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    cap[cnt]=c;
    ++cnt;
}

inline bool bfs()
{
    static int *qf,*qb;
    static int i;
    memset(h,-1,sizeof h);
    qf=qb=q;
    h[*qb++=source]=0;
    for(;qf!=qb;++qf)
        for(i=edge[*qf];i!=-1;i=nxt[i])
            if(cap[i] && h[to[i]]==-1)
                h[*qb++=to[i]]=h[*qf]+1;
    return h[sink]!=-1;
}

int dfs(int now,int maxcap)
{
    if(now==sink)
        return maxcap;
    for(int &i(w[now]),flow;i!=-1;i=nxt[i])
        if(cap[i] && h[to[i]]==h[now]+1 && (flow=dfs(to[i],std::min(maxcap,cap[i]))))
        {
            cap[i]-=flow;
            cap[i^1]+=flow;
            return flow;
        }
    return 0;
}

int nc,np,m,i,j,k;
int ans;

int main()
{
    while(scanf("%d %d %d %d",&n,&np,&nc,&m)!=EOF)
    {
        cnt=0;
        memset(edge,-1,sizeof edge);
        while(m--)
        {
            while(getchar()!='(');
            scanf("%d",&i);
            while(getchar()!=',');
            scanf("%d",&j);
            while(getchar()!=')');
            scanf("%d",&k);
            if(i!=j)
            {
                ++i;
                ++j;
                add(i,j,k);
                add(j,i,0);
            }
        }
        source=++n;
        while(np--)
        {
            while(getchar()!='(');
            scanf("%d",&i);
            while(getchar()!=')');
            scanf("%d",&j);
            ++i;
            add(source,i,j);
            add(i,source,0);
        }
        sink=++n;
        while(nc--)
        {
            while(getchar()!='(');
            scanf("%d",&i);
            while(getchar()!=')');
            scanf("%d",&j);
            ++i;
            add(i,sink,j);
            add(sink,i,0);
        }
        ans=0;
        while(bfs())
        {
            memcpy(w,edge,sizeof edge);
            while((k=dfs(source,inf)))
                ans+=k;
        }
        printf("%d\n",ans);
    }
    return 0;
}
