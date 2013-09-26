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
    int flow(maxcap),d;
    for(int &i(w[now]);i!=-1;i=nxt[i])
        if(cap[i] && h[to[i]]==h[now]+1)// && (flow=dfs(to[i],std::min(maxcap,cap[i]))))
        {
            d=dfs(to[i],std::min(flow,cap[i]));
            cap[i]-=d;
            cap[i^1]+=d;
            flow-=d;
            if(!flow)
                return maxcap;
        }
    return maxcap-flow;
}

inline int go()
{
    static int ans;
    ans=0;
    while(bfs())
    {
        memcpy(w,edge,sizeof edge);
        ans+=dfs(source,inf);
        /*
           while((k=dfs(source,inf)))
           ans+=k;
           */
    }
    return ans;
}
