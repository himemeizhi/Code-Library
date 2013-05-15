struct pv
{
	double x,y,z;
	pv() {}
	pv(double xx,double yy,double zz):x(xx),y(yy),z(zz)	{}
	pv operator -(const pv& b)const
	{
		return pv(x-b.x,y-b.y,z-b.z);
	}
	pv operator *(const pv& b)const
	{
		return pv(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);
	}
	double operator &(const pv& b)const
	{
		return x*b.x+y*b.y+z*b.z;
	}
};

//模
double Norm(pv p)
{
	return sqrt(p&p);
}

//`绕单位向量V旋转theta角度`
pv Trans(pv pa,pv V,double theta)
{
    double s = sin(theta);
    double c = cos(theta);
    double x,y,z;
    x = V.x;
    y = V.y;
    z = V.z;
    pv pp =
        pv(
                (x*x*(1-c)+c)*pa.x+(x*y*(1-c)-z*s)*pa.y+(x*z*(1-c)+y*s)*pa.z,
                (y*x*(1-c)+z*s)*pa.x+(y*y*(1-c)+c)*pa.y+(y*z*(1-c)-x*s)*pa.z,
                (x*z*(1-c)-y*s)*pa.x+(y*z*(1-c)+x*s)*pa.y+(z*z*(1-c)+c)*pa.z
          );
    return pp;
}

//经纬度转换

x=r*sin(θ)*cos(α);
y=r*sin(θ)*sin(α);
z=r*cos(θ);

r=sqrt(x*2+y*2+z*2);//??
r=sqrt(x^2+y^2+z^2);//??

α=atan(y/x);
θ=acos(z/r);

r∈[0,∞]
α∈[0,2π]
θ∈[0,π]

lat1∈[-π/2,π/2]
lng1∈[-π,π]

pv getpv(double lat,double lng,double r)
{
	lat += pi/2;
	lng += pi;
	return
    pv(r*sin(lat)*cos(lng),r*sin(lat)*sin(lng),r*cos(lat));
}

//经纬度球面距离

#include<cstdio>
#include<cmath>

#define MAXX 1111

char buf[MAXX];
const double r=6875.0/2,pi=acos(-1.0);
double a,b,c,x1,x2,y2,ans;

int main()
{
    double y1;
    while(gets(buf)!=NULL)
    {
        gets(buf);
        gets(buf);

        scanf("%lf^%lf'%lf\" %s\n",&a,&b,&c,buf);
        x1=a+b/60+c/3600;
        x1=x1*pi/180;
        if(buf[0]=='S')
            x1=-x1;

        scanf("%s",buf);
        scanf("%lf^%lf'%lf\" %s\n",&a,&b,&c,buf);
        y1=a+b/60+c/3600;
        y1=y1*pi/180;
        if(buf[0]=='W')
            y1=-y1;

        gets(buf);

        scanf("%lf^%lf'%lf\" %s\n",&a,&b,&c,buf);
        x2=a+b/60+c/3600;
        x2=x2*pi/180;
        if(buf[0]=='S')
            x2=-x2;

        scanf("%s",buf);
        scanf("%lf^%lf'%lf\" %s\n",&a,&b,&c,buf);
        y2=a+b/60+c/3600;
        y2=y2*pi/180;
        if(buf[0]=='W')
            y2=-y2;

        ans=acos(cos(x1)*cos(x2)*cos(y1-y2)+sin(x1)*sin(x2))*r;
        printf("The distance to the iceberg: %.2lf miles.\n",ans);
        if(ans+0.005<100)
            puts("DANGER!");

        gets(buf);
    }
    return 0;
}

inline bool ZERO(const double &a)
{
    return fabs(a)<eps;
}

//三维向量是否为零
inline bool ZERO(pv p)
{ 
    return (ZERO(p.x) && ZERO(p.y) && ZERO(p.z)); 
} 

//直线相交
bool LineIntersect(Line3D L1, Line3D L2) 
{ 
    pv s = L1.s-L1.e; 
    pv e = L2.s-L2.e; 
    pv p  = s*e; 
    if (ZERO(p)) 
        return false;    //是否平行 
    p = (L2.s-L1.e)*(L1.s-L1.e); 
    return ZERO(p&L2.e);         //是否共面 
} 

//线段相交
bool inter(pv a,pv b,pv c,pv d)
{
    pv ret = (a-b)*(c-d);
    pv t1 = (b-a)*(c-a);
    pv t2 = (b-a)*(d-a);
    pv t3 = (d-c)*(a-c);
    pv t4 = (d-c)*(b-c);
    return sgn(t1&ret)*sgn(t2&ret) < 0 && sgn(t3&ret)*sgn(t4&ret) < 0;
}

//点在直线上
bool OnLine(pv p, Line3D L)
{ 
    return ZERO((p-L.s)*(L.e-L.s)); 
} 

//点在线段上
bool OnSeg(pv p, Line3D L)
{ 
    return (ZERO((L.s-p)*(L.e-p)) && EQ(Norm(p-L.s)+Norm(p-L.e),Norm(L.e-L.s))); 
} 

//点到直线距离
double Distance(pv p, Line3D L)
{ 
    return (Norm((p-L.s)*(L.e-L.s))/Norm(L.e-L.s)); 
} 

//线段夹角
//范围值为[0,π]之间的弧度
double Inclination(Line3D L1, Line3D L2) 
{ 
    pv u = L1.e - L1.s; 
    pv v = L2.e - L2.s; 
    return acos( (u & v) / (Norm(u)*Norm(v)) ); 
} 
