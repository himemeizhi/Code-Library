//if every point connect with not less than [(N+1)/2] points
#include<cstdio>
#include<algorithm>
#include<cstring>

#define MAXX 177
#define MAX (MAXX*MAXX)

int edge[MAXX],nxt[MAX],to[MAX],cnt;

inline void add(int a,int b)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
}

bool done[MAXX];
int n,m,i,j,k;

inline int find(int a)
{
    static int i;
    for(i=edge[a];i;i=nxt[i])
        if(!done[to[i]])
        {
            edge[a]=nxt[i];
            return to[i];
        }
    return 0;
}

int a,b;
int next[MAXX],pre[MAXX];
bool mat[MAXX][MAXX];

int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        for(i=1;i<=n;++i)
            next[i]=done[i]=edge[i]=0;
        memset(mat,0,sizeof mat);
        cnt=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            add(i,j);
            add(j,i);
            mat[i][j]=mat[j][i]=true;
        }
        a=1;
        b=to[edge[a]];
        cnt=2;
        done[a]=done[b]=true;
        next[a]=b;
        while(cnt<n)
        {
            while(i=find(a))
            {
                next[i]=a;
                done[a=i]=true;
                ++cnt;
            }
            while(i=find(b))
            {
                next[b]=i;
                done[b=i]=true;
                ++cnt;
            }
            if(!mat[a][b])
                for(i=next[a];next[i]!=b;i=next[i])
                    if(mat[a][next[i]] && mat[i][b])
                    {
                        for(j=next[i];j!=b;j=next[j])
                            pre[next[j]]=j;
                        for(j=b;j!=next[i];j=pre[j])
                            next[j]=pre[j];
                        std::swap(next[i],b);
                        break;
                    }
            next[b]=a;
            for(i=a;i!=b;i=next[i])
                if(find(i))
                {
                    a=next[b=i];
                    break;
                }
        }
        while(a!=b)
        {
            printf("%d ",a);
            a=next[a];
        }
        printf("%d\n",b);
    }
    return 0;
}
