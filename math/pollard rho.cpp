#include<cstdio>
#include<cstdlib>
#include<list>

short T;
unsigned long long a;
std::list<unsigned long long>fac;

inline unsigned long long multi_mod(const unsigned long long &a,unsigned long long b,const unsigned long long &n)
{
    unsigned long long exp(a%n),tmp(0);
    while(b)
    {
        if(b&1)
        {
            tmp+=exp;
            if(tmp>n)
                tmp-=n;
        }
        exp<<=1;
        if(exp>n)
            exp-=n;
        b>>=1;
    }
    return tmp;
}

inline unsigned long long exp_mod(unsigned long long a,unsigned long long b,const unsigned long long &c)
{
    unsigned long long tmp(1);
    while(b)
    {
        if(b&1)
            tmp=multi_mod(tmp,a,c);
        a=multi_mod(a,a,c);
        b>>=1;
    }
    return tmp;
}

inline bool miller_rabbin(const unsigned long long &n,short T)
{
    if(n==2)
        return true;
    if(n<2 || !(n&1))
        return false;
    unsigned long long a,u(n-1),x,y;
    short t(0),i;
    while(!(u&1))
    {
        ++t;
        u>>=1;
    }
    while(T--)
    {
        a=rand()%(n-1)+1;
        x=exp_mod(a,u,n);
        for(i=0;i<t;++i)
        {
            y=multi_mod(x,x,n);
            if(y==1 && x!=1 && x!=n-1)
                return false;
            x=y;
        }
        if(y!=1)
            return false;
    }
    return true;
}

unsigned long long gcd(const unsigned long long &a,const unsigned long long &b)
{
    return b?gcd(b,a%b):a;
}

inline unsigned long long pollar_rho(const unsigned long long n,const unsigned long long &c)
{
    unsigned long long x(rand()%(n-1)+1),y,d,i(1),k(2);
    y=x;
    while(true)
    {
        ++i;
        x=(multi_mod(x,x,n)+c)%n;
        d=gcd((x-y+n)%n,n);
        if(d>1 && d<n)
            return d;
        if(x==y)
            return n;
        if(i==k)
        {
            k<<=1;
            y=x;
        }
    }
}

void find(const unsigned long long &n,short c)
{
    if(n==1)
        return;
    if(miller_rabbin(n,6))
    {
        fac.push_back(n);
        return;
    }
    unsigned long long p(n);
    short k(c);
    while(p>=n)
        p=pollar_rho(p,c--);
    find(p,k);
    find(n/p,k);
}

int main()
{
    scanf("%hd",&T);
    while(T--)
    {
        scanf("%llu",&a);
        fac.clear();
        find(a,120);
        if(fac.size()==1)
            puts("Prime");
        else
        {
            fac.sort();
            printf("%llu\n",fac.front());
        }
    }
    return 0;
}
