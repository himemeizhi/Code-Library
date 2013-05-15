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