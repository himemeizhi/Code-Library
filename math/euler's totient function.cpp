对正整数n，欧拉函数φ是少于或等于n的数中与n互质的数的数目。
φ函数的值通式：φ(x)=x(1-1/p1)(1-1/p2)(1-1/p3)(1-1/p4)……(1-1/pn),其中p1, p2……pn为x的所有质因数，x是不为0的整数。
φ(1)=1（唯一和1互质的数就是1本身）。
若m,n互质，φ(mn)=φ(m)φ(n)。 

inline int Euler(int n)
{
    static int i,ans,j;
    ans=n;
    j=sqrt(n);
    for (i=2; i<=j; ++i)
        if (n%i==0)
        {
            ans = ans-ans/i;
            while (n%i==0) 
                n /= i;
        }
    if (n>1) 
        ans = ans-ans/n;
    return ans;
}

//递推
inline void Euler()
{
    memset(euler,0,sizeof(euler));
    euler[1] = 1;
    static int i,j;
    for (i = 2; i <= 3000000; ++i)
    {
        if (!euler[i])
        {
            for (j = i; j <= 3000000; j += i)
            {
                if (!euler[j])
                    euler[j] = j;
                euler[j] = euler[j]/i*(i-1);
            }
        }
    }
}
