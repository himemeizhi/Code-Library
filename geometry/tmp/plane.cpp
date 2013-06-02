struct plane
{
    point3 a,b,c,o;
    plane(){}
    plane(point3 _a,point3 _b,point3 _c)
    {
        a=_a;
        b=_b;
        c=_c;
        o=pvec();
    }
    plane(double _a,double _b,double _c,double _d)
    {
    	//ax+by+cz+d=0
    	o=point3(_a,_b,_c);
		if (dblcmp(_a)!=0)
		{
			a=point3((-_d-_c-_b)/_a,1,1);
		}
		else if (dblcmp(_b)!=0)
		{
			a=point3(1,(-_d-_c-_a)/_b,1);
		}
		else if (dblcmp(_c)!=0)
		{
			a=point3(1,1,(-_d-_a-_b)/_c);
		}
    }
    void input()
    {
        a.input();
        b.input();
        c.input();
        o=pvec();
    }
    point3 pvec()
    {
        return b.sub(a).det(c.sub(a));
    }
	bool pointonplane(point3 p)//点是否在平面上 
    {
    	return dblcmp(p.sub(a).dot(o))==0;
    }
    //0 不在
	//1 在边界上
	//2 在内部 
    int pointontriangle(point3 p)//点是否在空间三角形abc上 
    {
    	if (!pointonplane(p))return 0;
    	double s=a.sub(b).det(c.sub(b)).len();
    	double s1=p.sub(a).det(p.sub(b)).len();
    	double s2=p.sub(a).det(p.sub(c)).len();
    	double s3=p.sub(b).det(p.sub(c)).len();
    	if (dblcmp(s-s1-s2-s3))return 0;
    	if (dblcmp(s1)&&dblcmp(s2)&&dblcmp(s3))return 2;
    	return 1;
    }
    //判断两平面关系  
    //0 相交
    //1 平行但不重合 
    //2 重合 
    bool relationplane(plane f)
    {
        if (dblcmp(o.det(f.o).len()))return 0;
        if (pointonplane(f.a))return 2;
        return 1;
    }
    double angleplane(plane f)//两平面夹角
    {
    	return acos(o.dot(f.o)/(o.len()*f.o.len()));
    }
    double dispoint(point3 p)//点到平面距离
	{
		return fabs(p.sub(a).dot(o)/o.len());
	}
    point3 pttoplane(point3 p)//点到平面最近点
	{
		line3 u=line3(p,p.add(o));
		crossline(u,p);
		return p;
	}
    int crossline(line3 u,point3 &p)//平面和直线的交点 
    {
    	double x=o.dot(u.b.sub(a));
    	double y=o.dot(u.a.sub(a));
    	double d=x-y;
    	if (dblcmp(fabs(d))==0)return 0;
    	p=u.a.mul(x).sub(u.b.mul(y)).div(d);
    	return 1;
    }
    int crossplane(plane f,line3 &u)//平面和平面的交线 
    {
    	point3 oo=o.det(f.o);
    	point3 v=o.det(oo);
    	double d=fabs(f.o.dot(v));
    	if (dblcmp(d)==0)return 0;
    	point3 q=a.add(v.mul(f.o.dot(f.a.sub(a))/d));
    	u=line3(q,q.add(oo));
    	return 1;
    }
};
