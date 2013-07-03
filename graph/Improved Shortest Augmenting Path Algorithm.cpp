#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXN 20111
#define MAXM (MAXN*25)
#define inf 0x3f3f3f3f

int edge[MAXN],nxt[MAXM],to[MAXM],cnt;
long long flow[MAXM],cap[MAXM];

inline void add(int a,int b,long long k)
{
    nxt[cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    cap[cnt]=k;
    ++cnt;
}

int n;
int h[MAXN],vh[MAXN],source,sink;

long long sap(int idx,int maxcap)
{
    if(idx==sink)
        return maxcap;
    long long l=maxcap,d;
    int minh=n;
    int i;
    for(i=edge[idx];i!=-1;i=nxt[i])
    {
        int nm=i;
        if(cap[nm]>flow[nm])
        {
            if(h[idx]==h[to[nm]]+1)
            {
                d=sap(to[nm],std::min(l,cap[nm]-flow[nm]));
                flow[nm]+=d;
                flow[i^1]-=d;
                l-=d;
                if(h[source]==n || !l)
                    return maxcap-l;
            }
            minh=std::min(minh,h[to[nm]]+1);
        }
    }
    if(l==maxcap)
    {
        --vh[h[idx]];
        ++vh[minh];
        if(!vh[h[idx]])
            h[source]=n;
        h[idx]=minh;
    }
    return maxcap-l;
}

inline void bfs()
{
    static int i;
    for(i=0;i<n;++i)
        h[i]=n;
    static int *qf,*qt;
    qf=qt=vh;

    h[sink]=0;
    *qt++=sink;
    static int u;
    while(qf!=qt)
    {
        u=*qf++;
        for(i=edge[u];i!=-1;i=nxt[i])
            if((i&1) && (h[to[i]]==n))
            {
                h[to[i]]=h[u]+1;
                *qt++=to[i];
            }
    }
    memset(vh,0,sizeof vh);
    for(i=0;i<n;++i)
        ++vh[h[i]];
}

inline long long go(int source,int sink)
{
    if(source==sink)
        return inf;
    ::source=source;
    ::sink=sink;
    bfs();
    static int i;
    static long long ans;
    for(i=0;i<cnt;++i)
        flow[i]=0ll;
    ans=0ll;
    while(h[source]!=n)
        ans+=sap(source,inf);
    return ans;
}

int m,i,j;
long long k;

int main()
{
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;++i)
        edge[i]=-1;
    cnt=0;
    while(m--)
    {
        scanf("%d %d %lld",&i,&j,&k);
        add(i,j,k);
        add(j,i,0ll);

        add(j,i,k);
        add(i,j,0ll);

    }
    printf("%lld\n",go(1,n));
    return 0;
}
