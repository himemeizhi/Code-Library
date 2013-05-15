#include<cstring>
#include<queue>

#define MAX 1000111
#define N 26

int nxt[MAX][N],fal[MAX],cnt;
bool ed[MAX];
char buf[MAX];

inline void init(int a)
{
    memset(nxt[a],0,sizeof(nxt[0]));
    fal[a]=0;
    ed[a]=false;
}

inline void insert()
{
    static int i,p;
    for(i=p=0;buf[i];++i)
    {
        if(!nxt[p][map[buf[i]]])
            init(nxt[p][map[buf[i]]]=++cnt);
        p=nxt[p][map[buf[i]]];
    }
    ed[p]=true;
}

inline void make()
{
    static std::queue<int>q;
    int i,now,p;
    q.push(0);
    while(!q.empty())
    {
        now=q.front();
        q.pop();
        for(i=0;i<N;++i)
            if(nxt[now][i])
            {
                q.push(p=nxt[now][i]);
                if(now)
                    fal[p]=nxt[fal[now]][i];
                ed[p]|=ed[fal[p]];
            }
            else
                nxt[now][i]=nxt[fal[now]][i];
    }
}
