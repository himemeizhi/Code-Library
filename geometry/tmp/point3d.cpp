struct point3 
{
	double x,y,z;
	point3(){}
	point3(double _x,double _y,double _z):
	x(_x),y(_y),z(_z){};
	void input()
	{
		scanf("%lf%lf%lf",&x,&y,&z);
	}
	void output()
	{
		printf("%.2lf %.2lf %.2lf\n",x,y,z);
	}
	bool operator==(point3 a)
    {
        return dblcmp(a.x-x)==0&&dblcmp(a.y-y)==0&&dblcmp(a.z-z)==0;
    }
    bool operator<(point3 a)const
    {
        return dblcmp(a.x-x)==0?dblcmp(y-a.y)==0?dblcmp(z-a.z)<0:y<a.y:x<a.x;
    }
	double len()
    {
        return sqrt(len2());
    }
    double len2()
    {
        return x*x+y*y+z*z;
    }
    double distance(point3 p)
    {
        return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)+(p.z-z)*(p.z-z));
    }
    point3 add(point3 p)
    {
        return point3(x+p.x,y+p.y,z+p.z);
    }
    point3 sub(point3 p)
    {
        return point3(x-p.x,y-p.y,z-p.z);
    }
	point3 mul(double d)
	{
		return point3(x*d,y*d,z*d);
	}
	point3 div(double d)
	{
		return point3(x/d,y/d,z/d);
	}
	double dot(point3 p)
    {
        return x*p.x+y*p.y+z*p.z;
    }
    point3 det(point3 p)
    {
        return point3(y*p.z-p.y*z,p.x*z-x*p.z,x*p.y-p.x*y);
    }
    double rad(point3 a,point3 b)
    {
    	point3 p=(*this);
    	return acos(a.sub(p).dot(b.sub(p))/(a.distance(p)*b.distance(p)));
    }
    point3 trunc(double r)
    {
        r/=len();
        return point3(x*r,y*r,z*r);
    }
    point3 rotate(point3 o,double r) // building?
    {
    }
};
