// hdu 4612
#include<cstdio>
#include<algorithm>
#include<set>
#include<cstring>
#include<stack>
#include<queue>

#define MAXX 200111
#define MAXE (1000111*2)
#pragma comment(linker, "/STACK:16777216")

int edge[MAXX],to[MAXE],nxt[MAXE],cnt;
#define v to[i]
inline void add(int a,int b)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
}

int dfn[MAXX],low[MAXX],col[MAXX],belong[MAXX];
int idx,bcnt;
std::stack<int>st;

void tarjan(int now,int last)
{
    col[now]=1;
    st.push(now);
    dfn[now]=low[now]=++idx;
    bool flag(false);
    for(int i(edge[now]);i;i=nxt[i])
    {
        if(v==last && !flag)
        {
            flag=true;
            continue;
        }
        if(!col[v])
        {
            tarjan(v,now);
            low[now]=std::min(low[now],low[v]);
            /*
            if(low[v]>dfn[now])
            then this is a bridge
            */
        }
        else
            if(col[v]==1)
                low[now]=std::min(low[now],dfn[v]);
    }
    col[now]=2;
    if(dfn[now]==low[now])
    {
        ++bcnt;
        static int x;
        do
        {
            x=st.top();
            st.pop();
            belong[x]=bcnt;
        }while(x!=now);
    }
}

std::set<int>set[MAXX];

int dist[MAXX];
std::queue<int>q;
int n,m,i,j,k;

inline int go(int s)
{
    static std::set<int>::const_iterator it;
    memset(dist,0x3f,sizeof dist);
    dist[s]=0;
    q.push(s);
    while(!q.empty())
    {
        s=q.front();
        q.pop();
        for(it=set[s].begin();it!=set[s].end();++it)
            if(dist[*it]>dist[s]+1)
            {
                dist[*it]=dist[s]+1;
                q.push(*it);
            }
    }
    return std::max_element(dist+1,dist+1+bcnt)-dist;
}

int main()
{
    while(scanf("%d %d",&n,&m),(n||m))
    {
        cnt=0;
        memset(edge,0,sizeof edge);
        while(m--)
        {
            scanf("%d %d",&i,&j);
            add(i,j);
            add(j,i);
        }

        memset(dfn,0,sizeof dfn);
        memset(belong,0,sizeof belong);
        memset(low,0,sizeof low);
        memset(col,0,sizeof col);
        bcnt=idx=0;
        while(!st.empty())
            st.pop();

        tarjan(1,-1);
        for(i=1;i<=bcnt;++i)
            set[i].clear();
        for(i=1;i<=n;++i)
            for(j=edge[i];j;j=nxt[j])
                set[belong[i]].insert(belong[to[j]]);
        for(i=1;i<=bcnt;++i)
            set[i].erase(i);
        /*
        printf("%d\n",dist[go(go(1))]);
        for(i=1;i<=bcnt;++i)
            printf("%d\n",dist[i]);
        puts("");
        */
        printf("%d\n",bcnt-1-dist[go(go(1))]);
    }
    return 0;
}
