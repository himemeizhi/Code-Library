#include<cstdio>
#include<cstring>
#include<vector>

#define MAXX 1111

int T;
int n,m,p,i,j,k;
std::vector<int>the[2];
int dp[MAXX],path[MAXX];
int ans[MAXX];

int main()
{
    the[0].reserve(MAXX);
    the[1].reserve(MAXX);
    {
        scanf("%d",&n);
        the[0].resize(n);
        for(i=0;i<n;++i)
            scanf("%d",&the[0][i]);
        scanf("%d",&m);
        the[1].resize(m);
        for(i=0;i<m;++i)
            scanf("%d",&the[1][i]);
        memset(dp,0,sizeof dp);
        for(i=0;i<the[0].size();++i)
        {
            n=0;
            p=-1;
            for(j=0;j<the[1].size();++j)
            {
                if(the[0][i]==the[1][j] && n+1>dp[j])
                {
                    dp[j]=n+1;
                    path[j]=p;
                }
                if(the[1][j]<the[0][i] && n<dp[j])
                {
                    n=dp[j];
                    p=j;
                }
            }
        }
        n=0;
        p=-1;
        for(i=0;i<the[1].size();++i)
            if(dp[i]>n)
                n=dp[p=i];
        printf("%d\n",n);
        for(i=n-1;i>=0;--i)
        {
            ans[i]=the[1][p];
            p=path[p];
        }
        for(i=0;i<n;++i)
            printf("%d ",ans[i]);
        puts("");
    }
    return 0;
}
