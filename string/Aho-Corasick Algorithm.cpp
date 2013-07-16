//trie graph
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
                nxt[now][i]=nxt[fal[now]][i]; // 使用本身的trie存串的时候注意nxt已被重载
    }
}

// normal version

#define N 128

char buf[MAXX];
int cnt[1111];

struct node
{
    node *fal,*nxt[N];
    int idx;
    node() { memset(this,0,sizeof node); }
}*rt;
std::queue<node*>Q;

void free(node *p)
{
    for(int i(0);i<N;++i)
        if(p->nxt[i])
            free(p->nxt[i]);
    delete p;
}

inline void add(char *s,int idx)
{
    static node *p;
    for(p=rt;*s;++s)
    {
        if(!p->nxt[*s])
            p->nxt[*s]=new node();
        p=p->nxt[*s];
    }
    p->idx=idx;
}

inline void make()
{
    Q.push(rt);
    static node *p,*q;
    static int i;
    while(!Q.empty())
    {
        p=Q.front();
        Q.pop();
        for(i=0;i<N;++i)
            if(p->nxt[i])
            {
                q=p->fal;
                while(q)
                {
                    if(q->nxt[i])
                    {
                        p->nxt[i]->fal=q->nxt[i];
                        break;
                    }
                    q=q->fal;
                }
                if(!q)
                    p->nxt[i]->fal=rt;
                Q.push(p->nxt[i]);
            }
    }
}

inline void match(const char *s)
{
    static node *p,*q;
    for(p=rt;*s;++s)
    {
        while(p!=rt && !p->nxt[*s])
            p=p->fal;
        p=p->nxt[*s];
        if(!p)
            p=rt;
        for(q=p;q!=rt && q->idx;q=q->fal) // why q->idx ? looks like not necessary at all, I delete it in an other solution
            ++cnt[q->idx];
    }
}

//可以考虑dfs一下，拉直fal指针来跳过无效的匹配
//在线调整关键字存在性的时候，可以考虑欧拉序压扁之后使用BIT或者线段树进行区间修改
