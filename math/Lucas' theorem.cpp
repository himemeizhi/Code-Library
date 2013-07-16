#include <cstdio>
/*
   Lucas 快速求解C(n,m)%p
   */
void gcd(int n,int k,int &x,int &y)
{
    if(k)
    {
        gcd(k,n%k,x,y);
        int t=x;
        x=y;
        y=t-(n/k)*y;
        return;
    }
    x=1;
    y=0;
}

int CmodP(int n,int k,int p)
{
    if(k>n) 
        return 0;
    int a,b,flag=0,x,y;
    a=b=1;
    for(int i=1;i<=k;i++)
    {
        x=n-i+1;
        y=i;
        while(x%p==0)
        {
            x/=p;
            ++flag;
        }
        while(y%p==0)
        {
            y/=p;
            --flag;
        }
        x%=p;
        y%=p;

        a*=x;
        b*=y;

        b%=p;
        a%=p;
    }
    if(flag)
        return 0;
    gcd(b,p,x,y);
    if(x<0)
        x+=p;
    a*=x;
    a%=p;
    return a;
}

//用Lucas 定理求解 C(n,m) % p ,p 是素数
long long Lucas(long long n, long long m, long long p)
{
    long long ans=1;
    while(m && n && ans)
    {
        ans*=(CmodP(n%p,m%p,p));
        ans=ans%p;
        n=n/p;
        m=m/p;
    }
    return ans;
}
int main()
{
    long long n,k,p,ans;
    int cas=0;
    while(scanf("%I64d%I64d%I64d",&n,&k,&p)!=EOF)
    {
        if(k>n-k)
            k=n-k;
        ans=Lucas(n+1,k,p)+n-k;
        printf("Case #%d: %I64d\n",++cas,ans%p);
    }
    return 0;
}

