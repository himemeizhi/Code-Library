`Euler's totient function:`

`对正整数n，欧拉函数$\varphi$是小于或等于n的数中与n互质的数的数目，也就是对n的简化剩余系的大小。`
` $\varphi$(2)=1（唯一和1互质的数就是1本身）。`
`若m,n互质，$\varphi (m\times n ) = \varphi (m ) \times \varphi (n )$。`
`对于n来说，所有这样的数的和为 $\frac{n\times\varphi (n )}{2}$ 。`
`$gcd(k,n)=d, k\in [1,n]$，这样的k有$\varphi(\frac{n}{d})个$`

inline int phi(int n)
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
     `$a^k \equiv 1 \pmod n$` 

`对m的简化剩余系中的所有x,ord(x)都一定是$\varphi$(m)的一个约数 (aka. Euler's totient theorem)`

`求:`
`method 1、根据定义，对$\varphi$(m)分解素因子之后暴力枚举所有$\varphi$(m)的约数，找到最小的一个d，满足 $x^d \equiv 1 \pmod m$;`
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

`若ord(x)==$\varphi$(m)，则x为m的一个原根`
`因此只需检查所有 $x^d$ \{d为$\varphi$(m)的约数\} 找到使 $x^d \equiv 1 \pmod m$ 的所有d，当且仅当这样的d只有一个，并且为$\varphi$(m)的时候，x是m的一个原根`

`当且仅当m= 1,2,4,$p^n$,$2\times p^n$ \{p为奇质数,n为正整数\} 时，m存在原根 // 应该是指存在对于完全剩余系的原根……？`

`当m存在原根时，原根数目为$\varphi$($\varphi$(m))`

`求：`
`枚举每一个简化剩余系中的数i，若对于i的每一个质因子p[j],$i^{\frac{\varphi (m)}{p[j]}} \not\equiv 1 \pmod m$，那么i为m的一个原根。也就是说，ord(i)==$\varphi$(m)。`
`最小原根通常极小。`

Carmichael function:

`$\lambda$(n) is defined as the smallest positive integer m such that `
    `$a^m \equiv 1 \pmod n$\{ forall a!=1 \&\& gcd(a,n)==1 \}`
`也就是简化剩余系(完全剩余系中存在乘法群中无法得到1的数)中所有x的 lcm\{ord(x)\}`

`if n=$p[0]^{a[0]} \times p[1]^{a[1]} \times ... \times p[m-1]^{a[m-1]}$`
`    then $\lambda$(n)=lcm($\lambda$($p[0]^{a[0]}$),$\lambda$($p[1]^{a[1]}$),...,$\lambda$($p[m-1]^{a[m-1]}$));`

`if n=$2^c \times p[0]^{a[0]} \times p[1]^{a[1]} \times ... \times p[m-1]^{a[m-1]}$`
`    then $\lambda$(n)=lcm($2^c$,$\varphi$($p[0]^{a[0]}$),$\varphi$($p[1]^{a[1]}$),...,$\varphi$($p[m-1]^{a[m-1]}$));`
    { c=0 if a<2; c=1 if a==2; c=a-2 if a>3; }


`Carmichael's theorem:`
`if gcd(a,n)==1`
`    then $\a^{\lambda (n)} \equiv 1 \pmod n$`
