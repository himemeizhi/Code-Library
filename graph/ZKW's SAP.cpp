#include<cstdio>
#include<algorithm>
#include<cstring>

#define MAXX 5111
#define MAXM (30111*4)
#define inf 0x3f3f3f3f3f3f3f3fll

int edge[MAXX],to[MAXM],nxt[MAXM],cnt;
int w[MAXX];
long long cap[MAXM];

int n;
int h[MAXX],vh[MAXX];

inline void add(int a,int b,long long c)
{
    nxt[cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    cap[cnt]=c;
    ++cnt;
}

int source,sink;

long long aug(int now,long long flow)
{
    if(now==sink)
        return flow;
    long long l(flow);
    for(int &i(edge[now]);i!=-1;i=nxt[i])
        if(cap[i] && h[to[i]]+1==h[now])
        {
            long long d(aug(to[i],std::min(l,cap[i])));
            cap[i]-=d;
            cap[i^1]+=d;
            l-=d;
            if(h[source]==n || !l)
                return flow-l;
        }
    int minh(n);
    for(int i(edge[now]=w[now]);i!=-1;i=nxt[i])
        if(cap[i] && h[to[i]]+1<minh)
            minh=h[to[i]]+1;
    if(!--vh[h[now]])
        h[source]=n;
    else
        ++vh[h[now]=minh];
    return flow-l;
}

int m,i,j,k;
long long ans;

int main()
{
    scanf("%d %d",&n,&m);
    source=1;
    sink=n;
    memset(edge,-1,sizeof edge);
    while(m--)
    {
        scanf("%d %d %lld",&i,&j,&ans);
        add(i,j,ans);
        add(j,i,0);

        add(j,i,ans);
        add(i,j,0);
    }
    memcpy(w,edge,sizeof edge);
    memset(h,0,sizeof h);
    memset(vh,0,sizeof vh);
    vh[0]=n;
    ans=0;
    while(h[source]<n)
        ans+=aug(source,inf);
    printf("%lld\n",ans);
    return 0;
}
