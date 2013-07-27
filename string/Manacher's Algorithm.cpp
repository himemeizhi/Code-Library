#include<cstdio>
#include<vector>

#define MAXX 1111

std::vector<char>str;
char buf[MAXX];
int z[MAXX<<1];
int i,j,l,r;
int ii,n,c;

inline int match(const int &a,const int &b)
{
    int i(0);
    while(a-i>=0 && b+i<str.size() && str[a-i]==str[b+i])//注意是i不是1，打错过很多次了
        ++i;
    return i;
}

int main()
{
    gets(buf);
    str.reserve(MAXX<<1);
    for(i=0;buf[i];++i)
    {
        str.push_back('$');
        str.push_back(buf[i]);
    }
    str.push_back('$');

    z[0]=1;
    c=l=r=0;
    for(i=1;i<str.size();++i)
    {
        ii=(l<<1)-i;
        n=r+1-i;

        if(i>r)
        {
            z[i]=match(i,i);
            l=i;
            r=i+z[i]-1;
        }
        else
            if(z[ii]==n)
            {
                z[i]=n+match(i-n,i+n);
                l=i;
                r=i+z[i]-1;
            }
            else
                z[i]=std::min(z[ii],n);
        if(z[i]>z[c])
            c=i;
    }

    for(i=c-z[c]+2,n=c+z[c];i<n;i+=2)
        putchar(str[i]);
    puts("");
    return 0;
}

//package:

inline int match(const int a,const int b,const std::vector<int> &str)
{
    static int i;
    i=0;
    while(a-i>=0 && b+i<str.size() && str[a-i]==str[b+i])
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

inline bool check(int *z,int a,int b) //检查子串[a,b]是否回文
{    
    a=a*2-1;
    b=b*2-1;
    int m=(a+b)/2;
    return z[m]>=b-m+1;
}

