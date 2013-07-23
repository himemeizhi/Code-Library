// like Edmonds-Karp Algorithm
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXX 5011
#define MAXE (MAXX*10*2)
#define inf 0x3f3f3f3f

int edge[MAXX],nxt[MAXE],to[MAXE],cap[MAXE],cst[MAXE],cnt;
#define v to[i]
inline void adde(int a,int b,int c,int d)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
    cap[cnt]=c;
    cst[cnt]=d;
}
inline void add(int a,int b,int c,int d)
{ adde(a,b,c,d);adde(b,a,0,-d);}

int dist[MAXX],pre[MAXX];
int source,sink;
std::queue<int>q;
bool in[MAXX];

inline bool go()
{
    static int now,i;
    memset(dist,0x3f,sizeof dist);
    dist[source]=0;
    pre[source]=-1;
    q.push(source);
    in[source]=true;
    while(!q.empty())
    {
        in[now=q.front()]=false;
        q.pop();
        for(i=edge[now];i!=-1;i=nxt[i])
            if(cap[i] && dist[v]>dist[now]+cst[i])
            {
                dist[v]=dist[now]+cst[i];
                pre[v]=i;
                if(!in[v])
                {
                    q.push(v);
                    in[v]=true;
                }
            }
    }
    return dist[sink]!=inf;
}

inline int mcmf(int &flow)
{
    static int ans,i;
    flow=ans=0;
    while(go())
    {
        static int min;
        min=inf;
        for(i=pre[sink];i!=-1;i=pre[to[i^1]])
            min=std::min(min,cap[i]);
        flow+=min;
        ans+=min*dist[sink];
        for(i=pre[sink];i!=-1;i=pre[to[i^1]])
        {
            cap[i]-=min;
            cap[i^1]+=min;
        }
    }
    return ans;
}

// TQ's version
struct mcmf
{
    struct Edge
    {
        int from,to,cap,flow,cost;
    };
    int n,m,s,t;
    std::vector<Edge>edges;
    std::vector<int>G[maxn];
    int inq[maxn],d[maxn],p[maxn],a[maxn];
    
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n;++i)
            G[i].clear();
        edges.clear();
    }
    
    void addedge(int from,int to,int cap,int cost)
    {
        Edge x={from,to,cap,0,cost};
        edges.push_back(x);
        Edge y={to,from,0,0,-cost};
        edges.push_back(y);
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    int mincost(int s,int t)
    {
        int flow=0,cost=0;
        while(BellmanFord(s,t,flow,cost));
        if(flow!=(n-1)/2)return -1;
        return cost;
    }
private:
    bool BellmanFord(int s,int t,int& flow,int& cost)
    {
        for(int i=0;i<=n;++i)
            d[i]=INF;
        memset(inq,0,sizeof(inq));
        d[s]=0; inq[s]=1; p[s]=0; a[s]=INF;
        std::queue<int>Q;
        Q.push(s);
        while(!Q.empty())
        {
            int u=Q.front();
            Q.pop();
            inq[u]=0;
            for(int i=0;i<G[u].size();++i)
            {
                Edge& e=edges[G[u][i]];
                if(e.cap>e.flow && d[e.to]>d[u]+e.cost)
                {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to])
                    {
                        Q.push(e.to);
                        inq[e.to]=1;
                    }
                }
            }
        }
        if(d[t]==INF)
            return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }

}G;
