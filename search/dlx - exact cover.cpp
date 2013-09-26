#define MAXN (N*22) // row
#define MAXM (N*10) // col
#define MAXX (MAXN*MAXM)

int cnt;
int l[MAXX],r[MAXX],u[MAXX],d[MAXX],rh[MAXX],ch[MAXX];
int sz[MAXM],hd[MAXN];
bool done[MAXN]; //solution

inline void init(const int m)
{
    static int i;
    for(i=0;i<=m;++i)
    {
        l[i+1]=i;
        r[i]=i+1;
        u[i]=d[i]=i;
        sz[i]=0;
    }
    r[m]=0;
    cnt=m+1;
}

inline void link(int x,int y)
{
    d[cnt]=d[y];
    u[cnt]=y;
    u[d[y]]=cnt;
    d[y]=cnt;
    if(hd[x]<0)  // set the val to -1 when you init a new line
    {
        hd[x]=l[cnt]=r[cnt]=cnt;
        done[x]=false;
    }
    else
    {
        l[cnt]=hd[x];
        r[cnt]=r[hd[x]];
        l[r[hd[x]]]=cnt;
        r[hd[x]]=cnt;
    }
    ++sz[y];
    rh[cnt]=x;
    ch[cnt]=y;
    ++cnt;
}

inline void rm(int c)
{
    l[r[c]]=l[c];
    r[l[c]]=r[c];
    static int i,j;
    for(i=d[c];i!=c;i=d[i])
        for(j=r[i];j!=i;j=r[j])
        {
            u[d[j]]=u[j];
            d[u[j]]=d[j];
            --sz[ch[j]];
        }
}

inline void add(int c)
{
    l[r[c]]=c;
    r[l[c]]=c;
    static int i,j;
    for(i=d[c];i!=c;i=d[i])
        for(j=r[i];j!=i;j=r[j])
        {
            u[d[j]]=j;
            d[u[j]]=j;
            ++sz[ch[j]];
        }
}

bool dlx()
{
    if(!r[0])
        return true;
    int i,j,c;
    for(i=c=r[0];i;i=r[i])
        if(sz[i]<sz[c])
            c=i;
    rm(c);
    for(i=d[c];i!=c;i=d[i])
    {
        done[rh[i]]=true;
        for(j=r[i];j!=i;j=r[j])
            rm(ch[j]);
        if(dlx())
            return true;
        for(j=l[i];j!=i;j=l[j])
            add(ch[j]);
        done[rh[i]]=false;
    }
    add(c);
    return false;
}
