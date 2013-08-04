#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXX 5111
#define MAXM (30111*4)
#define inf 0x3f3f3f3f3f3f3f3fll

int edge[MAXX],to[MAXM],nxt[MAXM],cnt;
#define v to[i]
long long cap[MAXM];

int n;
int h[MAXX],gap[MAXX],pre[MAXX],w[MAXX];

inline void add(int a,int b,long long c)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    cap[cnt]=c;
}

int source,sink;

inline long long go(const int N=sink)
{
    static int now,N,i;
    static long long min,mf;
    memset(gap,0,sizeof gap);
    memset(h,0,sizeof h);
    memcpy(w,edge,sizeof w);
    gap[0]=N;
    mf=0;

    pre[now=source]=-1;
    while(h[source]<N)
    {
rep:
        if(now==sink)
        {
            min=inf;
            for(i=pre[sink];i!=-1;i=pre[to[i^1]])
                if(min>=cap[i])
                {
                    min=cap[i];
                    now=to[i^1];
                }
            for(i=pre[sink];i!=-1;i=pre[to[i^1]])
            {
                cap[i]-=min;
                cap[i^1]+=min;
            }
            mf+=min;
        }
        for(int &i(w[now]);i!=-1;i=nxt[i])
            if(cap[i] && h[v]+1==h[now])
            {
                pre[now=v]=i;
                goto rep;
            }
        if(!--gap[h[now]])
            return mf;
        min=N;
        for(i=w[now]=edge[now];i!=-1;i=nxt[i])
            if(cap[i])
                min=std::min(min,(long long)h[v]);
        ++gap[h[now]=min+1];
        if(now!=source)
            now=to[pre[now]^1];
    }
    return mf;
}

int m,i,j,k;
long long ans;

int main()
{
    scanf("%d %d",&n,&m);
    source=1;
    sink=n;
    cnt=-1;
    memset(edge,-1,sizeof edge);
    while(m--)
    {
        scanf("%d %d %lld",&i,&j,&ans);
        add(i,j,ans);
        add(j,i,ans);
    }
    printf("%lld\n",go());
    return 0;
}
