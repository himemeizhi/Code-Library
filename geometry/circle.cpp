//单位圆覆盖
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>

#define MAXX 333
#define  eps 1e-8

struct pv
{
    double x,y;
    pv(){}
    pv(const double &xx,const double &yy):x(xx),y(yy){}
    inline pv operator-(const pv &i)const
    {
        return pv(x-i.x,y-i.y);
    }
    inline double cross(const pv &i)const
    {
        return x*i.y-y*i.x;
    }
    inline void print()
    {
        printf("%lf %lf\n",x,y);
    }
    inline double len()
    {
        return sqrt(x*x+y*y);
    }
}pnt[MAXX];

struct node
{
    double k;
    bool flag;
    node(){}
    node(const double &kk,const bool &ff):k(kk),flag(ff){}
    inline bool operator<(const node &i)const
    {
        return k<i.k;
    }
};

std::vector<node>alpha;

short n,i,j,k,l;
short ans,sum;
double R=2;
double theta,phi,d;
const double pi(acos(-1.0));

int main()
{
    alpha.reserve(MAXX<<1);
    while(scanf("%hd",&n),n)
    {
        for(i=0;i<n;++i)
            scanf("%lf %lf",&pnt[i].x,&pnt[i].y);
        ans=0;
        for(i=0;i<n;++i)
        {
            alpha.resize(0);
            for(j=0;j<n;++j)
                if(i!=j)
                {
                    if((d=(pnt[i]-pnt[j]).len())>R)
                        continue;
                    if((theta=atan2(pnt[j].y-pnt[i].y,pnt[j].x-pnt[i].x))<0)
                        theta+=2*pi;
                    phi=acos(d/R);
                    alpha.push_back(node(theta-phi,true));
                    alpha.push_back(node(theta+phi,false));
                }
            std::sort(alpha.begin(),alpha.end());
            for(j=0;j<alpha.size();++j)
            {
                if(alpha[j].flag)
                    ++sum;
                else
                    --sum;
                ans=std::max(ans,sum);
            }
        }
        printf("%hd\n",ans+1);
    }
    return 0;
}

//最小覆盖圆

#include<cstdio>
#include<cmath>

#define MAXX 511
#define eps 1e-8

struct pv
{
    double x,y;
    pv(){}
    pv(const double &xx,const double &yy):x(xx),y(yy){}
    inline pv operator-(const pv &i)const
    {
        return pv(x-i.x,y-i.y);
    }
    inline pv operator+(const pv &i)const
    {
        return pv(x+i.x,y+i.y);
    }
    inline double cross(const pv &i)const
    {
        return x*i.y-y*i.x;
    }
    inline double len()
    {
        return sqrt(x*x+y*y);
    }
    inline pv operator/(const double &a)const
    {
        return pv(x/a,y/a);
    }
    inline pv operator*(const double &a)const
    {
        return pv(x*a,y*a);
    }
}pnt[MAXX],o,tl,lt,aa,bb,cc,dd;

short n,i,j,k,l;
double r,u;

inline pv ins(const pv &a1,const pv &a2,const pv &b1,const pv &b2)
{
    tl=a2-a1;
    lt=b2-b1;
    u=(b1-a1).cross(lt)/(tl).cross(lt);
    return a1+tl*u;
}

inline pv get(const pv &a,const pv &b,const pv &c)
{
    aa=(a+b)/2;
    bb.x=aa.x-a.y+b.y;
    bb.y=aa.y+a.x-b.x;
    cc=(a+c)/2;
    dd.x=cc.x-a.y+c.y;
    dd.y=cc.y+a.x-c.x;
    return ins(aa,bb,cc,dd);
}

int main()
{
    while(scanf("%hd",&n),n)
    {
        for(i=0;i<n;++i)
            scanf("%lf %lf",&pnt[i].x,&pnt[i].y);
        o=pnt[0];
        r=0;
        for(i=1;i<n;++i)
            if((pnt[i]-o).len()>r+eps)
            {
                o=pnt[i];
                r=0;
                for(j=0;j<i;++j)
                    if((pnt[j]-o).len()>r+eps)
                    {
                        o=(pnt[i]+pnt[j])/2;
                        r=(o-pnt[j]).len();
                        for(k=0;k<j;++k)
                            if((o-pnt[k]).len()>r+eps)
                            {
                                o=get(pnt[i],pnt[j],pnt[k]);
                                r=(o-pnt[i]).len();
                            }
                    }
            }
        printf("%.2lf %.2lf %.2lf\n",o.x,o.y,r);
    }
    return 0;
}

//两原面积交
double dis(int x,int y)
{
    return sqrt((double)(x*x+y*y));
}

double area(int x1,int y1,int x2,int y2,double r1,double r2)
{
    double s=dis(x2-x1,y2-y1);
    if(r1+r2<s) return 0;
    else if(r2-r1>s) return PI*r1*r1;
    else if(r1-r2>s) return PI*r2*r2;
    double q1=acos((r1*r1+s*s-r2*r2)/(2*r1*s));
    double q2=acos((r2*r2+s*s-r1*r1)/(2*r2*s));
    return (r1*r1*q1+r2*r2*q2-r1*s*sin(q1));
}

//三角形外接圆
{
    for (int i = 0; i < 3; i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    tp = pv((p[0].x+p[1].x)/2,(p[0].y+p[1].y)/2);
    l[0] = Line(tp,pv(tp.x-(p[1].y-p[0].y),tp.y+(p[1].x-p[0].x)));
    tp = pv((p[0].x+p[2].x)/2,(p[0].y+p[2].y)/2);
    l[1] = Line(tp,pv(tp.x-(p[2].y-p[0].y),tp.y+(p[2].x-p[0].x)));
    tp = LineToLine(l[0],l[1]);
    r = pv(tp,p[0]).Length();
    printf("(%.6f,%.6f,%.6f)\n",tp.x,tp.y,r);
}

//三角形内切圆
{
    for (int i = 0; i < 3; i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    if (xmult(pv(p[0],p[1]),pv(p[0],p[2])) < 0)
        swap(p[1],p[2]);
    for (int i = 0; i < 3; i++)
        len[i] = pv(p[i],p[(i+1)%3]).Length();
    tr = (len[0]+len[1]+len[2])/2;
    r = sqrt((tr-len[0])*(tr-len[1])*(tr-len[2])/tr);
    for (int i = 0; i < 2; i++)
    {
        v = pv(p[i],p[i+1]);
        tv = pv(-v.y,v.x);
        tr = tv.Length();
        tv = pv(tv.x*r/tr,tv.y*r/tr);
        tp = pv(p[i].x+tv.x,p[i].y+tv.y);
        l[i].s = tp;
        tp = pv(p[i+1].x+tv.x,p[i+1].y+tv.y);
        l[i].e = tp;
    }
    tp = LineToLine(l[0],l[1]);
    printf("(%.6f,%.6f,%.6f)\n",tp.x,tp.y,r);
}
