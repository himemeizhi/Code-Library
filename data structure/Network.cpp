//`HLD……备忘……_(:3JZ)_`
#include<cstdio>
#include<algorithm>
#include<cstdlib>

#define MAXX 80111
#define MAXE (MAXX<<1)
#define N 18

int edge[MAXX],nxt[MAXE],to[MAXE],cnt;
int fa[MAXX][N],dg[MAXX];

inline int lca(int a,int b)
{
    static int i,j;
    j=0;
    if(dg[a]<dg[b])
        std::swap(a,b);
    for(i=dg[a]-dg[b];i;i>>=1,++j)
        if(i&1)
            a=fa[a][j];
    if(a==b)
        return a;
    for(i=N-1;i>=0;--i)
        if(fa[a][i]!=fa[b][i])
        {
            a=fa[a][i];
            b=fa[b][i];
        }
    return fa[a][0];
}

inline void add(int a,int b)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
}

int sz[MAXX],pre[MAXX],next[MAXX];

void rr(int now)
{
    sz[now]=1;
    int max,id;
    max=0;
    for(int i(edge[now]);i;i=nxt[i])
        if(to[i]!=fa[now][0])
        {
            fa[to[i]][0]=now;
            dg[to[i]]=dg[now]+1;
            rr(to[i]);
            sz[now]+=sz[to[i]];
            if(sz[to[i]]>max)
            {
                max=sz[to[i]];
                id=to[i];
            }
        }
    if(max)
    {
        next[now]=id;
        pre[id]=now;
    }
}

#define MAXT (MAXX*N*5)

namespace Treap
{
    int cnt;
    int son[MAXT][2],key[MAXT],val[MAXT],sz[MAXT];

    inline void init()
    {
        key[0]=RAND_MAX;
        val[0]=0xc0c0c0c0;
        cnt=0;
    }

    inline void up(int id)
    {
        sz[id]=sz[son[id][0]]+sz[son[id][1]]+1;
    }
    inline void rot(int &id,int tp)
    {
        static int k;
        k=son[id][tp];
        son[id][tp]=son[k][tp^1];
        son[k][tp^1]=id;
        up(id);
        up(k);
        id=k;
    }
    void insert(int &id,int v)
    {
        if(id)
        {
            int k(v>=val[id]);
            insert(son[id][k],v);
            if(key[son[id][k]]<key[id])
                rot(id,k);
            else
                up(id);
            return;
        }
        id=++cnt;
        key[id]=rand()-1;
        val[id]=v;
        sz[id]=1;
        son[id][0]=son[id][1]=0;
    }
    void del(int &id,int v)
    {
        if(!id)
            return;
        if(val[id]==v)
        {
            int k(key[son[id][1]]<key[son[id][0]]);
            if(!son[id][k])
            {
                id=0;
                return;
            }
            rot(id,k);
            del(son[id][k^1],v);
        }
        else
            del(son[id][v>val[id]],v);
        up(id);
    }
    int rank(int id,int v)
    {
        if(!id)
            return 0;
        if(val[id]<=v)
            return sz[son[id][0]]+1+rank(son[id][1],v);
        return rank(son[id][0],v);
    }
    void print(int id)
    {
        if(!id)
            return;
        print(son[id][0]);
        printf("%d ",val[id]);
        print(son[id][1]);
    }
}

int head[MAXX],root[MAXX],len[MAXX],pos[MAXX];

#define MAX (MAXX*6)
#define mid (l+r>>1)
#define lc lson[id],l,mid
#define rc rson[id],mid+1,r

int lson[MAX],rson[MAX];
int treap[MAX];

void make(int &id,int l,int r,int *the)
{
    id=++cnt;
    static int k;
    for(k=l;k<=r;++k)
        Treap::insert(treap[id],the[k]);
    if(l!=r)
    {
        make(lc,the);
        make(rc,the);
    }
}

int query(int id,int l,int r,int a,int b,int q)
{
    if(a<=l && r<=b)
        return Treap::rank(treap[id],q);
    int re(0);
    if(a<=mid)
        re=query(lc,a,b,q);
    if(b>mid)
        re+=query(rc,a,b,q);
    return re;
}

inline int query(int a,int b,int v)
{
    static int re;
    for(re=0;root[a]!=root[b];a=fa[root[a]][0])
        re+=query(head[root[a]],1,len[root[a]],1,pos[a],v);
    re+=query(head[root[a]],1,len[root[a]],pos[b],pos[a],v);
    return re;
}

inline void update(int id,int l,int r,int pos,int val,int n)
{
    while(l<=r)
    {
        Treap::del(treap[id],val);
        Treap::insert(treap[id],n);
        if(l==r)
            return;
        if(pos<=mid)
        {
            id=lson[id];
            r=mid;
        }
        else
        {
            id=rson[id];
            l=mid+1;
        }
    }
}

int n,q,i,j,k;
int val[MAXX];

int main()
{
    srand(1e9+7);
    scanf("%d %d",&n,&q);
    for(i=1;i<=n;++i)
        scanf("%d",val+i);
    for(k=1;k<n;++k)
    {
        scanf("%d %d",&i,&j);
        add(i,j);
        add(j,i);
    }
    rr(rand()%n+1);
    for(j=1;j<N;++j)
        for(i=1;i<=n;++i)
            fa[i][j]=fa[fa[i][j-1]][j-1];

    Treap::init();
    cnt=0;
    for(i=1;i<=n;++i)
        if(!pre[i])
        {
            static int tmp[MAXX];
            for(k=1,j=i;j;j=next[j],++k)
            {
                pos[j]=k;
                root[j]=i;
                tmp[k]=val[j];
            }
            --k;
            len[i]=k;
            make(head[i],1,k,tmp);
        }
    while(q--)
    {
        scanf("%d",&k);
        if(k)
        {
            static int a,b,c,d,l,r,ans,m;
            scanf("%d %d",&a,&b);
            c=lca(a,b);
            if(dg[a]+dg[b]-2*dg[c]+1<k)
            {
                puts("invalid request!");
                continue;
            }
            k=dg[a]+dg[b]-2*dg[c]+1-k+1;
            if(dg[a]<dg[b])
                std::swap(a,b);
            l=-1e9;
            r=1e9;
            if(b!=c)
            {
                d=a;
                for(i=0,j=dg[a]-dg[c]-1;j;j>>=1,++i)
                    if(j&1)
                        d=fa[d][i];
                while(l<=r)
                {
                    m=l+r>>1;
                    if(query(a,d,m)+query(b,c,m)>=k)
                    {
                        ans=m;
                        r=m-1;
                    }
                    else
                        l=m+1;
                }
            }
            else
            {
                while(l<=r)
                {
                    m=l+r>>1;
                    if(query(a,c,m)>=k)
                    {
                        ans=m;
                        r=m-1;
                    }
                    else
                        l=m+1;
                }
            }
            printf("%d\n",ans);
        }
        else
        {
            scanf("%d %d",&i,&j);
            update(head[root[i]],1,len[root[i]],pos[i],val[i],j);
            val[i]=j;
        }
    }
    return 0;
}
