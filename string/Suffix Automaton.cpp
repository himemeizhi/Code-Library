/*
`length(s) $\in$ [ min(s), max(s) ] = [ val[fal[s]]+1, val[s] ]`
 */
#define MAXX 90111
#define MAXN (MAXX<<1)

int fal[MAXN],nxt[MAXN][26],val[MAXN],cnt,rt,last;

inline int neww(int v=0)
{
    val[++cnt]=v;
    fal[cnt]=0;
    memset(nxt[cnt],0,sizeof nxt[0]);
    return cnt;
}

inline void add(int w)
{
    static int p,np,q,nq;
    p=last;
    np=neww(val[p]+1);
    while(p && !nxt[p][w])
    {
        nxt[p][w]=np;
        p=fal[p];
    }
    if(!p)
        fal[np]=rt;
    else
    {
        q=nxt[p][w];
        if(val[p]+1==val[q])
            fal[np]=q;
        else
        {
            nq=neww(val[p]+1);
            memcpy(nxt[nq],nxt[q],sizeof nxt[0]);
            fal[nq]=fal[q];

            fal[q]=fal[np]=nq;
            while(p && nxt[p][w]==q)
            {
                nxt[p][w]=nq;
                p=fal[p];
            }
        }
    }
    last=np;
}

int v[MAXN],the[MAXN];

inline void make(char *str)
{
    cnt=0;
    rt=last=neww();
    static int i,len,now;
    for(i=0;str[i];++i)
        add(str[i]-'a');
    len=i;
    memset(v,0,sizeof v);
    for(i=1;i<=cnt;++i)
        ++v[val[i]];
    for(i=1;i<=len;++i)
        v[i]+=v[i-1];
    for(i=1;i<=cnt;++i)
        the[v[val[i]]--]=i;
    for(i=cnt;i;--i)
    {
        now=the[i];
        // topsort already
    }
}
/*
sizeof right(s):
    init:
        for all np:
            count[np]=1;
    process:
        for all status s:
            count[fal[s]]+=count[s];
*/
