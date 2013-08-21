#include<cstdio>
#include<algorithm>
#include<vector>

#define MAXX 111
#define N 128

std::vector<char>the[2];
std::vector<int>dp(MAXX),p[N];

int i,j,k;
char buf[MAXX];
int t;

int main()
{
    the[0].reserve(MAXX);
    the[1].reserve(MAXX);
    while(gets(buf),buf[0]!='#')
    {
        the[0].resize(0);
        for(i=0;buf[i];++i)
            the[0].push_back(buf[i]);
        the[1].resize(0);
        gets(buf);
        for(i=0;buf[i];++i)
            the[1].push_back(buf[i]);
        for(i=0;i<N;++i)
            p[i].resize(0);
        for(i=0;i<the[1].size();++i)
            p[the[1][i]].push_back(i);
        dp.resize(1);
        dp[0]=-1;
        for(i=0;i<the[0].size();++i)
            for(j=p[the[0][i]].size()-1;j>=0;--j)
            {
                k=p[the[0][i]][j];
                if(k>dp.back())
                    dp.push_back(k);
                else
                    *std::lower_bound(dp.begin(),dp.end(),k)=k;
            }
        printf("Case #%d: you can visit at most %ld cities.\n",++t,dp.size()-1);
    }
    return 0;
}
