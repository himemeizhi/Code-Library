#define MAXN 55
#define MAXM 55
#define MAXX (MAXN*MAXM)

int cnt;
int l[MAXX],r[MAXX],u[MAXX],d[MAXX],ch[MAXX];
int hd[MAXN],sz[MAXM];

inline void init(int m)
{
    static int i;
    for(i=0;i<=m;++i)
    {
        r[i]=i+1;
        l[i+1]=i;
        u[i]=d[i]=i;
        sz[i]=0;
    }
    r[m]=0;
    cnt=m;
}

inline void link(int x,int y)
{
    ++cnt;
    d[cnt]=d[y];
    u[cnt]=y;
    u[d[y]]=cnt;
    d[y]=cnt;
    if(hd[x]==-1)
        hd[x]=l[cnt]=r[cnt]=cnt;
    else
    {
        l[cnt]=hd[x];
        r[cnt]=r[hd[x]];
        l[r[hd[x]]]=cnt;
        r[hd[x]]=cnt;
    }
    ++sz[y];
    ch[cnt]=y;
}

inline void rm(int c)
{
    static int i;
    for(i=d[c];i!=c;i=d[i])
    {
        r[l[i]]=r[i];
        l[r[i]]=l[i];
    }
}

inline void add(int c)
{
    static int i;
    for(i=d[c];i!=c;i=d[i])
        r[l[i]]=l[r[i]]=i;
}

int K; // can't select more than K rows

inline int A()
{
    static int i,j,k,re;
    static bool done[MAXM];
    re=0;
    memset(done,0,sizeof done);
    for(i=r[0];i;i=r[i])
        if(!done[i])
        {
            ++re;
            for(j=d[i];j!=i;j=d[j])
                for(k=r[j];k!=j;k=r[k])
                    done[ch[k]]=true;
        }
    return re;
}

bool dlx(int now)
{
    if(!r[0])
        return true;
    if(now+A()<=K)
    {
        int i,j,c;
        for(i=c=r[0];i;i=r[i])
            if(sz[i]<sz[c])
                c=i;
        for(i=d[c];i!=c;i=d[i])
        {
            rm(i);
            for(j=r[i];j!=i;j=r[j])
                rm(j);
            if(dlx(now+1))
                return true;
            for(j=l[i];j!=i;j=l[j])
                add(j);
            add(i);
        }
    }
    return false;
}
