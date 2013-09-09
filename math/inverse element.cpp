inline void getInv2(int x,int mod)
{
    inv[1]=1;
    for (int i=2; i<=x; i++)
        inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
}

long long inv(long long x)// `likes above one`
{    
    return x <= 1ll ? x : (mod - mod / x) * inv(mod % x) % mod;    
}   

inline long long power(long long x,long long y,int mod)
{
    long long ret=1;
    for (long long a=x%mod; y; y>>=1,a=a*a%mod)
        if (y&1)
            ret=ret*a%mod;
    return ret;
}

inline int getInv(int x,int mod)//`mod为素数`
{
    return power(x,mod-2,mod);
}

//`谨慎来说，用exgcd更靠谱`
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

inline int inv(int b,int mod)
{
    static int x,y;
    gcd(b,mod,x,y);
    if(x<0)
        x+=mod;
    return x;
}
