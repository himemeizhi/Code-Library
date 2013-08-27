#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>

#define MAXX 40111

int a[MAXX],b[MAXX];
int n,R;
std::multiset<int>set;

inline bool check(const int g)
{
    static int i,j,k;
    static long long sum;
    static int l,r,q[MAXX],dp[MAXX];
    set.clear();
    q[0]=dp[0]=l=r=sum=0;
    for(j=i=1;i<=n;++i)
    {
        sum+=b[i];
        while(sum>g)
            sum-=b[j++];
        if(j>i)
            return false;
        while(l<r && q[l]<j)
        {
            ++l;
            if(l<r && set.count(dp[q[l-1]]+a[q[l]]))
                set.erase(set.find(dp[q[l-1]]+a[q[l]]));
        }
        while(l<r && a[q[r-1]]<=a[i])
        {
            --r;
            if(l<r && set.count(dp[q[r-1]]+a[q[r]]))
                set.erase(set.find(dp[q[r-1]]+a[q[r]]));
        }
        if(l<r)
            set.insert(dp[q[r-1]]+a[i]);
        q[r++]=i;
        dp[i]=dp[j-1]+a[q[l]];
        if(r-l>1)
            dp[i]=std::min(dp[i],*set.begin());
    }
    return dp[n]<=R;
}

int i,j,k;
long long l,r,mid,ans;

int main()
{
    while(scanf("%d %d",&n,&R)!=EOF)
    {
        l=r=0;
        for(i=1;i<=n;++i)
        {
            scanf("%d %d",a+i,b+i);
            r+=b[i];
        }
        ans=-1;
        while(l<=r)
        {
            mid=l+r>>1;
            if(check(mid))
            {
                ans=mid;
                r=mid-1;
            }
            else
                l=mid+1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
