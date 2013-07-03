#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

#define MAXX 233

bool map[MAXX][MAXX];
std::vector<int>p[MAXX];
int m[MAXX];
int vis[MAXX];
int q[MAXX],*qf,*qb;

int n;

inline void label(int x,int y,int b)
{
    static int i,z;
    for(i=b+1;i<p[x].size();++i)
        if(vis[z=p[x][i]]==1)
        {
            p[z]=p[y];
            p[z].insert(p[z].end(),p[x].rbegin(),p[x].rend()-i);
            vis[z]=0;
            *qb++=z;
        }
}

inline bool bfs(int now)
{
    static int i,x,y,z,b;
    for(i=0;i<n;++i)
        p[i].resize(0);
    p[now].push_back(now);
    memset(vis,-1,sizeof vis);
    vis[now]=0;
    qf=qb=q;
    *qb++=now;

    while(qf<qb)
        for(x=*qf++,y=0;y<n;++y)
            if(map[x][y] && m[y]!=y && vis[y]!=1)
            {
                if(vis[y]==-1)
                    if(m[y]==-1)
                    {
                        for(i=0;i+1<p[x].size();i+=2)
                        {
                            m[p[x][i]]=p[x][i+1];
                            m[p[x][i+1]]=p[x][i];
                        }
                        m[x]=y;
                        m[y]=x;
                        return true;
                    }
                    else
                    {
                        p[z=m[y]]=p[x];
                        p[z].push_back(y);
                        p[z].push_back(z);
                        vis[y]=1;
                        vis[z]=0;
                        *qb++=z;
                    }
                else
                {
                    for(b=0;b<p[x].size() && b<p[y].size() && p[x][b]==p[y][b];++b);
                    --b;
                    label(x,y,b);
                    label(y,x,b);
                }
            }
    return false;
}

int i,j,k;
int ans;

int main()
{
    scanf("%d",&n);
    for(i=0;i<n;++i)
        p[i].reserve(n);
    while(scanf("%d %d",&i,&j)!=EOF)
    {
        --i;
        --j;
        map[i][j]=map[j][i]=true;
    }
    memset(m,-1,sizeof m);
    for(i=0;i<n;++i)
        if(m[i]==-1)
        {
            if(bfs(i))
                ++ans;
            else
                m[i]=i;
        }
    printf("%d\n",ans<<1);
    for(i=0;i<n;++i)
        if(i<m[i])
            printf("%d %d\n",i+1,m[i]+1);
    return 0;
}
