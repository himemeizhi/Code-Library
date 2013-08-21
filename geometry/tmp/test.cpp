//`三角形:`
//`1. 半周长$P=\frac{a+b+c}{2}$`
//`2. 面积$S=\frac{aH}{2}=\frac{ab\sin(C)}{2}=\sqrt{P\times (P-a)\times (P-b)\times (P-c)}$`
//`3. 中线$Ma=\frac{\sqrt{2(b^2+c^2)-a^2}}{2}=\frac{\sqrt{b^2+c^2+2bc\cos(A)}}{2}$`
//`4. 角平分线$Ta=\frac{\sqrt{bc((b+c)^2-a^2)}}{b+c}=\frac{2bc\cos(\frac{A}{2})}{b+c}$`
//`5. 高线$Ha=b\sin(C)=c\sin(B)=\sqrt{b^2-{\frac{a^2+b^2-c^2}{2a}}^2}$`
//`6. 内切圆半径$r=\frac{S}{P}=\frac{\arcsin(\frac{B}{2})\sin(\frac{C}{2})}{\sin(\frac{B+C}{2})}=4R\sin(\frac{A}{2})\sin(\frac{B}{2})\sin(\frac{C}{2})=\sqrt{\frac{(P-a)(P-b)(P-c)}{P}}=P\tan(\frac{A}{2})\tan(\frac{B}{2})\tan(\frac{C}{2})$`
//`7. 外接圆半径$R=\frac{abc}{4S}=\frac{a}{2\sin(A)}=\frac{b}{2\sin(B)}=\frac{c}{2\sin(C)}$`
//`四边形:`
//`D1,D2 为对角线,M 对角线中点连线,A 为对角线夹角`
//`1. $a^2+b^2+c^2+d^2={D_1}^2+{D_2}^2+4M^2$`
//`2. $S=\frac{D_1D_2\sin(A)}{2}$`
//`(以下对圆的内接四边形)`
//`3. $ac+bd=D_1D_2$`
//`4. $S=\sqrt{(P-a)(P-b)(P-c)(P-d)}$,P 为半周长`
//`正n 边形:`
//`R 为外接圆半径,r 为内切圆半径`
//`1. 中心角$A=\frac{2\pi}{n}$`
//`2. 内角$C=(n-2)\frac{\pi}{n}$`
//`3. 边长$a=2\sqrt{R^2-r^2}=2R\sin(\frac{A}{2})=2r\tan(\frac{A}{2})$`
//`4. 面积$S=\frac{nar}{2}=nr^2\tan(\frac{A}{2})=\frac{nR^2\sin(A)}{2}=\frac{na^2}{4\tan(\frac{A}{2})}$`
//`圆:`
//`1. 弧长$l=rA$`
//`2. 弦长$a=2\sqrt{2hr-h^2}=2r\sin(\frac{A}{2})$`
//`3. 弓形高$h=r-\sqrt{r^2-\frac{a^2}{4}}=r(1-\cos(\frac{A}{2}))=\frac{\arctan(\frac{A}{4})}{2}$`
//`4. 扇形面积$S1=\frac{rl}{2}=\frac{r^2A}{2}$`
//`5. 弓形面积$S2=\frac{rl-a(r-h)}{2}=\frac{r^2(A-\sin(A))}{2}$`
//`棱柱:`
//`1. 体积$V=Ah$,A 为底面积,h 为高`
//`2. 侧面积$S=lp$,l 为棱长,p 为直截面周长`
//`3. 全面积$T=S+2A$`
//`棱锥:`
//`1. 体积$V=\frac{Ah}{3}$,A 为底面积,h 为高`
//`(以下对正棱锥)`
//`2. 侧面积$S=\frac{lp}{2}$,l 为斜高,p 为底面周长`
//`3. 全面积$T=S+A$`
//`棱台:`
//`1. 体积$V=(A_1+A_2+\sqrt{A_1A_2})\frac{h}{3}$,A1.A2 为上下底面积,h 为高`
//`(以下为正棱台)`
//`2. 侧面积$S=\frac{(p_{1}+p_{2})l}{2}$,p1.p2 为上下底面周长,l 为斜高`
//`3. 全面积$T=S+A_1+A_2$`
//`圆柱:`
//`1. 侧面积$S=2\pi rh$`
//`2. 全面积$T=2\pi r(h+r)$`
//`3. 体积$V=\pi r^2h$`
//`圆锥:`
//`1. 母线$l=\sqrt{h^2+r^2}$`
//`2. 侧面积$S=\pi rl$`
//`3. 全面积$T=\pi r(l+r)$`
//`4. 体积$V=\pi r^2\frac{h}{3}$`
//`圆台:`
//`1. 母线$l=\sqrt{h^2+(r_1-r_2)^2}$`
//`2. 侧面积$S=\pi(r_1+r_2)l$`
//`3. 全面积$T=\pi r_1(l+r_1)+\pi r_2(l+r_2)$`
//`4. 体积$V=\pi({r_1}^2+{r_2}^2+{r_1}{r_2})\frac{h}{3}$`
//`球:`
//`1. 全面积$T=4\pi r^2$`
//`2. 体积$V=\pi r^3\frac{4}{3}$`
//`球台:`
//`1. 侧面积$S=2\pi rh$`
//`2. 全面积$T=\pi(2rh+{r_1}^2+{r_2}^2)$`
//`3. 体积V=$\frac{1}{6}\pi h(3({r_1}^2+{r_2}^2)+h^2)$`
//`球扇形:`
//`1. 全面积$T=\pi r(2h+r_0)$,h 为球冠高,r0 为球冠底面半径`
//`2. 体积$V=\frac{2}{3}\pi r^2h$`

//`polygon`
#include <stdlib.h>
#include <math.h>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define _sign(x) ((x)>eps?1:((x)<-eps?2:0))
struct point{double x,y;};
struct line{point a,b;};
double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//`判定凸多边形,顶点按顺时针或逆时针给出,允许相邻边共线`
int is_convex(int n,point* p)
{
    int i,s[3]={1,1,1};
    for (i=0;i<n&&s[1]|s[2];i++)
        s[_sign(xmult(p[(i+1)%n],p[(i+2)%n],p[i]))]=0;
    return s[1]|s[2];
}
//`判定凸多边形,顶点按顺时针或逆时针给出,不允许相邻边共线`
int is_convex_v2(int n,point* p)
{
    int i,s[3]={1,1,1};
    for (i=0;i<n&&s[0]&&s[1]|s[2];i++)
        s[_sign(xmult(p[(i+1)%n],p[(i+2)%n],p[i]))]=0;
    return s[0]&&s[1]|s[2];
}
//`判点在凸多边形内或多边形边上,顶点按顺时针或逆时针给出`
int inside_convex(point q,int n,point* p)
{
    int i,s[3]={1,1,1};
    for (i=0;i<n&&s[1]|s[2];i++)
        s[_sign(xmult(p[(i+1)%n],q,p[i]))]=0;
    return s[1]|s[2];
}
//`判点在凸多边形内,顶点按顺时针或逆时针给出,在多边形边上返回0`
int inside_convex_v2(point q,int n,point* p)
{
    int i,s[3]={1,1,1};
    for (i=0;i<n&&s[0]&&s[1]|s[2];i++)
        s[_sign(xmult(p[(i+1)%n],q,p[i]))]=0;
    return s[0]&&s[1]|s[2];
}
//`判点在任意多边形内,顶点按顺时针或逆时针给出`
//`on\_edge 表示点在多边形边上时的返回值,offset 为多边形坐标上限`
int inside_polygon(point q,int n,point* p,int on_edge=1)
{
    point q2;
    int i=0,count;
    while (i<n)
        for (count=i=0,q2.x=rand()+offset,q2.y=rand()+offset;i<n;i++)
            if
                (zero(xmult(q,p[i],p[(i+1)%n]))&&(p[i].x-q.x)*(p[(i+1)%n].x-q.x)<eps&&(p[i].y-q.y)*(p[(i+1)%n].y-q.y)<eps)
                    return on_edge;
            else if (zero(xmult(q,q2,p[i])))
                break;
            else if
                (xmult(q,p[i],q2)*xmult(q,p[(i+1)%n],q2)<-eps&&xmult(p[i],q,p[(i+1)%n])*xmult(p[i],q2,p[(i+1)%n])<-eps)
                    count++;
    return count&1;
}
inline int opposite_side(point p1,point p2,point l1,point l2)
{
    return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-eps;
}
inline int dot_online_in(point p,point l1,point l2)
{
    return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}
//`判线段在任意多边形内,顶点按顺时针或逆时针给出,与边界相交返回1`
int inside_polygon(point l1,point l2,int n,point* p)
{
    point t[MAXN],tt;
    int i,j,k=0;
    if (!inside_polygon(l1,n,p)||!inside_polygon(l2,n,p))
        return 0;
    for (i=0;i<n;i++)
        if (opposite_side(l1,l2,p[i],p[(i+1)%n])&&opposite_side(p[i],p[(i+1)%n],l1,l2))
            return 0;
        else if (dot_online_in(l1,p[i],p[(i+1)%n]))
            t[k++]=l1;
        else if (dot_online_in(l2,p[i],p[(i+1)%n]))
            t[k++]=l2;
        else if (dot_online_in(p[i],l1,l2))
            t[k++]=p[i];
    for (i=0;i<k;i++)
        for (j=i+1;j<k;j++)
        {
            tt.x=(t[i].x+t[j].x)/2;
            tt.y=(t[i].y+t[j].y)/2;
            if (!inside_polygon(tt,n,p))
                return 0;
        }
    return 1;
}
point intersection(line u,line v)
{
    point ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
        /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}
point barycenter(point a,point b,point c)
{
    line u,v;
    u.a.x=(a.x+b.x)/2;
    u.a.y=(a.y+b.y)/2;
    u.b=c;
    v.a.x=(a.x+c.x)/2;
    v.a.y=(a.y+c.y)/2;
    v.b=b;
    return intersection(u,v);
}
//`多边形重心`
point barycenter(int n,point* p)
{
    point ret,t;
    double t1=0,t2;
    int i;
    ret.x=ret.y=0;
    for (i=1;i<n-1;i++)
        if (fabs(t2=xmult(p[0],p[i],p[i+1]))>eps)
        {
            t=barycenter(p[0],p[i],p[i+1]);
            ret.x+=t.x*t2;
            ret.y+=t.y*t2;
            t1+=t2;
        }
    if (fabs(t1)>eps)
        ret.x/=t1,ret.y/=t1;
    return ret;
}


//`cut polygon`
//`多边形切割`
//`可用于半平面交`
#define MAXN 100
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};
double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int same_side(point p1,point p2,point l1,point l2)
{
    return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}
point intersection(point u1,point u2,point v1,point v2)
{
    point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
        /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
//`将多边形沿l1,l2 确定的直线切割在side 侧切割,保证l1,l2,side 不共线`
void polygon_cut(int& n,point* p,point l1,point l2,point side)
{
    point pp[100];
    int m=0,i;
    for (i=0;i<n;i++)
    {
        if (same_side(p[i],side,l1,l2))
            pp[m++]=p[i];
        if
            (!same_side(p[i],p[(i+1)%n],l1,l2)&&!(zero(xmult(p[i],l1,l2))&&zero(xmult(p[(i+1)%n],l1,l2))))
                pp[m++]=intersection(p[i],p[(i+1)%n],l1,l2);
    }
    for (n=i=0;i<m;i++)
        if (!i||!zero(pp[i].x-pp[i-1].x)||!zero(pp[i].y-pp[i-1].y))
            p[n++]=pp[i];
    if (zero(p[n-1].x-p[0].x)&&zero(p[n-1].y-p[0].y))
        n--;
    if (n<3)
        n=0;
}

//`float`
//`浮点几何函数库`
#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};
struct line{point a,b;};
//`计算cross product (P1-P0)x(P2-P0)`
double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double xmult(double x1,double y1,double x2,double y2,double x0,double y0)
{
    return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}
//`计算dot product (P1-P0).(P2-P0)`
double dmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
double dmult(double x1,double y1,double x2,double y2,double x0,double y0)
{
    return (x1-x0)*(x2-x0)+(y1-y0)*(y2-y0);
}
//`两点距离`
double distance(point p1,point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double distance(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
//`判三点共线`
int dots_inline(point p1,point p2,point p3)
{
    return zero(xmult(p1,p2,p3));
}
int dots_inline(double x1,double y1,double x2,double y2,double x3,double y3)
{
    return zero(xmult(x1,y1,x2,y2,x3,y3));
}
//`判点是否在线段上,包括端点`
int dot_online_in(point p,line l)
{
    return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}
int dot_online_in(point p,point l1,point l2)
{
    return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}
int dot_online_in(double x,double y,double x1,double y1,double x2,double y2)
{
    return zero(xmult(x,y,x1,y1,x2,y2))&&(x1-x)*(x2-x)<eps&&(y1-y)*(y2-y)<eps;
}
//`判点是否在线段上,不包括端点`
int dot_online_ex(point p,line l)
{
    return
        dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y))&&(!zero(p.x-l.b.x)||!zero(p.y-l.b.y));
}
int dot_online_ex(point p,point l1,point l2)
{
    return
        dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y))&&(!zero(p.x-l2.x)||!zero(p.y-l2.y));
}
int dot_online_ex(double x,double y,double x1,double y1,double x2,double y2)
{
    return
        dot_online_in(x,y,x1,y1,x2,y2)&&(!zero(x-x1)||!zero(y-y1))&&(!zero(x-x2)||!zero(y-y2));
}
//`判两点在线段同侧,点在线段上返回0`
int same_side(point p1,point p2,line l)
{
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
int same_side(point p1,point p2,point l1,point l2)
{
    return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}
//`判两点在线段异侧,点在线段上返回0`
int opposite_side(point p1,point p2,line l)
{
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}
int opposite_side(point p1,point p2,point l1,point l2)
{
    return xmult(l1,p1,l2)*xmult(l1,p2,l2)<-eps;
}
//`判两直线平行`
int parallel(line u,line v)
{
    return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}
int parallel(point u1,point u2,point v1,point v2)
{
    return zero((u1.x-u2.x)*(v1.y-v2.y)-(v1.x-v2.x)*(u1.y-u2.y));
}
//`判两直线垂直`
int perpendicular(line u,line v)
{
    return zero((u.a.x-u.b.x)*(v.a.x-v.b.x)+(u.a.y-u.b.y)*(v.a.y-v.b.y));
}
int perpendicular(point u1,point u2,point v1,point v2)
{
    return zero((u1.x-u2.x)*(v1.x-v2.x)+(u1.y-u2.y)*(v1.y-v2.y));
}
//`判两线段相交,包括端点和部分重合`
int intersect_in(line u,line v)
{
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_in(point u1,point u2,point v1,point v2)
{
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
    return
        dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u
                2);
}
//`判两线段相交,不包括端点和部分重合`
int intersect_ex(line u,line v)
{
    return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int intersect_ex(point u1,point u2,point v1,point v2)
{
    return opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);
}
//`计算两直线交点,注意事先判断直线是否平行!`
//`线段交点请另外判线段相交(同时还是要判断是否平行!)`
point intersection(line u,line v)
{
    point ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
        /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}
point intersection(point u1,point u2,point v1,point v2)
{
    point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
        /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
//`点到直线上的最近点`
point ptoline(point p,line l)
{
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    return intersection(p,t,l.a,l.b);
}
point ptoline(point p,point l1,point l2)
{
    point t=p;
    t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
    return intersection(p,t,l1,l2);
}
//`点到直线距离`
double disptoline(point p,line l)
{
    return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
double disptoline(point p,point l1,point l2)
{
    return fabs(xmult(p,l1,l2))/distance(l1,l2);
}
double disptoline(double x,double y,double x1,double y1,double x2,double y2)
{
    return fabs(xmult(x,y,x1,y1,x2,y2))/distance(x1,y1,x2,y2);
}
//`点到线段上的最近点`
point ptoseg(point p,line l)
{
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    if (xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
        return distance(p,l.a)<distance(p,l.b)?l.a:l.b;
    return intersection(p,t,l.a,l.b);
}
point ptoseg(point p,point l1,point l2)
{
    point t=p;
    t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
    if (xmult(l1,t,p)*xmult(l2,t,p)>eps)
        return distance(p,l1)<distance(p,l2)?l1:l2;
    return intersection(p,t,l1,l2);
}
//`点到线段距离`
double disptoseg(point p,line l)
{
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    if (xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
        return distance(p,l.a)<distance(p,l.b)?distance(p,l.a):distance(p,l.b);
    return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
double disptoseg(point p,point l1,point l2)
{
    point t=p;
    t.x+=l1.y-l2.y,t.y+=l2.x-l1.x;
    if (xmult(l1,t,p)*xmult(l2,t,p)>eps)
        return distance(p,l1)<distance(p,l2)?distance(p,l1):distance(p,l2);
    return fabs(xmult(p,l1,l2))/distance(l1,l2);
}
//`矢量V 以P 为顶点逆时针旋转angle 并放大scale 倍`
point rotate(point v,point p,double angle,double scale)
{
    point ret=p;
    v.x-=p.x,v.y-=p.y;
    p.x=scale*cos(angle);
    p.y=scale*sin(angle);
    ret.x+=v.x*p.x-v.y*p.y;
    ret.y+=v.x*p.y+v.y*p.x;
    return ret;
}

//`area`
#include <math.h>
struct point{double x,y;};
//`计算cross product (P1-P0)x(P2-P0)`
double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double xmult(double x1,double y1,double x2,double y2,double x0,double y0)
{
    return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}
//`计算三角形面积,输入三顶点`
double area_triangle(point p1,point p2,point p3)
{
    return fabs(xmult(p1,p2,p3))/2;
}
double area_triangle(double x1,double y1,double x2,double y2,double x3,double y3)
{
    return fabs(xmult(x1,y1,x2,y2,x3,y3))/2;
}
37
//`计算三角形面积,输入三边长`
double area_triangle(double a,double b,double c)
{
    double s=(a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
//`计算多边形面积,顶点按顺时针或逆时针给出`
double area_polygon(int n,point* p)
{
    double s1=0,s2=0;
    int i;
    for (i=0;i<n;i++)
        s1+=p[(i+1)%n].y*p[i].x,s2+=p[(i+1)%n].y*p[(i+2)%n].x;
    return fabs(s1-s2)/2;
}

//`surface of ball`
#include <math.h>
const double pi=acos(-1);
//`计算圆心角lat 表示纬度,-90<=w<=90,lng 表示经度`
//`返回两点所在大圆劣弧对应圆心角,0<=angle<=pi`
double angle(double lng1,double lat1,double lng2,double lat2)
{
    double dlng=fabs(lng1-lng2)*pi/180;
    while (dlng>=pi+pi)
        dlng-=pi+pi;
    if (dlng>pi)
        dlng=pi+pi-dlng;
    lat1*=pi/180,lat2*=pi/180;
    return acos(cos(lat1)*cos(lat2)*cos(dlng)+sin(lat1)*sin(lat2));
}
//`计算距离,r 为球半径`
double line_dist(double r,double lng1,double lat1,double lng2,double lat2)
{
    double dlng=fabs(lng1-lng2)*pi/180;
    while (dlng>=pi+pi)
        dlng-=pi+pi;
    if (dlng>pi)
        dlng=pi+pi-dlng;
    lat1*=pi/180,lat2*=pi/180;
    return r*sqrt(2-2*(cos(lat1)*cos(lat2)*cos(dlng)+sin(lat1)*sin(lat2)));
}
//`计算球面距离,r 为球半径`
inline double sphere_dist(double r,double lng1,double lat1,double lng2,double lat2)
{
    return r*angle(lng1,lat1,lng2,lat2);
}

//`triangle`
#include <math.h>
struct point{double x,y;};
struct line{point a,b;};
double distance(point p1,point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
point intersection(line u,line v)
{
    point ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
        /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}
//`外心`
point circumcenter(point a,point b,point c)
{
    line u,v;
    u.a.x=(a.x+b.x)/2;
    u.a.y=(a.y+b.y)/2;
    u.b.x=u.a.x-a.y+b.y;
    u.b.y=u.a.y+a.x-b.x;
    v.a.x=(a.x+c.x)/2;
    v.a.y=(a.y+c.y)/2;
    v.b.x=v.a.x-a.y+c.y;
    v.b.y=v.a.y+a.x-c.x;
    return intersection(u,v);
}
//`内心`
point incenter(point a,point b,point c)
{
    line u,v;
    double m,n;
    u.a=a;
    m=atan2(b.y-a.y,b.x-a.x);
    n=atan2(c.y-a.y,c.x-a.x);
    u.b.x=u.a.x+cos((m+n)/2);
    u.b.y=u.a.y+sin((m+n)/2);
    v.a=b;
    m=atan2(a.y-b.y,a.x-b.x);
    n=atan2(c.y-b.y,c.x-b.x);
    v.b.x=v.a.x+cos((m+n)/2);
    v.b.y=v.a.y+sin((m+n)/2);
    return intersection(u,v);
}
//`垂心`
point perpencenter(point a,point b,point c)
{
    line u,v;
    u.a=c;
    u.b.x=u.a.x-a.y+b.y;
    u.b.y=u.a.y+a.x-b.x;
    v.a=b;
    v.b.x=v.a.x-a.y+c.y;
    v.b.y=v.a.y+a.x-c.x;
    return intersection(u,v);
}
//`重心`
//`到三角形三顶点距离的平方和最小的点`
//`三角形内到三边距离之积最大的点`
point barycenter(point a,point b,point c)
{
    line u,v;
    u.a.x=(a.x+b.x)/2;
    u.a.y=(a.y+b.y)/2;
    u.b=c;
    v.a.x=(a.x+c.x)/2;
    v.a.y=(a.y+c.y)/2;
    v.b=b;
    return intersection(u,v);
}
//`费马点`
//`到三角形三顶点距离之和最小的点`
point fermentpoint(point a,point b,point c)
{
    point u,v;
    double step=fabs(a.x)+fabs(a.y)+fabs(b.x)+fabs(b.y)+fabs(c.x)+fabs(c.y);
    int i,j,k;
    u.x=(a.x+b.x+c.x)/3;
    u.y=(a.y+b.y+c.y)/3;
    while (step>1e-10)
        for (k=0;k<10;step/=2,k++)
            for (i=-1;i<=1;i++)
                for (j=-1;j<=1;j++)
                {
                    v.x=u.x+step*i;
                    v.y=u.y+step*j;
                    if
                        (distance(u,a)+distance(u,b)+distance(u,c)>distance(v,a)+distance(v,b)+distance(v,c))
                            u=v;
                }
    return u;
}

//`3-d`
//`三维几何函数库`
#include <math.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point3{double x,y,z;};
struct line3{point3 a,b;};
struct plane3{point3 a,b,c;};
//`计算cross product U x V`
point3 xmult(point3 u,point3 v)
{
    point3 ret;
    ret.x=u.y*v.z-v.y*u.z;
    ret.y=u.z*v.x-u.x*v.z;
    ret.z=u.x*v.y-u.y*v.x;
    return ret;
}
//`计算dot product U . V`
double dmult(point3 u,point3 v)
{
    return u.x*v.x+u.y*v.y+u.z*v.z;
}
//`矢量差 U - V`
point3 subt(point3 u,point3 v)
{
    point3 ret;
    ret.x=u.x-v.x;
    ret.y=u.y-v.y;
    ret.z=u.z-v.z;
    return ret;
}
//`取平面法向量`
point3 pvec(plane3 s)
{
    return xmult(subt(s.a,s.b),subt(s.b,s.c));
}
point3 pvec(point3 s1,point3 s2,point3 s3)
{
    return xmult(subt(s1,s2),subt(s2,s3));
}
//`两点距离,单参数取向量大小`
double distance(point3 p1,point3 p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}
//`向量大小`
double vlen(point3 p)
{
    return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}
//`判三点共线`
int dots_inline(point3 p1,point3 p2,point3 p3)
{
    return vlen(xmult(subt(p1,p2),subt(p2,p3)))<eps;
}
//`判四点共面`
int dots_onplane(point3 a,point3 b,point3 c,point3 d)
{
    return zero(dmult(pvec(a,b,c),subt(d,a)));
}
//`判点是否在线段上,包括端点和共线`
int dot_online_in(point3 p,line3 l)
{
    return zero(vlen(xmult(subt(p,l.a),subt(p,l.b))))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&
        (l.a.y-p.y)*(l.b.y-p.y)<eps&&(l.a.z-p.z)*(l.b.z-p.z)<eps;
}
int dot_online_in(point3 p,point3 l1,point3 l2)
{
    return zero(vlen(xmult(subt(p,l1),subt(p,l2))))&&(l1.x-p.x)*(l2.x-p.x)<eps&&
        (l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;
}
//`判点是否在线段上,不包括端点`
int dot_online_ex(point3 p,line3 l)
{
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y)||!zero(p.z-l.a.z))&&
        (!zero(p.x-l.b.x)||!zero(p.y-l.b.y)||!zero(p.z-l.b.z));
}
int dot_online_ex(point3 p,point3 l1,point3 l2)
{
    return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&
        (!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));
}
//`判点是否在空间三角形上,包括边界,三点共线无意义`
int dot_inplane_in(point3 p,plane3 s)
{
    return zero(vlen(xmult(subt(s.a,s.b),subt(s.a,s.c)))-vlen(xmult(subt(p,s.a),subt(p,s.b)))-
            vlen(xmult(subt(p,s.b),subt(p,s.c)))-vlen(xmult(subt(p,s.c),subt(p,s.a))));
}
int dot_inplane_in(point3 p,point3 s1,point3 s2,point3 s3)
{
    return zero(vlen(xmult(subt(s1,s2),subt(s1,s3)))-vlen(xmult(subt(p,s1),subt(p,s2)))-
            vlen(xmult(subt(p,s2),subt(p,s3)))-vlen(xmult(subt(p,s3),subt(p,s1))));
}
//`判点是否在空间三角形上,不包括边界,三点共线无意义`
int dot_inplane_ex(point3 p,plane3 s)
{
    return dot_inplane_in(p,s)&&vlen(xmult(subt(p,s.a),subt(p,s.b)))>eps&&
        vlen(xmult(subt(p,s.b),subt(p,s.c)))>eps&&vlen(xmult(subt(p,s.c),subt(p,s.a)))>eps;
}
int dot_inplane_ex(point3 p,point3 s1,point3 s2,point3 s3)
{
    return dot_inplane_in(p,s1,s2,s3)&&vlen(xmult(subt(p,s1),subt(p,s2)))>eps&&
        vlen(xmult(subt(p,s2),subt(p,s3)))>eps&&vlen(xmult(subt(p,s3),subt(p,s1)))>eps;
}
//`判两点在线段同侧,点在线段上返回0,不共面无意义`
int same_side(point3 p1,point3 p2,line3 l)
{
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))>eps;
}
int same_side(point3 p1,point3 p2,point3 l1,point3 l2)
{
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))>eps;
}
//`判两点在线段异侧,点在线段上返回0,不共面无意义`
int opposite_side(point3 p1,point3 p2,line3 l)
{
    return dmult(xmult(subt(l.a,l.b),subt(p1,l.b)),xmult(subt(l.a,l.b),subt(p2,l.b)))<-eps;
}
int opposite_side(point3 p1,point3 p2,point3 l1,point3 l2)
{
    return dmult(xmult(subt(l1,l2),subt(p1,l2)),xmult(subt(l1,l2),subt(p2,l2)))<-eps;
}
//`判两点在平面同侧,点在平面上返回0`
int same_side(point3 p1,point3 p2,plane3 s)
{
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))>eps;
}
int same_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3)
{
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))>eps;
}
//`判两点在平面异侧,点在平面上返回0`
int opposite_side(point3 p1,point3 p2,plane3 s)
{
    return dmult(pvec(s),subt(p1,s.a))*dmult(pvec(s),subt(p2,s.a))<-eps;
}
int opposite_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3)
{
    return dmult(pvec(s1,s2,s3),subt(p1,s1))*dmult(pvec(s1,s2,s3),subt(p2,s1))<-eps;
}
//`判两直线平行`
int parallel(line3 u,line3 v)
{
    return vlen(xmult(subt(u.a,u.b),subt(v.a,v.b)))<eps;
}
int parallel(point3 u1,point3 u2,point3 v1,point3 v2)
{
    return vlen(xmult(subt(u1,u2),subt(v1,v2)))<eps;
}
//`判两平面平行`
int parallel(plane3 u,plane3 v)
{
    return vlen(xmult(pvec(u),pvec(v)))<eps;
}
int parallel(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3)
{
    return vlen(xmult(pvec(u1,u2,u3),pvec(v1,v2,v3)))<eps;
}
//`判直线与平面平行`
int parallel(line3 l,plane3 s)
{
    return zero(dmult(subt(l.a,l.b),pvec(s)));
}
int parallel(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
{
    return zero(dmult(subt(l1,l2),pvec(s1,s2,s3)));
}
//`判两直线垂直`
int perpendicular(line3 u,line3 v)
{
    return zero(dmult(subt(u.a,u.b),subt(v.a,v.b)));
}
int perpendicular(point3 u1,point3 u2,point3 v1,point3 v2)
{
    return zero(dmult(subt(u1,u2),subt(v1,v2)));
}
//`判两平面垂直`
int perpendicular(plane3 u,plane3 v)
{
    return zero(dmult(pvec(u),pvec(v)));
}
int perpendicular(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3)
{
    return zero(dmult(pvec(u1,u2,u3),pvec(v1,v2,v3)));
}
//`判直线与平面平行`
int perpendicular(line3 l,plane3 s)
{
    return vlen(xmult(subt(l.a,l.b),pvec(s)))<eps;
}
int perpendicular(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
{
    return vlen(xmult(subt(l1,l2),pvec(s1,s2,s3)))<eps;
}
//`判两线段相交,包括端点和部分重合`
int intersect_in(line3 u,line3 v)
{
    if (!dots_onplane(u.a,u.b,v.a,v.b))
        return 0;
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_in(point3 u1,point3 u2,point3 v1,point3 v2)
{
    if (!dots_onplane(u1,u2,v1,v2))
        return 0;
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
    return
        dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u
                2);
}
//`判两线段相交,不包括端点和部分重合`
int intersect_ex(line3 u,line3 v)
{
    return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int intersect_ex(point3 u1,point3 u2,point3 v1,point3 v2)
{
    return
        dots_onplane(u1,u2,v1,v2)&&opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);
}
//`判线段与空间三角形相交,包括交于边界和(部分)包含`
int intersect_in(line3 l,plane3 s)
{
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&
        !same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);
}
int intersect_in(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
{
    return !same_side(l1,l2,s1,s2,s3)&&!same_side(s1,s2,l1,l2,s3)&&
        !same_side(s2,s3,l1,l2,s1)&&!same_side(s3,s1,l1,l2,s2);
}
//`判线段与空间三角形相交,不包括交于边界和(部分)包含`
int intersect_ex(line3 l,plane3 s)
{
    return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&
        opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);
}
int intersect_ex(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
{
    return opposite_side(l1,l2,s1,s2,s3)&&opposite_side(s1,s2,l1,l2,s3)&&
        opposite_side(s2,s3,l1,l2,s1)&&opposite_side(s3,s1,l1,l2,s2);
}
//`计算两直线交点,注意事先判断直线是否共面和平行!`
//`线段交点请另外判线段相交(同时还是要判断是否平行!)`
point3 intersection(line3 u,line3 v)
{
    point3 ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
        /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    ret.z+=(u.b.z-u.a.z)*t;
    return ret;
}
point3 intersection(point3 u1,point3 u2,point3 v1,point3 v2)
{
    point3 ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
        /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    ret.z+=(u2.z-u1.z)*t;
    return ret;
}
//`计算直线与平面交点,注意事先判断是否平行,并保证三点不共线!`
//`线段和空间三角形交点请另外判断`
point3 intersection(line3 l,plane3 s)
{
    point3 ret=pvec(s);
    double t=(ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z))/
        (ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));
    ret.x=l.a.x+(l.b.x-l.a.x)*t;
    ret.y=l.a.y+(l.b.y-l.a.y)*t;
    ret.z=l.a.z+(l.b.z-l.a.z)*t;
    return ret;
}
point3 intersection(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
{
    point3 ret=pvec(s1,s2,s3);
    double t=(ret.x*(s1.x-l1.x)+ret.y*(s1.y-l1.y)+ret.z*(s1.z-l1.z))/
        (ret.x*(l2.x-l1.x)+ret.y*(l2.y-l1.y)+ret.z*(l2.z-l1.z));
    ret.x=l1.x+(l2.x-l1.x)*t;
    ret.y=l1.y+(l2.y-l1.y)*t;
    ret.z=l1.z+(l2.z-l1.z)*t;
    return ret;
}
//`计算两平面交线,注意事先判断是否平行,并保证三点不共线!`
line3 intersection(plane3 u,plane3 v)
{
    line3 ret;
    ret.a=parallel(v.a,v.b,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.a,v.b,u.a,u.b,u.
            c);
    ret.b=parallel(v.c,v.a,u.a,u.b,u.c)?intersection(v.b,v.c,u.a,u.b,u.c):intersection(v.c,v.a,u.a,u.b,u.
            c);
    return ret;
}
line3 intersection(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3)
{
    line3 ret;
    ret.a=parallel(v1,v2,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v1,v2,u1,u2,u3);
    ret.b=parallel(v3,v1,u1,u2,u3)?intersection(v2,v3,u1,u2,u3):intersection(v3,v1,u1,u2,u3);
    return ret;
}
//`点到直线距离`
double ptoline(point3 p,line3 l)
{
    return vlen(xmult(subt(p,l.a),subt(l.b,l.a)))/distance(l.a,l.b);
}
double ptoline(point3 p,point3 l1,point3 l2)
{
    return vlen(xmult(subt(p,l1),subt(l2,l1)))/distance(l1,l2);
}
//`点到平面距离`
double ptoplane(point3 p,plane3 s)
{
    return fabs(dmult(pvec(s),subt(p,s.a)))/vlen(pvec(s));
}
double ptoplane(point3 p,point3 s1,point3 s2,point3 s3)
{
    return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));
}
//`直线到直线距离`
double linetoline(line3 u,line3 v)
{
    point3 n=xmult(subt(u.a,u.b),subt(v.a,v.b));
    return fabs(dmult(subt(u.a,v.a),n))/vlen(n);
}
double linetoline(point3 u1,point3 u2,point3 v1,point3 v2)
{
    point3 n=xmult(subt(u1,u2),subt(v1,v2));
    return fabs(dmult(subt(u1,v1),n))/vlen(n);
}
//`两直线夹角cos 值`
double angle_cos(line3 u,line3 v)
{
    return dmult(subt(u.a,u.b),subt(v.a,v.b))/vlen(subt(u.a,u.b))/vlen(subt(v.a,v.b));
}
double angle_cos(point3 u1,point3 u2,point3 v1,point3 v2)
{
    return dmult(subt(u1,u2),subt(v1,v2))/vlen(subt(u1,u2))/vlen(subt(v1,v2));
}
//`两平面夹角cos 值`
double angle_cos(plane3 u,plane3 v)
{
    return dmult(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));
}
double angle_cos(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3)
{
    return dmult(pvec(u1,u2,u3),pvec(v1,v2,v3))/vlen(pvec(u1,u2,u3))/vlen(pvec(v1,v2,v3));
}
//`直线平面夹角sin 值`
double angle_sin(line3 l,plane3 s)
{
    return dmult(subt(l.a,l.b),pvec(s))/vlen(subt(l.a,l.b))/vlen(pvec(s));
}
double angle_sin(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
{
    return dmult(subt(l1,l2),pvec(s1,s2,s3))/vlen(subt(l1,l2))/vlen(pvec(s1,s2,s3));
}

//`CH`
#include <stdlib.h>
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};
//`计算cross product (P1-P0)x(P2-P0)`
double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//`graham 算法顺时针构造包含所有共线点的凸包,O(nlogn)`
point p1,p2;
int graham_cp(const void* a,const void* b)
{
    double ret=xmult(*((point*)a),*((point*)b),p1);
    return zero(ret)?(xmult(*((point*)a),*((point*)b),p2)>0?1:-1):(ret>0?1:-1);
}
void _graham(int n,point* p,int& s,point* ch)
{
    int i,k=0;
    for (p1=p2=p[0],i=1;i<n;p2.x+=p[i].x,p2.y+=p[i].y,i++)
        if (p1.y-p[i].y>eps||(zero(p1.y-p[i].y)&&p1.x>p[i].x))
            p1=p[k=i];
    p2.x/=n,p2.y/=n;
    p[k]=p[0],p[0]=p1;
    qsort(p+1,n-1,sizeof(point),graham_cp);
    for (ch[0]=p[0],ch[1]=p[1],ch[2]=p[2],s=i=3;i<n;ch[s++]=p[i++])
        for (;s>2&&xmult(ch[s-2],p[i],ch[s-1])<-eps;s--);
}
//`构造凸包接口函数,传入原始点集大小n,点集p(p 原有顺序被打乱!)`
//`返回凸包大小,凸包的点在convex 中`
//`参数maxsize 为1 包含共线点,为0 不包含共线点,缺省为1`
//`参数clockwise 为1 顺时针构造,为0 逆时针构造,缺省为1`
//`在输入仅有若干共线点时算法不稳定,可能有此类情况请另行处理!`
//`不能去掉点集中重合的点`
int graham(int n,point* p,point* convex,int maxsize=1,int dir=1)
{
    point* temp=new point[n];
    int s,i;
    _graham(n,p,s,temp);
    for (convex[0]=temp[0],n=1,i=(dir?1:(s-1));dir?(i<s):i;i+=(dir?1:-1))
        if (maxsize||!zero(xmult(temp[i-1],temp[i],temp[(i+1)%s])))
            convex[n++]=temp[i];
    delete []temp;
    return n;
}

//`Pick's`
#define abs(x) ((x)>0?(x):-(x))
struct point{int x,y;};
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
//`多边形上的网格点个数`
int grid_onedge(int n,point* p)
{
    int i,ret=0;
    for (i=0;i<n;i++)
        ret+=gcd(abs(p[i].x-p[(i+1)%n].x),abs(p[i].y-p[(i+1)%n].y));
    return ret;
}
//`多边形内的网格点个数`
int grid_inside(int n,point* p)
{
    int i,ret=0;
    for (i=0;i<n;i++)
        ret+=p[(i+1)%n].y*(p[i].x-p[(i+2)%n].x);
    return (abs(ret)-grid_onedge(n,p))/2+1;
}

//`circle`
#include <math.h>
#define eps 1e-8
struct point{double x,y;};
double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double distance(point p1,point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double disptoline(point p,point l1,point l2)
{
    return fabs(xmult(p,l1,l2))/distance(l1,l2);
}
point intersection(point u1,point u2,point v1,point v2)
{
    point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
        /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
//`判直线和圆相交,包括相切`
int intersect_line_circle(point c,double r,point l1,point l2)
{
    return disptoline(c,l1,l2)<r+eps;
}
//`判线段和圆相交,包括端点和相切`
int intersect_seg_circle(point c,double r,point l1,point l2)
{
    double t1=distance(c,l1)-r,t2=distance(c,l2)-r;
    point t=c;
    if (t1<eps||t2<eps)
        return t1>-eps||t2>-eps;
    t.x+=l1.y-l2.y;
    t.y+=l2.x-l1.x;
    return xmult(l1,c,t)*xmult(l2,c,t)<eps&&disptoline(c,l1,l2)-r<eps;
}
//`判圆和圆相交,包括相切`
int intersect_circle_circle(point c1,double r1,point c2,double r2)
{
    return distance(c1,c2)<r1+r2+eps&&distance(c1,c2)>fabs(r1-r2)-eps;
}
//`计算圆上到点p 最近点,如p 与圆心重合,返回p 本身`
point dot_to_circle(point c,double r,point p)
{
    point u,v;
    if (distance(p,c)<eps)
        return p;
    u.x=c.x+r*fabs(c.x-p.x)/distance(c,p);
    u.y=c.y+r*fabs(c.y-p.y)/distance(c,p)*((c.x-p.x)*(c.y-p.y)<0?-1:1);
    v.x=c.x-r*fabs(c.x-p.x)/distance(c,p);
    v.y=c.y-r*fabs(c.y-p.y)/distance(c,p)*((c.x-p.x)*(c.y-p.y)<0?-1:1);
    return distance(u,p)<distance(v,p)?u:v;
}
//`计算直线与圆的交点,保证直线与圆有交点`
//`计算线段与圆的交点可用这个函数后判点是否在线段上`
void intersection_line_circle(point c,double r,point l1,point l2,point& p1,point& p2)
{
    point p=c;
    double t;
    p.x+=l1.y-l2.y;
    p.y+=l2.x-l1.x;
    p=intersection(p,c,l1,l2);
    t=sqrt(r*r-distance(p,c)*distance(p,c))/distance(l1,l2);
    p1.x=p.x+(l2.x-l1.x)*t;
    p1.y=p.y+(l2.y-l1.y)*t;
    p2.x=p.x-(l2.x-l1.x)*t;
    p2.y=p.y-(l2.y-l1.y)*t;
}
//`计算圆与圆的交点,保证圆与圆有交点,圆心不重合`
void intersection_circle_circle(point c1,double r1,point c2,double r2,point& p1,point& p2)
{
    point u,v;
    double t;
    t=(1+(r1*r1-r2*r2)/distance(c1,c2)/distance(c1,c2))/2;
    u.x=c1.x+(c2.x-c1.x)*t;
    u.y=c1.y+(c2.y-c1.y)*t;
    v.x=u.x+c1.y-c2.y;
    v.y=u.y-c1.x+c2.x;
    intersection_line_circle(c1,r1,u,v,p1,p2);
}

//`integer`
//`整数几何函数库`
//`注意某些情况下整数运算会出界!`
#define sign(a) ((a)>0?1:(((a)<0?-1:0)))
struct point{int x,y;};
struct line{point a,b;};
//`计算cross product (P1-P0)x(P2-P0)`
int xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int xmult(int x1,int y1,int x2,int y2,int x0,int y0)
{
    return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}
//`计算dot product (P1-P0).(P2-P0)`
int dmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
int dmult(int x1,int y1,int x2,int y2,int x0,int y0)
{
    return (x1-x0)*(x2-x0)+(y1-y0)*(y2-y0);
}
//`判三点共线`
int dots_inline(point p1,point p2,point p3)
{
    return !xmult(p1,p2,p3);
}
int dots_inline(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return !xmult(x1,y1,x2,y2,x3,y3);
}
//`判点是否在线段上,包括端点和部分重合`
int dot_online_in(point p,line l)
{
    return !xmult(p,l.a,l.b)&&(l.a.x-p.x)*(l.b.x-p.x)<=0&&(l.a.y-p.y)*(l.b.y-p.y)<=0;
}
int dot_online_in(point p,point l1,point l2)
{
    return !xmult(p,l1,l2)&&(l1.x-p.x)*(l2.x-p.x)<=0&&(l1.y-p.y)*(l2.y-p.y)<=0;
}
int dot_online_in(int x,int y,int x1,int y1,int x2,int y2)
{
    return !xmult(x,y,x1,y1,x2,y2)&&(x1-x)*(x2-x)<=0&&(y1-y)*(y2-y)<=0;
}
//`判点是否在线段上,不包括端点`
int dot_online_ex(point p,line l)
{
    return dot_online_in(p,l)&&(p.x!=l.a.x||p.y!=l.a.y)&&(p.x!=l.b.x||p.y!=l.b.y);
}
int dot_online_ex(point p,point l1,point l2)
{
    return dot_online_in(p,l1,l2)&&(p.x!=l1.x||p.y!=l1.y)&&(p.x!=l2.x||p.y!=l2.y);
}
int dot_online_ex(int x,int y,int x1,int y1,int x2,int y2)
{
    return dot_online_in(x,y,x1,y1,x2,y2)&&(x!=x1||y!=y1)&&(x!=x2||y!=y2);
}
//`判两点在直线同侧,点在直线上返回0`
int same_side(point p1,point p2,line l)
{
    return sign(xmult(l.a,p1,l.b))*xmult(l.a,p2,l.b)>0;
}
int same_side(point p1,point p2,point l1,point l2)
{
    return sign(xmult(l1,p1,l2))*xmult(l1,p2,l2)>0;
}
//`判两点在直线异侧,点在直线上返回0`
int opposite_side(point p1,point p2,line l)
{
    return sign(xmult(l.a,p1,l.b))*xmult(l.a,p2,l.b)<0;
}
int opposite_side(point p1,point p2,point l1,point l2)
{
    return sign(xmult(l1,p1,l2))*xmult(l1,p2,l2)<0;
}
//`判两直线平行`
int parallel(line u,line v)
{
    return (u.a.x-u.b.x)*(v.a.y-v.b.y)==(v.a.x-v.b.x)*(u.a.y-u.b.y);
}
int parallel(point u1,point u2,point v1,point v2)
{
    return (u1.x-u2.x)*(v1.y-v2.y)==(v1.x-v2.x)*(u1.y-u2.y);
}
//`判两直线垂直`
int perpendicular(line u,line v)
{
    return (u.a.x-u.b.x)*(v.a.x-v.b.x)==-(u.a.y-u.b.y)*(v.a.y-v.b.y);
}
int perpendicular(point u1,point u2,point v1,point v2)
{
    return (u1.x-u2.x)*(v1.x-v2.x)==-(u1.y-u2.y)*(v1.y-v2.y);
}
//`判两线段相交,包括端点和部分重合`
int intersect_in(line u,line v)
{
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
int intersect_in(point u1,point u2,point v1,point v2)
{
    if (!dots_inline(u1,u2,v1)||!dots_inline(u1,u2,v2))
        return !same_side(u1,u2,v1,v2)&&!same_side(v1,v2,u1,u2);
    return
        dot_online_in(u1,v1,v2)||dot_online_in(u2,v1,v2)||dot_online_in(v1,u1,u2)||dot_online_in(v2,u1,u
                2);
}
//`判两线段相交,不包括端点和部分重合`
int intersect_ex(line u,line v)
{
    return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
int intersect_ex(point u1,point u2,point v1,point v2)
{
    return opposite_side(u1,u2,v1,v2)&&opposite_side(v1,v2,u1,u2);
}
