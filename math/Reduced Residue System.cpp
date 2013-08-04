Euler's totient function:

对正整数n，欧拉函数φ是少于或等于n的数中与n互质的数的数目，也就是对n的简化剩余系的大小。
φ(1)=1（唯一和1互质的数就是1本身）。
若m,n互质，φ(mn)=φ(m)φ(n)。 
对于n来说，所有这样的数的和为n*φ(n)/2。

inline long long phi(int n)
{
    static int i;
    static int re;
    re=n;
    for(i=0;prm[i]*prm[i]<=n;++i)
        if(n%prm[i]==0)
        {
            re-=re/prm[i];
            do
                n/=prm[i];
            while(n%prm[i]==0);
        }
    if(n!=1)
        re-=re/n;
    return re;
}

inline void Euler()
{
    static int i,j;
    phi[1]=1;
    for(i=2;i<MAXX;++i)
        if(!phi[i])
            for(j=i;j<MAXX;j+=i)
            {
                if(!phi[j])
                    phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
}

Multiplicative order:

the multiplicative order of a modulo n is the smallest positive integer k with
     a^k ≡ 1 (mod n). 

对m的简化剩余系中的所有x,ord(x)都一定是φ(m)的一个约数 (aka. Euler's totient theorem)

求:
method 1、根据定义，对φ(m)分解素因子之后暴力枚举所有φ(m)的约数，找到最小的一个d，满足 pow(x,d,m)==1;
method 2、
inline long long ord(long long x,long long m)
{
    static long long ans;
    static int i,j;
    ans=phi(m);
    for(i=0;i<fac.size();++i)
        for(j=0;j<fac[i].second && pow(x,ans/fac[i].first,m)==1ll;++j)
            ans/=fac[i].first;
    return ans;
}


Primitive root:

若ord(x)==φ(m)，则x为m的一个原根
因此只需检查所有 pow(x,d) {d为φ(m)的约数} 找到使 pow(x,d)%m==1 的所有d，当且仅当这样的d只有一个，并且为φ(m)的时候，x是m的一个原根

当且仅当m= 1,2,4,pow(p,n),2*pow(p,n) {p为奇质数,n为正整数} 时，m存在原根 // 应该是指存在对于完全剩余系的原根……？

当m存在原根时，原根数目为φ(φ(m))

求：
枚举每一个简化剩余系中的数i，若对于i的每一个质因子p[j],pow(i,φ(m)/p[j])%m都不为1，那么i为m的一个原根。也就是说，ord(i)==φ(m)。
最小原根通常极小。

Carmichael function:

λ(n) is defined as the smallest positive integer m such that 
    pow(a,m)%n==1 { for a!=1 && gcd(a,n)==1 }
也就是简化剩余系(完全剩余系中存在乘法群中无法得到1的数)中所有x的 lcm{ord(x)}

if n=pow(p[0],a[0])*pow(p[1],a[1])*...*pow(p[m-1],a[m-1])
    then λ(n)=lcm(λ(pow(p[0],a[0])),λ(pow(p[1],a[1])),...,λ(pow(p[m-1],a[m-1])));

if n=pow(2,a)*pow(p[0],a[0])*pow(p[1],a[1])*...*pow(p[m-1],a[m-1])
    then λ(n)=lcm(pow(2,c),φ(pow(p[0],a[0])),φ(pow(p[1],a[1])),...,φ(pow(p[m-1],a[m-1])));
    { c=0 if a<2; c=1 if a==2; c=a-2 if a>3; }


Carmichael's theorem:
if gcd(a,n)==1
    then pow(a,λ(n))%n==1
