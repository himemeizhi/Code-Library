#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

#define MAXX 50111

struct Q
{
    int l,r,s,w;
    bool operator<(const Q &i)const
    {
        return w==i.w?r<i.r:w<i.w;
    }
}a[MAXX];

int c[MAXX];
long long col[MAXX],sz[MAXX],ans[MAXX];
int n,m,cnt,len;

long long gcd(long long a,long long b)
{
    return a?gcd(b%a,a):b;
}

int i,j,k,now;
long long all,num;

int main()
{
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;++i)
        scanf("%d",c+i);
    len=sqrt(m);
    for(i=1;i<=m;++i)
    {
        scanf("%d %d",&a[i].l,&a[i].r);
        if(a[i].l>a[i].r)
            std::swap(a[i].l,a[i].r);
        sz[i]=a[i].r-a[i].l+1;
        a[i].w=a[i].l/len+1;
        a[i].s=i;
    }
    std::sort(a+1,a+m+1);
    i=1;
    while(i<=m)
    {
        now=a[i].w;
        memset(col,0,sizeof col);
        for(j=a[i].l;j<=a[i].r;++j)
            ans[a[i].s]+=2*(col[c[j]]++);
        for(++i;a[i].w==now;++i)
        {
            ans[a[i].s]=ans[a[i-1].s];
            for(j=a[i-1].r+1;j<=a[i].r;++j)
                ans[a[i].s]+=2*(col[c[j]]++);
            if(a[i-1].l<a[i].l)
                for(j=a[i-1].l;j<a[i].l;++j)
                    ans[a[i].s]-=2*(--col[c[j]]);
            else
                for(j=a[i].l;j<a[i-1].l;++j)
                    ans[a[i].s]+=2*(col[c[j]]++);
        }
    }
    for(i=1;i<=m;++i)
    {
        if(sz[i]==1)
            all=1ll;
        else
            all=sz[i]*(sz[i]-1);
        num=gcd(ans[i],all);
        printf("%lld/%lld\n",ans[i]/num,all/num);
    }
    return 0;
}
