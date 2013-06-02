struct line3 
{
	point3 a,b;
	line3(){}
	line3(point3 _a,point3 _b)
    {
        a=_a;
        b=_b;
    }
    bool operator==(line3 v)
    {
    	return (a==v.a)&&(b==v.b);
    }
    void input()
    {
    	a.input();
    	b.input();
    }
    double length()
    {
    	return a.distance(b);
    }
    bool pointonseg(point3 p)
    {
    	return dblcmp(p.sub(a).det(p.sub(b)).len())==0&&dblcmp(a.sub(p).dot(b.sub(p)))<=0;
    }
    double dispointtoline(point3 p)
    {
    	return b.sub(a).det(p.sub(a)).len()/a.distance(b);
    }
    double dispointtoseg(point3 p)
    {
        if (dblcmp(p.sub(b).dot(a.sub(b)))<0||dblcmp(p.sub(a).dot(b.sub(a)))<0)
        {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }
    point3 lineprog(point3 p)
    {
    	return a.add(b.sub(a).trunc(b.sub(a).dot(p.sub(a))/b.distance(a)));
    } 	
    point3 rotate(point3 p,double ang)//p绕此向量逆时针arg角度
	{
		if (dblcmp((p.sub(a).det(p.sub(b)).len()))==0)return p;
		point3 f1=b.sub(a).det(p.sub(a));
		point3 f2=b.sub(a).det(f1);
		double len=fabs(a.sub(p).det(b.sub(p)).len()/a.distance(b));
		f1=f1.trunc(len);f2=f2.trunc(len);
		point3 h=p.add(f2);
		point3 pp=h.add(f1);
		return h.add((p.sub(h)).mul(cos(ang*1.0))).add((pp.sub(h)).mul(sin(ang*1.0)));
	}
};
