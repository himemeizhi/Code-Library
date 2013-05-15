#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define maxn 1005
#define INF 1<<30
using namespace std;
struct Edge
{
	int from,to,cap,flow;
};
vector<Edge>edges;
vector<int>G[maxn];
int num[maxn],p[maxn],n,m;
int st[maxn],et[maxn],nt[maxn];
int d[maxn],s,t,cur[maxn];
void addedge(int from,int to,int cap)
{
    struct Edge x={from,to,cap,0};
	edges.push_back(x);
	struct Edge y={to,from,0,0};
	edges.push_back(y);
	int m=edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
}
void bfs()//一次BFS求出每个点到汇点的“距离”
{
	queue<int>q;
	memset(d,0,sizeof(d));
	d[t]=1;
	q.push(t);
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(int i=0;i<G[u].size();++i)
		if(G[u][i]&1)
		{
			Edge& e=edges[G[u][i]];
			if(!d[e.to])
			{
				d[e.to]=d[u]+1;
				q.push(e.to);
			}
		}
	}
}
int augment()//找到一条增广路，增广
{
	int u=t, a=INF;
	while(u!=s)
	{
		Edge& e=edges[p[u]];
		a=min(a,e.cap-e.flow);//增广流量等于增广路径上残余流量最小的一条边
		u=e.from;
	}
	u=t;
	while(u!=s)
	{
		edges[p[u]].flow+=a;
		edges[p[u]^1].flow-=a;
		u=edges[p[u]].from;
	}
	return a;
}
int sap()
{
	int flow=0;
	bfs();
	memset(num,0,sizeof(num));
	for(int i=0;i<=t;++i)num[d[i]]++;
	int u=s;
	memset(cur,0,sizeof(cur));
	while(d[s]<t)
	{
		if(u==t)
		{
			flow+=augment();
			u=s;
		}
		int ok=0;
		for(int i=cur[u];i<G[u].size();++i)
		{
			Edge& e=edges[G[u][i]];
			if(e.cap>e.flow && d[u]==d[e.to]+1)
			{
				ok=1;
				p[e.to]=G[u][i];
				cur[u]=i;
				u=e.to;
				break;
			}
		}
		if(!ok)//当前图没有可增广的路，改变距离标记
		{
			int m=t-1;
			for(int i=0;i<G[u].size();++i)
			{
				Edge& e=edges[G[u][i]];
				if(e.cap>e.flow) m=min(m,d[e.to]);
			}
			if(--num[d[u]]==0)break;//gap优化
			num[d[u]=m+1]++;
			cur[u]=0;//重新构图以后当前弧指向第一条边
			if(u!=s)u=edges[p[u]].from;
		}
	}
	return flow;
}
void init()
{
 edges.clear();
 for(int i=0;i<maxn;++i)G[i].clear();
}
int main()
{
    int T, i;
  //      freopen("1.txt","r",stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        s=0;  t=-1;
        int res=0;
        init();
        for(i=1;i<=n;++i)
        {
            scanf("%d%d%d",&st[i],&et[i],&nt[i]);
            res+=nt[i];
            if(et[i]+n+1>t)t=et[i]+n+1;
        }
        for (i=1; i<=n; ++i)
        {
            int j;
            addedge(s,i,nt[i]);
            for(j=st[i];j<=et[i];++j) addedge(i,j+n,1);
        }
        for(i=n+1;i<t;++i) addedge(i,t,m);
        int ans = sap();
        if(ans==res)printf("Yaha, Garfield, You Finish it!\n");
        else printf("Oh~~Garfield, You are just as before!\n");
    }
	return 0;
}
