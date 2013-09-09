//单位圆覆盖
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>

#define eps 1e-8
#define MAXX 211
const double pi(acos(-1));
typedef std::pair<double,int> pdi;

struct pv
{
    double x,y;
    pv(double a=0,double b=0):x(a),y(b){}
    pv operator-(const pv &i)const
    {
        return pv(x-i.x,y-i.y);
    }
    double len()
    {
        return hypot(x,y);
    }
}pnt[MAXX];

std::vector<pdi>alpha(MAXX<<1);

inline int solve(double r) //radius
{
    static int ans,sum,i,j;
    sum=ans=0;
    for(i=0;i<n;++i)
    {
        alpha.resize(0);
        static double d,theta,phi;
        static pv vec;
        for(j=0;j<n;++j)
        {
            if(j==i || (d=(vec=pnt[i]-pnt[j]).len())>2*r+eps)
                continue;
            if((theta=atan2(vec.y,vec.x))<-eps)
                theta+=2*pi;
            phi=acos(d/(2*r));
            alpha.push_back(pdi(theta-phi+2*pi,-1));
            alpha.push_back(pdi(theta+phi+2*pi,1));
        }
        std::sort(alpha.begin(),alpha.end());
        for(j=0;j<alpha.size();++j)
        {
            sum-=alpha[j].second;
            if(sum>ans)
                ans=sum;
        }
    }
    return ans+1;
}
