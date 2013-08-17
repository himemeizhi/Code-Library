inline int match(const int a,const int b,const std::vector<int> &str)
{
    static int i;
    i=0;
    while(a-i>=0 && b+i<str.size() && str[a-i]==str[b+i])//`注意是i不是1，打错过很多次了`
        ++i;
    return i;
}

inline void go(int *z,const std::vector<int> &str)
{
    static int c,l,r,i,ii,n;
    z[0]=1;
    c=l=r=0;
    for(i=1;i<str.size();++i)
    {
        ii=(l<<1)-i;
        n=r+1-i;

        if(i>r)
        {
            z[i]=match(i,i,str);
            l=i;
            r=i+z[i]-1;
        }
        else
            if(z[ii]==n)
            {
                z[i]=n+match(i-n,i+n,str);
                l=i;
                r=i+z[i]-1;
            }
            else
                z[i]=std::min(z[ii],n);
        if(z[i]>z[c])
            c=i;
    }
}

inline bool check(int *z,int a,int b) //`检查子串[a,b]是否回文`
{    
    a=a*2-1;
    b=b*2-1;
    int m=(a+b)/2;
    return z[m]>=b-m+1;
}

