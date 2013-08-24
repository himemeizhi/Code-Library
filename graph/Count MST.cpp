//hdu 4408
#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXX 111

long long mod;
long long a[MAXX][MAXX];

inline long long det(int n)
{
    static int i,j,k;
    static long long re,t;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            a[i][j]%=mod;
    re=1ll;
    for(i=0;i<n;++i)
    {
        for(j=i+1;j<n;++j)
            while(a[j][i])
            {
                t=a[i][i]/a[j][i];
                for(k=i;k<n;++k)
                    a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                for(k=i;k<n;++k)
                    std::swap(a[i][k],a[j][k]);
                re=-re;
            }
        if(!a[i][i])
            return 0ll;
        re=re*a[i][i]%mod;
    }
    return (re+mod)%mod;
}

struct E
{
    int a,b,c;
    bool operator<(const E &i)const
    {
        return c<i.c;
    }
}edge[1111];

int set[2][MAXX];
int find(int a,int t)
{
    return set[t][a]?set[t][a]=find(set[t][a],t):a;
}

int id[MAXX],dg[MAXX];
int map[MAXX][MAXX];
int n,m,i,j,k;
long long ans;
int cnt;

int main()
{
    while(scanf("%d %d %lld",&n,&m,&mod),(n||m||mod))
    {
        for(i=0;i<m;++i)
            scanf("%d %d %d",&edge[i].a,&edge[i].b,&edge[i].c);
        std::sort(edge,edge+m);
        memset(set[0],0,sizeof set[0]);
        ans=cnt=1;
        for(i=0;i<m;i=j)
        {
            for(j=i;j<m;++j)
                if(edge[i].c!=edge[j].c)
                    break;
            memset(dg,0,sizeof dg);
            memset(map,0,sizeof map);
            memset(set[1],0,sizeof set[0]);
            static int t,x,y;
            t=0;
            for(k=i;k<j;++k)
            {
                x=find(edge[k].a,0);
                y=find(edge[k].b,0);
                if(x!=y)
                {
                    ++map[x][y];
                    ++map[y][x];
                    ++dg[x];
                    ++dg[y];
                    x=find(x,1);
                    y=find(y,1);
                    if(x!=y)
                        set[1][x]=y;
                    ++t;
                }
            }
            for(k=i;k<j;++k)
            {
                x=find(edge[k].a,0);
                y=find(edge[k].b,0);
                if(x!=y)
                {
                    ++cnt;
                    set[0][x]=y;
                }
            }
            if(t)
            {
                for(k=1;k<=n;++k)
                    if(dg[k] && find(k,1)==k)
                    {
                        memset(a,0,sizeof a);
                        t=0;
                        static int ii,jj;
                        for(ii=1;ii<=n;++ii)
                            if(dg[ii] && find(ii,1)==k)
                                id[ii]=t++;
                        for(ii=1;ii<=n;++ii)
                            if(dg[ii] && find(ii,1)==k)
                            {
                                a[id[ii]][id[ii]]=dg[ii];
                                for(jj=1;jj<=n;++jj)
                                {
                                    if(!dg[jj] || ii==jj || find(jj,1)!=k)
                                        continue;
                                    if(map[ii][jj])
                                    {
                                        static long long cnt;
                                        cnt=-map[ii][jj];
                                        a[id[ii]][id[jj]]=(cnt%mod+mod)%mod;
                                    }
                                }
                            }
                        ans=(ans*det(t-1))%mod;
                    }
            }
        }
        if(cnt!=n)
            puts("0");
        else
            printf("%lld\n",(ans%mod+mod)%mod);
    }
    return 0;
}
