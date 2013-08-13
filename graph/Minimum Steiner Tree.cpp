#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXX 211
#define MAXE 10111
#define inf 0x3f3f3f3f

int edge[MAXX],nxt[MAXE],to[MAXE],wg[MAXE],cnt;
inline void add(int a,int b,int c)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    wg[cnt]=c;
}

int dp[1<<8];
int s[MAXX];
int d[1<<8][MAXX];
int S[MAXX],P[MAXX];
int fac[8];

struct node
{
    int a,b,dist;
    node(){}
    node(int i,int j,int k):a(i),b(j),dist(k){}
    bool operator<(const node &i)const
    {
        return dist>i.dist;
    }
    int &get()
    {
        return d[b][a];
    }
}now;

std::priority_queue<node>q;

int n,m,nn,i,j,k;
int cs,cf,x,y;
int ans,cst;

inline bool check(int x)
{
    static int re,i;
    for(i=re=0;x;x>>=1,++i)
        re+=(x&1)*(i<cf?fac[i]:-1);
    return re>=0;
}

inline int count(int x)
{
    static int i,re;
    x>>=cf;
    for(re=0;x;x>>=1)
        re+=(x&1);
    return re;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        memset(s,0,sizeof s);
        memset(d,0x3f,sizeof d);
        memset(dp,0x3f,sizeof dp);
        ans=cnt=cf=cs=0;
        memset(edge,0,sizeof edge);
        for(i=1;i<=n;++i)
        {
            scanf("%d %d",P+i,S+i);
            if(S[i] && P[i])
            {
                ++ans;
                --P[i];
                S[i]=0;
            }
            if(P[i])
            {
                s[i]=1<<cf;
                fac[cf]=P[i];
                d[s[i]][i]=0;
                ++cf;
            }
        }
        for(i=1;i<=n;++i)
            if(S[i])
            {
                s[i]=1<<(cf+cs);
                d[s[i]][i]=0;
                ++cs;
            }
        nn=1<<(cf+cs);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            add(i,j,k);
            add(j,i,k);
        }
        for(y=1;y<nn;++y)
        {
            for(x=1;x<=n;++x)
            {
                if(s[x] && !(s[x]&y))
                    continue;
                for(i=(y-1)&y;i;i=(i-1)&y)
                    d[y][x]=std::min(d[y][x],d[i|s[x]][x]+d[(y^i)|s[x]][x]);
                if(d[y][x]!=inf)
                    q.push(node(x,y,d[y][x]));
            }
            while(!q.empty())
            {
                now=q.top();
                q.pop();
                if(now.dist!=now.get())
                    continue;
                static int x,y,a,b;
                x=now.a;
                y=now.b;
                for(i=edge[x];i;i=nxt[i])
                {
                    a=to[i];
                    b=y|s[a];
                    if(d[b][a]>now.get()+wg[i])
                    {
                        d[b][a]=now.get()+wg[i];
                        if(b==y)
                            q.push(node(a,b,d[b][a]));
                    }
                }
            }
        }
        for(j=0;j<nn;++j)
            dp[j]=*std::min_element(d[j]+1,d[j]+1+n);
        cnt=cst=0;
        for(i=1;i<nn;++i)
            if(check(i))
            {
                for(j=(i-1)&i;j;j=(j-1)&i)
                    if(check(j) && check(i^j))
                        dp[i]=std::min(dp[i],dp[j]+dp[i^j]);
                k=count(i);
                if(dp[i]!=inf && (k>cnt || (k==cnt && dp[i]<cst)))
                {
                    cnt=k;
                    cst=dp[i];
                }
            }
        printf("%d %d\n",ans+cnt,cst);
    }
    return 0;
}
