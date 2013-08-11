#include<cstdio>
#include<cstring>
#include<complex>
#include<vector>
#include<algorithm>

#define MAXX 100111
#define MAXN (MAXX<<2)

int T;
int n,i,j,k;

typedef std::complex<long double> com;
std::vector<com>x(MAXN);
int a[MAXX];
long long pre[MAXN],cnt[MAXN];
long long ans;

inline void fft(std::vector<com> &y,int sign)
{
    static int i,j,k,h;
    static com u,t,w,wn;
    for(i=1,j=y.size()/2;i+1<y.size();++i)
    {
        if(i<j)
            std::swap(y[i],y[j]);
        k=y.size()/2;
        while(j>=k)
        {
            j-=k;
            k/=2;
        }
        if(j<k)
            j+=k;
    }
    for(h=2;h<=y.size();h<<=1)
    {
        wn=com(cos(-sign*2*M_PI/h),sin(-sign*2*M_PI/h));
        for(j=0;j<y.size();j+=h)
        {
            w=com(1,0);
            for(k=j;k<j+h/2;++k)
            {
                u=y[k];
                t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w*=wn;
            }
        }
    }
    if(sign==-1)
        for(i=0;i<y.size();++i)
            y[i]=com(y[i].real()/y.size(),y[i].imag());
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(cnt,0,sizeof cnt);
        scanf("%d",&n);
        for(i=0;i<n;++i)
        {
            scanf("%d",a+i);
            ++cnt[a[i]];
        }
        std::sort(a,a+n);
        k=a[n-1]+1;
        for(j=1;j<(k<<1);j<<=1);// size must be such many
        x.resize(0);
        for(i=0;i<k;++i)
            x.push_back(com(cnt[i],0));
        x.insert(x.end(),j-k,com(0,0));

        fft(x,1);
        for(i=0;i<x.size();++i)
            x[i]=x[i]*x[i];
        fft(x,-1);
        /*
        if we need to combine 2 arrays
        fft(x,1);
        fft(y,1);
        for(i=0;i<x.size();++i)
            x[i]=x[i]*y[i];
        fft(x,-1);
        */

        for(i=0;i<x.size();++i)
            cnt[i]=ceil(x[i].real()); //  maybe we need (x[i].real()+0.5f) or nearbyint(x[i].real())
        x.resize(2*a[n-1]); // result here
    }
    return 0;
}
