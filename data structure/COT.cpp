#include<cstdio>
#include<algorithm>

#define MAXX 100111
#define MAX (MAXX*23)
#define N 18

int sz[MAX],lson[MAX],rson[MAX],cnt;
int head[MAXX];
int pre[MAXX][N];
int map[MAXX],m;

int edge[MAXX],nxt[MAXX<<1],to[MAXX<<1];
int n,i,j,k,q,l,r,mid;
int num[MAXX],dg[MAXX];

int make(int l,int r)
{
    if(l==r)
        return ++cnt;
    int id(++cnt),mid((l+r)>>1);
    lson[id]=make(l,mid);
    rson[id]=make(mid+1,r);
    return id;
}

inline int update(int id,int pos)
{
    int re(++cnt);
    l=1;
    r=m;
    int nid(re);
    sz[nid]=sz[id]+1;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(pos<=mid)
        {
            lson[nid]=++cnt;
            rson[nid]=rson[id];
            nid=lson[nid];
            id=lson[id];
            r=mid;
        }
        else
        {
            lson[nid]=lson[id];
            rson[nid]=++cnt;
            nid=rson[nid];
            id=rson[id];
            l=mid+1;
        }
        sz[nid]=sz[id]+1;
    }
    return re;
}

void rr(int now,int fa)
{
    dg[now]=dg[fa]+1;
    head[now]=update(head[fa],num[now]);
    for(int i(edge[now]);i;i=nxt[i])
        if(to[i]!=fa)
        {
            j=1;
            for(pre[to[i]][0]=now;j<N;++j)
                pre[to[i]][j]=pre[pre[to[i]][j-1]][j-1];
            rr(to[i],now);
        }
}

inline int query(int a,int b,int n,int k)
{
    static int tmp,t;
    l=1;
    r=m;
    a=head[a];
    b=head[b];
    t=num[n];
    n=head[n];
    while(l<r)
    {
        mid=(l+r)>>1;
        tmp=sz[lson[a]]+sz[lson[b]]-2*sz[lson[n]]+(l<=t && t<=mid);
        if(tmp>=k)
        {
            a=lson[a];
            b=lson[b];
            n=lson[n];
            r=mid;
        }
        else
        {
            k-=tmp;
            a=rson[a];
            b=rson[b];
            n=rson[n];
            l=mid+1;
        }
    }
    return l;
}

inline int lca(int a,int b)
{
    static int i,j;
    j=0;
    if(dg[a]<dg[b])
        std::swap(a,b);
    for(i=dg[a]-dg[b];i;i>>=1,++j)
        if(i&1)
            a=pre[a][j];
    if(a==b)
        return a;
    for(i=N-1;i>=0;--i)
        if(pre[a][i]!=pre[b][i])
        {
            a=pre[a][i];
            b=pre[b][i];
        }
    return pre[a][0];
}

int main()
{
    scanf("%d %d",&n,&q);
    for(i=1;i<=n;++i)
    {
        scanf("%d",num+i);
        map[i]=num[i];
    }
    std::sort(map+1,map+n+1);
    m=std::unique(map+1,map+n+1)-map-1;
    for(i=1;i<=n;++i)
        num[i]=std::lower_bound(map+1,map+m+1,num[i])-map;
    for(i=1;i<n;++i)
    {
        scanf("%d %d",&j,&k);
        nxt[++cnt]=edge[j];
        edge[j]=cnt;
        to[cnt]=k;

        nxt[++cnt]=edge[k];
        edge[k]=cnt;
        to[cnt]=j;
    }
    cnt=0;
    head[0]=make(1,m);
    rr(1,0);
    while(q--)
    {
        scanf("%d %d %d",&i,&j,&k);
        printf("%d\n",map[query(i,j,lca(i,j),k)]);
    }
    return 0;
}


