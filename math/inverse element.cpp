inline void getInv2(int x,int mod)
{
    inv[1]=1;
    for (int i=2; i<=x; i++)
        inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
}

long long power(long long x,long long y,int mod)
{
    long long ret=1;
    for (long long a=x%mod; y; y>>=1,a=a*a%mod)
        if (y&1)
            ret=ret*a%mod;
    return ret;
}

inline int getInv(int x,int mod)//mod为素数
{
    return power(x,mod-2);
}
