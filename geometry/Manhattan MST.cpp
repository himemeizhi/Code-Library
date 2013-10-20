#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>

const int range(10000000);
const int ra(131072);
#define MAXX 100111
#define inf 0x7fffffff

int c[ra<<1],d[ra<<1];
int a[MAXX],b[MAXX];
int order[MAXX*4],torder[MAXX];
int idx[MAXX];
int road[MAXX][8];
int x[MAXX],y[MAXX];
int n;

inline void insert(int a,int b,int i)
{
    for(a+=ra;a && c[a]>b;a>>=1)
    {
        c[a]=b;
        d[a]=i;
    }
}

inline int find(int a)
{
    static int re,max;
    a+=ra;
    re=d[a];
    max=c[a];
    for(;a>1;a>>=1)
        if((a&1) && (c[--a]<max))
        {
            max=c[a];
            re=d[a];
        }
    return re;
}

const int cut(0xffff);
const int sz(1<<16|111);
int ta[sz],tb[MAXX];

inline void sort(int *p,int *tb,int n)
{
    static int i;
    memset(ta,0,sizeof ta);
    for(i=0;i<n;++i)
        ++ta[p[i]&cut];
    for(i=1;i<sz;++i)
        ta[i]+=ta[i-1];
    for(i=n-1;i>=0;--i)
        tb[--ta[p[order[i]]&cut]]=order[i];
    memmove(order,tb,n*sizeof(int));

    memset(ta,0,sizeof ta);
    for(i=0;i<n;++i)
        ++ta[p[i]>>16];
    for(i=1;i<sz;++i)
        ta[i]+=ta[i-1];
    for(i=n-1;i>=0;--i)
        tb[--ta[p[order[i]]>>16]]=order[i];
    memmove(order,tb,n*sizeof(int));
}

inline void work(int ii)
{
    static int i;
    for(i=0;i<n;++i)
    {
        a[i]=y[i]-x[i]+range;
        b[i]=range-y[i];
        order[i]=i;
    }
    sort(b,tb,n);
    sort(a,tb,n);
    for(i=0;i<n;++i)
    {
        torder[i]=order[i];
        order[i]=i;
    }
    sort(a,tb,n);
    sort(b,tb,n);
    for(i=0;i<n;++i)
        idx[order[i]]=i;
    for(i=1;i<ra+n;++i)
        c[i]=inf;
    memset(d,-1,sizeof d);
    for(i=0;i<n;++i)
    {
        int &tt(torder[i]);
        road[tt][ii]=find(idx[tt]);
        insert(idx[tt],y[tt]+x[tt],tt);
    }
}

inline int dist(int a,int b)
{
    return abs(x[a]-x[b])+abs(y[a]-y[b]);
}

int ttb[MAXX*4];
int rx[MAXX*4],ry[MAXX*4],rd[MAXX*4];
int rr;

int fa[MAXX];
int findfa(int a)
{
    return fa[a]==-1?a:fa[a]=findfa(fa[a]);
}

inline long long kruscal()
{
    static int i,j,x,y,t,tot;
    static long long ans;
    tot=ans=rr=0;
    for(i=0;i<n;++i)
        for(j=0;j<4;++j)
            if(road[i][j]!=-1)
            {
                rx[rr]=i;
                ry[rr]=road[i][j];
                rd[rr++]=dist(i,road[i][j]);
            }
    for(i=0;i<rr;++i)
        order[i]=i;
    sort(rd,ttb,rr);
    memset(fa,-1,sizeof fa);
    for(i=0;i<rr;++i)
    {
        if(tot+1==n)
            break;
        t=order[i];
        x=findfa(rx[t]);
        y=findfa(ry[t]);
        if(x!=y)
        {
            ans+=rd[t];
            ++tot;
            fa[x]=y;
        }
    }
    return ans;
}

int ca;
int i,j,k;

int main()
{
    while(scanf("%d",&n),n)
    {
        for(i=0;i<n;++i)
            scanf("%d %d",x+i,y+i);
        memset(road,-1,sizeof road);
        for(i=0;i<4;++i)
        {
            if(i==2)
                for(j=0;j<n;++j)
                    std::swap(x[j],y[j]);
            if(i&1)
                for(j=0;j<n;++j)
                    x[j]=range-x[j];
            work(i);
        }
        printf("Case %d: Total Weight = %lld\n",++ca,kruscal());
    }
    return 0;
}
