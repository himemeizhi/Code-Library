#define maxn 2008
struct Twosat
{
    int n;
    std::vector<int>G[maxn*2];
    bool mark[maxn*2];
    int s[maxn*2],c;

    bool dfs(int x)
    {
        if(mark[x^1])return false;
        if(mark[x])return true;
        mark[x]=true;
        s[c++]=x;
        for(int i=0;i<G[x].size();++i)
            if(!dfs(G[x][i]))return false;
        return true;
    }

    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;++i)
            G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    void add_clause(int x,int xval,int y,int yval)//增加一条子句
    {
        x=x*2+xval;
        y=y*2+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve()
    {
        for(int i=0;i<n*2;i+=2)
            if(!mark[i]&&!mark[i+1])
            {
                c=0;
                if(!dfs(i))
                {
                    while(c>0)
                        mark[s[--c]]=false;
                    if(!dfs(i+1))
                        return false;
                }
            }
        return true;
    }
};
