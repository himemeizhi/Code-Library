#include<cstdio>
#include<cstring>

#define MAXX 111

bool Map[MAXX][MAXX],visit[MAXX];
int link[MAXX],n,m;
bool dfs(int t)
{
    for (int i=0; i<m; i++)
        if (!visit[i] && Map[t][i]){
            visit[i] = true;
            if (link[i]==-1 || dfs(link[i])){
                link[i] = t;
                return true;
            }
        }
    return false;
}
int main()
{
    int k,a,b,c;
    while (scanf("%d",&n),n){
        memset(Map,false,sizeof(Map));
        scanf("%d%d",&m,&k);
        while (k--){
            scanf("%d%d%d",&a,&b,&c);
            if (b && c)
                Map[b][c] = true;
        }
        memset(link,-1,sizeof(link));
        int ans = 0;
        for (int i=0; i<n; i++){
            memset(visit,false,sizeof(visit));
            if (dfs(i))
                ans++;
        }
        printf("%d\n",ans);
    }
}
