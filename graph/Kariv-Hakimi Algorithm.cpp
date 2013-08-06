//Absolute Center of a graph, not only a tree
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<set>

#define MAXX 211
#define inf 0x3f3f3f3f

int e[MAXX][MAXX],dist[MAXX][MAXX];
double dp[MAXX],ta;
int ans,d;
int n,m,a,b;
int i,j,k;
typedef std::pair<int,int> pii;
std::vector<pii>vt[2];
bool done[MAXX];
typedef std::pair<double,int> pdi;
std::multiset<pdi>q;
int pre[MAXX];

int main()
{
    vt[0].reserve(MAXX);
    vt[1].reserve(MAXX);
    scanf("%d %d",&n,&m);
    memset(e,0x3f,sizeof(e));
    while(m--)
    {
        scanf("%d %d %d",&i,&j,&k);
        e[i][j]=e[j][i]=std::min(e[i][j],k);
    }
    for(i=1;i<=n;++i)
        e[i][i]=0;
    memcpy(dist,e,sizeof(dist));
    for(k=1;k<=n;++k)
        for(i=1;i<=n;++i)
            for(j=1;j<=n;++j)
                dist[i][j]=std::min(dist[i][j],dist[i][k]+dist[k][j]);
    ans=inf;
    for(i=1;i<=n;++i)
        for(j=i;j<=n;++j)
            if(e[i][j]!=inf)
            {
                vt[0].resize(0);
                vt[1].resize(0);
                static int i;
                for(i=1;i<=n;++i)
                    vt[0].push_back(pii(dist[::i][i],dist[j][i]));
                std::sort(vt[0].begin(),vt[0].end());
                for(i=0;i<vt[0].size();++i)
                {
                    while(!vt[1].empty() && vt[1].back().second<=vt[0][i].second)
                        vt[1].pop_back();
                    vt[1].push_back(vt[0][i]);
                }
                d=inf;
                if(vt[1].size()==1)
                    if(vt[1][0].first<vt[1][0].second)
                    {
                        ta=0;
                        d=(vt[1][0].first<<1);
                    }
                    else
                    {
                        ta=e[::i][j];
                        d=(vt[1][0].second<<1);
                    }
                else
                    for(i=1;i<vt[1].size();++i)
                        if(d>e[::i][j]+vt[1][i-1].first+vt[1][i].second)
                        {
                            ta=(e[::i][j]+vt[1][i].second-vt[1][i-1].first)/(double)2.0f;
                            d=e[::i][j]+vt[1][i-1].first+vt[1][i].second;
                        }
                if(d<ans)
                {
                    ans=d;
                    a=::i;
                    b=j;
                    dp[::i]=ta;
                    dp[j]=e[::i][j]-ta;
                }
            }
    printf("%d\n",ans);
    for(i=1;i<=n;++i)
        if(i!=a && i!=b)
            dp[i]=1e20;
    q.insert(pdi(dp[a],a));
    if(a!=b)
        q.insert(pdi(dp[b],b));
    if(a!=b)
        pre[b]=a;
    while(!q.empty())
    {
        k=q.begin()->second;
        q.erase(q.begin());
        if(done[k])
            continue;
        done[k]=true;
        for(i=1;i<=n;++i)
            if(e[k][i]!=inf && dp[k]+e[k][i]<dp[i])
            {
                dp[i]=dp[k]+e[k][i];
                q.insert(pdi(dp[i],i));
                pre[i]=k;
            }
    }
    vt[0].resize(0);
    for(i=1;i<=n;++i)
        if(pre[i])
            if(i<pre[i])
                printf("%d %d\n",i,pre[i]);
            else
                printf("%d %d\n",pre[i],i);
    return 0;
}
