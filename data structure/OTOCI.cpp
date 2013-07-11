#include<cstdio>
#include<algorithm>

#define MAXX 30111

int nxt[MAXX][2],fa[MAXX],pre[MAXX],val[MAXX],sum[MAXX];
bool rev[MAXX];

inline void up(int id)
{
    static int i;
    sum[id]=val[id];
    for(i=0;i<2;++i)
        if(nxt[id][i])
            sum[id]+=sum[nxt[id][i]];
}

inline void rot(int id,int tp)
{
    static int k;
    k=pre[id];
    nxt[k][tp^1]=nxt[id][tp];
    if(nxt[id][tp])
        pre[nxt[id][tp]]=k;
    if(pre[k])
        nxt[pre[k]][k==nxt[pre[k]][1]]=id;
    pre[id]=pre[k];
    nxt[id][tp]=k;
    pre[k]=id;
    up(k);
    up(id);
}

inline void down(int id)
{
    static int i;
    if(rev[id])
    {
        rev[id]=false;
        std::swap(nxt[id][0],nxt[id][1]);
        for(i=0;i<2;++i)
            if(nxt[id][i])
                rev[nxt[id][i]]^=true;
    }
}

int freshen(int id)
{
    int re(id);
    if(pre[id])
        re=freshen(pre[id]);
    down(id);
    return re;
}

inline void splay(int id)
{
    static int rt;
    if(id!=(rt=freshen(id)))
        for(std::swap(fa[id],fa[rt]);pre[id];rot(id,id==nxt[pre[id]][0]));
    /* another faster methond:
    if(id!=rt)
    {
        std::swap(fa[id],fa[rt]);
        do
        {
            rt=pre[id];
            if(pre[rt])
            {
                k=(nxt[pre[rt]][0]==rt);
                if(nxt[rt][k]==id)
                    rot(id,k^1);
                else
                    rot(rt,k);
                rot(id,k);
            }
            else
                rot(id,id==nxt[rt][0]);
        }
        while(pre[id]);
    }
    */
}

inline void access(int id)
{
    static int to;
    for(to=0;id;id=fa[id])
    {
        splay(id);
        if(nxt[id][1])
        {
            pre[nxt[id][1]]=0;
            fa[nxt[id][1]]=id;
        }
        nxt[id][1]=to;
        if(to)
        {
            pre[to]=id;
            fa[to]=0;
        }
        up(to=id);
    }
}

inline int getrt(int id)
{
    access(id);
    splay(id);
    while(nxt[id][0])
    {
        id=nxt[id][0];
        down(id);
    }
    return id;
}

inline void makert(int id)
{
    access(id);
    splay(id);
    if(nxt[id][0])
        rev[id]^=true;
}

int n,i,j,k,q;
char buf[11];

int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;++i)
        scanf("%d",val+i);
    scanf("%d",&q);
    while(q--)
    {
        scanf("%s %d %d",buf,&i,&j);
        switch(buf[0])
        {
            case 'b':
                if(getrt(i)==getrt(j))
                    puts("no");
                else
                {
                    puts("yes");
                    makert(i);
                    fa[i]=j;
                }
                break;
            case 'p':
                access(i);
                splay(i);
                val[i]=j;
                up(i);
                break;
            case 'e':
                if(getrt(i)!=getrt(j))
                    puts("impossible");
                else
                {
                    makert(i);
                    access(j);
                    splay(j);
                    printf("%d\n",sum[j]);
                }
                break;
        }
    }
    return 0;
}
