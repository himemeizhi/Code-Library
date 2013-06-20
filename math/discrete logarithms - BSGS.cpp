//The running time of BSGS and the space complexity is O(\sqrt{n})
//Pollard's rho algorithm for logarithms' running time is approximately O(\sqrt{p}) where p is n's largest prime factor.
#include<cstdio>
#include<cmath>
#include<cstring>

struct Hash // std::map is bad. clear()时会付出巨大的代价
{
    static const int mod=100003; // prime is good
    static const int MAXX=47111; // bigger than sqrt(c)
    int hd[mod],nxt[MAXX],cnt;
    long long v[MAXX],k[MAXX]; // a^k ≡ v (mod c)
    inline void init()
    {
        memset(hd,0,sizeof hd);
        cnt=0;
    }
    inline long long find(long long v)
    {
        static int now;
        for(now=hd[v%mod];now;now=nxt[now])
            if(this->v[now]==v)
                return k[now];
        return -1ll;
    }
    inline void insert(long long k,long long v)
    {
        if(find(v)!=-1ll)
            return;
        nxt[++cnt]=hd[v%mod];
        hd[v%mod]=cnt;
        this->v[cnt]=v;
        this->k[cnt]=k;
    }
}hash;

long long gcd(long long a,long long b)
{
    return b?gcd(b,a%b):a;
}

long long exgcd(long long a,long long b,long long &x,long long &y)
{
    if(b)
    {
        long long re(exgcd(b,a%b,x,y)),tmp(x);
        x=y;
        y=tmp-(a/b)*y;
        return re;
    }
    x=1ll;
    y=0ll;
    return a;
}

inline long long bsgs(long long a,long long b,long long c) // a^x ≡ b (mod c)
{
    static long long x,y,d,g,m,am,k;
    static int i,cnt;
    a%=c;
    b%=c;
    x=1ll%c; // if c==1....
    for(i=0;i<100;++i) 
    {
        if(x==b)
            return i;
        x=(x*a)%c;
    }
    d=1ll%c;
    cnt=0;
    while((g=gcd(a,c))!=1ll)
    {
        if(b%g)
            return -1ll;
        ++cnt;
        c/=g;
        b/=g;
        d=a/g*d%c;
    }
    hash.init();
    m=sqrt((double)c); // maybe need a ceil
    am=1ll%c;
    hash.insert(0,am);
    for(i=1;i<=m;++i)
    {
        am=am*a%c;
        hash.insert(i,am);
    }
    for(i=0;i<=m;++i)
    {
        g=exgcd(d,c,x,y);
        x=(x*b/g%c+c)%c;
        k=hash.find(x);
        if(k!=-1ll)
            return i*m+k+cnt;
        d=d*am%c;
    }
    return -1ll;
}

long long k,p,n;

int main()
{
    while(scanf("%lld %lld %lld",&k,&p,&n)!=EOF)
    {
        if(n>p || (k=bsgs(k,n,p))==-1ll)
            puts("Orz,I can’t find D!");
        else
            printf("%lld\n",k);
    }
    return 0;
}
