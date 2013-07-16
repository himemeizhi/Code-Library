#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<deque>

#define MAXX 111
#define MAXN 211
#define MAXE (MAXN*MAXN*3)
#define inf 0x3f3f3f3f

char buf[MAXX];

int edge[MAXN],nxt[MAXE],to[MAXE],cap[MAXE],cst[MAXE],cnt;

inline void adde(int a,int b,int c,int k)
{
    nxt[cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    cap[cnt]=c;
    cst[cnt]=k;
    ++cnt;
}

inline void add(int a,int b,int c,int k)
{
    adde(a,b,c,k);
    adde(b,a,0,-k);
}

int n,mf,cost,pi1;
int source,sink;
bool done[MAXN];

int aug(int now,int maxcap)
{
    if(now==sink)
    {
        mf+=maxcap;
        cost+=maxcap*pi1;
        return maxcap;
    }
    done[now]=true;
    int l=maxcap;
    for(int i(edge[now]);i!=-1;i=nxt[i])
        if(cap[i] && !cst[i] && !done[to[i]])
        {
            int d(aug(to[i],std::min(l,cap[i])));
            cap[i]-=d;
            cap[i^1]+=d;
            l-=d;
            if(!l)
                return maxcap;
        }
    return maxcap-l;
}

inline bool label()
{
    static int d,i,j;
    d=inf;
    for(i=1;i<=n;++i)
        if(done[i])
            for(j=edge[i];j!=-1;j=nxt[j])
                if(cap[j] && !done[to[j]] && cst[j]<d)
                    d=cst[j];
    if(d==inf)
        return false;
    for(i=1;i<=n;++i)
        if(done[i])
            for(j=edge[i];j!=-1;j=nxt[j])
            {
                cst[j]-=d;
                cst[j^1]+=d;
            }
    pi1+=d;
    return true;
    /* primal-dual approach
    static int d[MAXN],i,j;
    static std::deque<int>q;
    memset(d,0x3f,sizeof d);
    d[sink]=0;
    q.push_back(sink);
    while(!q.empty())
    {
        static int dt,now;
        now=q.front();
        q.pop_front();
        for(i=edge[now];i!=-1;i=nxt[i])
            if(cap[i^1] && (dt=d[now]-cst[i])<d[to[i]])
                if((d[to[i]]=dt)<=d[q.empty()?0:q.front()])
                    q.push_front(to[i]);
                else
                    q.push_back(to[i]);
    }
    for(i=1;i<=n;++i)
        for(j=edge[i];j!=-1;j=nxt[j])
            cst[j]+=d[to[j]]-d[i];
    pi1+=d[source];
    return d[source]!=inf;
    */
}

int m,i,j,k;
typedef std::pair<int,int> pii;
std::vector<pii>M(MAXN),H(MAXN);

int main()
{
    while(scanf("%d %d",&n,&m),(n||m))
    {
        M.resize(0);
        H.resize(0);
        for(i=0;i<n;++i)
        {
            scanf("%s",buf);
            for(j=0;j<m;++j)
                if(buf[j]=='m')
                    M.push_back(pii(i,j));
                else
                    if(buf[j]=='H')
                        H.push_back(pii(i,j));
        }
        n=M.size()+H.size();
        source=++n;
        sink=++n;
        memset(edge,-1,sizeof edge);
        cnt=0;
        for(i=0;i<M.size();++i)
            for(j=0;j<H.size();++j)
                add(i+1,j+1+M.size(),1,abs(M[i].first-H[j].first)+abs(M[i].second-H[j].second));
        for(i=0;i<M.size();++i)
            add(source,i+1,1,0);
        for(i=0;i<H.size();++i)
            add(i+1+M.size(),sink,1,0);
        mf=cost=pi1=0;
        do
            do
                memset(done,0,sizeof done);
            while(aug(source,inf));
        while(label());
        /* primal-dual approach
        while(label())
            do
                memset(done,0,sizeof done);
            while(aug(source,inf));
        */
        printf("%d\n",cost);
    }
    return 0;
}
