#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXN 511
#define MAXM 2500111
#define v to[i]

int set[MAXN];
int find(int a)
{
    return set[a]?set[a]=find(set[a]):a;
}

int n,m,i,j,k,ans;

struct edge
{
    int a,b,c;
    bool in;
    bool operator<(const edge &i)const
    {
        return c<i.c;
    }
}ed[MAXM];

int map[MAXN][MAXN];
bool done[MAXN];

int head[MAXN],to[MAXN<<1],nxt[MAXN<<1],wg[MAXN<<1],cnt;
inline void add(int a,int b,int c)
{
    nxt[++cnt]=head[a];
    head[a]=cnt;
    to[cnt]=b;
    wg[cnt]=c;
}

void dfs(const int now,const int fa)
{
    done[now]=true;
    for(int i(head[now]);i;i=nxt[i])
        if(v!=fa)
        {
            for(int j(1);j<=n;++j)
                if(done[j])
                    map[v][j]=map[j][v]=std::max(map[j][now],wg[i]);
            dfs(v,now);
        }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(i=0;i<m;++i)
        scanf("%d %d %d",&ed[i].a,&ed[i].b,&ed[i].c);
    std::sort(ed,ed+m);
    for(i=0;i<m;++i)
        if(find(ed[i].a)!=find(ed[i].b))
        {
            j+=ed[i].c;
            ++k;
            set[find(ed[i].a)]=find(ed[i].b);
            ed[i].in=true;
            add(ed[i].a,ed[i].b,ed[i].c);
            add(ed[i].b,ed[i].a,ed[i].c);
        }
    if(k+1!=n)
        puts("Cost: -1\nCost: -1");
    else
    {
        printf("Cost: %d\n",j);
        if(m==n-1)
        {
            puts("Cost: -1");
            return 0;
        }
        ans=0x3f3f3f3f;
        memset(map,0x3f,sizeof map);
        for(i=1;i<=n;++i)
            map[i][i]=0;
        dfs(1,0);
        for(i=0;i<m;++i)
            if(!ed[i].in)
                ans=std::min(ans,j+ed[i].c-map[ed[i].a][ed[i].b]);
        printf("Cost: %d\n",ans);
    }
    return 0;
}
