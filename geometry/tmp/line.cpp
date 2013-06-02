struct line 
{
    point a,b;
    line(){}
    line(point _a,point _b)
    {
        a=_a;
        b=_b;
    }
    bool operator==(line v)
    {
    	return (a==v.a)&&(b==v.b);
    }
    //倾斜角angle 
    line(point p,double angle)
    {
    	a=p;
    	if (dblcmp(angle-pi/2)==0)
    	{
    		b=a.add(point(0,1));
    	}
    	else 
    	{
    		b=a.add(point(1,tan(angle)));
    	}
    }		
    //ax+by+c=0
    line(double _a,double _b,double _c)
    {
    	if (dblcmp(_a)==0)
    	{
    		a=point(0,-_c/_b);
    		b=point(1,-_c/_b);
    	}
    	else if (dblcmp(_b)==0)
    	{
    		a=point(-_c/_a,0);
    		b=point(-_c/_a,1);
    	}
    	else 
    	{
    		a=point(0,-_c/_b);
    		b=point(1,(-_c-_a)/_b);
    	}
    }
    void input()
    {
        a.input();
        b.input();
    }
    void adjust()
    {
    	if (b<a)swap(a,b);
    }
    double length()
    {
        return a.distance(b);
    }
    double angle()//直线倾斜角 0<=angle<180 
	{
		double k=atan2(b.y-a.y,b.x-a.x);
		if (dblcmp(k)<0)k+=pi;
		if (dblcmp(k-pi)==0)k-=pi;
		return k;
	}
    //点和线段关系
    //1 在逆时针
    //2 在顺时针
    //3 平行
    int relation(point p)
    {
        int c=dblcmp(p.sub(a).det(b.sub(a)));
        if (c<0)return 1;
        if (c>0)return 2;
        return 3;
    }
    bool pointonseg(point p)
    {
        return dblcmp(p.sub(a).det(b.sub(a)))==0&&dblcmp(p.sub(a).dot(p.sub(b)))<=0;
    }
    bool parallel(line v)
    {
        return dblcmp(b.sub(a).det(v.b.sub(v.a)))==0;
    }
    //2 规范相交
    //1 非规范相交
    //0 不相交 
    int segcrossseg(line v)
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        int d3=dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
        int d4=dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
        if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
        return (d1==0&&dblcmp(v.a.sub(a).dot(v.a.sub(b)))<=0||
                d2==0&&dblcmp(v.b.sub(a).dot(v.b.sub(b)))<=0||
                d3==0&&dblcmp(a.sub(v.a).dot(a.sub(v.b)))<=0||
                d4==0&&dblcmp(b.sub(v.a).dot(b.sub(v.b)))<=0);        
    }        
    int linecrossseg(line v)//*this seg v line
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        if ((d1^d2)==-2)return 2;
        return (d1==0||d2==0);
    }
    //0 平行
	//1 重合
	//2 相交 
    int linecrossline(line v)
    {
        if ((*this).parallel(v))
        {
            return v.relation(a)==3;
        }
        return 2;
    }
    point crosspoint(line v)
    {
        double a1=v.b.sub(v.a).det(a.sub(v.a));
        double a2=v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }
    double dispointtoline(point p)
    {
        return fabs(p.sub(a).det(b.sub(a)))/length();
    }
    double dispointtoseg(point p)
    {
        if (dblcmp(p.sub(b).dot(a.sub(b)))<0||dblcmp(p.sub(a).dot(b.sub(a)))<0)
        {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }
    point lineprog(point p)
    {
        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
    }
    point symmetrypoint(point p)
    {
    	point q=lineprog(p);
    	return point(2*q.x-p.x,2*q.y-p.y);
    }	
};
