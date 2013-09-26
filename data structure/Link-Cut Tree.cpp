//`记得随手down啊……亲……`
//`debug时记得优先检查up/down/select`
#define MAXX
#define lson nxt[id][0]
#define rson nxt[id][1]

int nxt[MAXX][2],fa[MAXX],pre[MAXX];
bool rev[MAXX];

inline void up(int id)
{
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

inline void down(int id) //`记得随手down啊……亲……`
{
    static int i;
    if(rev[id])
    {
        rev[id]=false;
        for(i=0;i<2;++i)
            if(nxt[id][i])
            {
                rev[nxt[id][i]]^=true;
                std::swap(nxt[nxt[id][i]][0],nxt[nxt[id][i]][1]);
            }
    }
}

inline void splay(int id)//`记得随手down啊……亲……`
{
    down(id);
    if(!pre[id])
        return;
    static int rt,k,st[MAXX];
    for(rt=id,k=0;rt;rt=pre[rt])
        st[k++]=rt;
    rt=st[k-1];
    while(k)
        down(st[--k]);
    for(std::swap(fa[id],fa[rt]);pre[id];rot(id,id==nxt[pre[id]][0]));
    /* another faster methond:
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
    */
}

inline int access(int id)
{
    static int to;
    for(to=0;id;id=fa[id])
    {
        splay(id);
        if(rson)
        {
            pre[rson]=0;
            fa[rson]=id;
        }
        rson=to;
        if(to)
        {
            pre[to]=id;
            fa[to]=0;
        }
        up(to=id);
    }
    return to;
}
