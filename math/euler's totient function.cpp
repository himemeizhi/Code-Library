对正整数n，欧拉函数φ是少于或等于n的数中与n互质的数的数目。
φ函数的值通式：φ(x)=x(1-1/p1)(1-1/p2)(1-1/p3)(1-1/p4)……(1-1/pn),其中p1, p2……pn为x的所有质因数，x是不为0的整数。
φ(1)=1（唯一和1互质的数就是1本身）。
若m,n互质，φ(mn)=φ(m)φ(n)。 

inline long long phi(int n)
{
    static int i,j;
    static int re;
    re=n;
    j=sqrt((double)n);
    for(i=0;prm[i]<=j;++i)
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
