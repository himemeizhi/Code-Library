#include<cstdio>
#include<algorithm>
#include<queue>

#define MAXX 100111
#define MAX (MAXX<<1)

struct node
{
    bool set,rev;
    node *pre,*nxt[2],*fa;
    int lmax,max,rmax,sum,val,sz;
    node();
    node(int a);
}*tree[MAXX],*nil,*a,*b;

node::node()
{
    rev=set=false;
    fa=pre=nil;
    nxt[0]=nxt[1]=nil;
    sz=lmax=max=rmax=sum=val=0;
}

node::node(int a)
{
    set=rev=false;
    sum=val=a;
    sz=1;
    lmax=max=rmax=std::max(0,a);
    fa=pre=nxt[0]=nxt[1]=nil;
}

inline void add(node &x,const node &l,const node &r)
{
    x.max=std::max(l.rmax+r.lmax,std::max(l.max,r.max));
    x.lmax=std::max(l.lmax,l.sum+r.lmax);
    x.rmax=std::max(r.rmax,r.sum+l.rmax);
    x.sum=l.sum+r.sum;
}

inline void up(node *id)
{
    id->sz=id->nxt[0]->sz+id->nxt[1]->sz+1;
    id->sum=id->val+id->nxt[0]->sum+id->nxt[1]->sum;
    id->lmax=std::max(id->nxt[0]->lmax,id->nxt[0]->sum+id->val+id->nxt[1]->lmax);
    id->rmax=std::max(id->nxt[1]->rmax,id->nxt[1]->sum+id->val+id->nxt[0]->rmax);
    id->max=std::max(id->nxt[0]->rmax+id->val+id->nxt[1]->lmax,std::max(id->nxt[0]->max,id->nxt[1]->max));
}

inline void set(node *id,int val)
{
    if(id==nil)
        return;
    id->set=true;
    id->val=val;
    id->sum=val*id->sz;
    id->max=id->lmax=id->rmax=std::max(0,id->sum);
}

inline void down(node *id)
{
    if(id==nil)
        return;
    if(id->rev)
    {
        id->rev=false;
        for(int i(0);i<2;++i)
            if(id->nxt[i]!=nil)
            {
                id->nxt[i]->rev^=true;
                std::swap(id->nxt[i]->nxt[0],id->nxt[i]->nxt[1]);
                std::swap(id->nxt[i]->lmax,id->nxt[i]->rmax);
            }
    }
    if(id->set)
    {
        for(int i(0);i<2;++i)
            if(id->nxt[i]!=nil)
                set(id->nxt[i],id->val);
        id->set=false;
    }
}

inline void rot(node *id,int tp)
{
    node *k(id->pre);
    k->nxt[tp^1]=id->nxt[tp];
    if(id->nxt[tp]!=nil)
        id->nxt[tp]->pre=k;
    if(k->pre!=nil)
        k->pre->nxt[k==k->pre->nxt[1]]=id;
    id->pre=k->pre;
    id->nxt[tp]=k;
    k->pre=id;
    up(k);
    up(id);
}

node *fresh(node* id)
{
    node *re(id);
    if(id->pre!=nil)
        re=fresh(id->pre);
    down(id);
    return re;
}

inline void splay(node *id)
{
    node *rt(fresh(id));
    if(id!=rt)
        for(std::swap(rt->fa,id->fa);id->pre!=nil;rot(id,id==id->pre->nxt[0]));
}

inline void access(node *id)
{
    for(node *to(nil);id!=nil;id=id->fa)
    {
        splay(id);
        id->nxt[1]->pre=nil;
        if(id->nxt[1]!=nil)
            id->nxt[1]->fa=id;
        id->nxt[1]=to;
        if(to!=nil)
            to->pre=id;
        to->fa=nil;
        up(to=id);
    }
}

inline void lca(node *&to,node *&id)
{
    access(to);
    splay(id);
    for(to=nil;id->fa!=nil;splay(id=id->fa))
    {
        id->nxt[1]->pre=nil;
        if(id->nxt[1]!=nil)
            id->nxt[1]->fa=id;
        id->nxt[1]=to;
        if(to!=nil)
            to->pre=id;
        to->fa=nil;
        up(to=id);
    }
}

int n,i,j,k;
int nxt[MAX],to[MAX],edge[MAXX],cnt;
std::queue<int>q;

inline void add(int a,int b)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
}

void rr(int now,int fa)
{
    for(int i(edge[now]);i;i=nxt[i])
        if(to[i]!=fa)
        {
            tree[to[i]]->fa=tree[now];
            rr(to[i],now);
        }
}

/*
void print(node *id)
{
    if(id!=nil)
    {
        print(id->nxt[0]);
        printf("%2d %2d %2d %2d %2d %2d %c %2d\n",id->val,id->sum,id->sz,id->lmax,id->max,id->rmax,id->rev?'r':'n',id->pre->val);
        print(id->nxt[1]);
    }
}
*/

int main()
{
    nil=new node();
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {
        scanf("%d",&j);
        tree[i]=new node(j);
    }
    for(i=1;i<n;++i)
    {
        scanf("%d %d",&j,&k);
        add(j,k);
        add(k,j);
    }
    tree[0]=nil;
    rr(1,0);
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d %d",&k,&i,&j);
        a=tree[i];
        b=tree[j];
        access(a);
        splay(a);
        a->rev^=true;
        std::swap(a->nxt[0],a->nxt[1]);
        std::swap(a->lmax,a->rmax);
        access(b);
        splay(b);
        /*
        print(b);
        puts("");
        printf("%d %d %d %d\n",b->sum,b->nxt[0]->sum,b->val,b->nxt[1]->sum);
        */
        if(k==1)
            printf("%d\n",b->max);
        else
        {
            scanf("%d",&k);
            set(b,k);
        }
    }
    return 0;
}
