struct polygon 
{
    int n;
    point p[maxp];
    line l[maxp];
    void input()
    {
    	n=4;
    	p[0].input();
    	p[2].input();
    	double dis=p[0].distance(p[2]);
    	p[1]=p[2].rotate(p[0],pi/4);
    	p[1]=p[0].add((p[1].sub(p[0])).trunc(dis/sqrt(2.0)));
    	p[3]=p[2].rotate(p[0],2*pi-pi/4);
    	p[3]=p[0].add((p[3].sub(p[0])).trunc(dis/sqrt(2.0)));
    }
    void add(point q)
    {
    	p[n++]=q;
    }
    void getline()
    {
        for (int i=0;i<n;i++)
        {
            l[i]=line(p[i],p[(i+1)%n]);
        }
    }
    struct cmp
	{
	    point p;
	    cmp(const point &p0){p=p0;}
	    bool operator()(const point &aa,const point &bb)
	    {
	        point a=aa,b=bb;
	        int d=dblcmp(a.sub(p).det(b.sub(p)));
	        if (d==0)
	        {
	            return dblcmp(a.distance(p)-b.distance(p))<0;
	        }
	        return d>0;
	    }
	};
    void norm()
    {
        point mi=p[0];
        for (int i=1;i<n;i++)mi=min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }
    void getconvex(polygon &convex)
    {
        int i,j,k;
        sort(p,p+n);
        convex.n=n;
        for (i=0;i<min(n,2);i++)
        {
            convex.p[i]=p[i];
        }
        if (n<=2)return;
        int &top=convex.n;
        top=1;
        for (i=2;i<n;i++)
        {
            while (top&&convex.p[top].sub(p[i]).det(convex.p[top-1].sub(p[i]))<=0)
                top--;
            convex.p[++top]=p[i];
        }
        int temp=top;
        convex.p[++top]=p[n-2];
        for (i=n-3;i>=0;i--)
        {
            while (top!=temp&&convex.p[top].sub(p[i]).det(convex.p[top-1].sub(p[i]))<=0)
                top--;
            convex.p[++top]=p[i];
        }
    }
    bool isconvex()
    {
    	bool s[3];
    	memset(s,0,sizeof(s));
    	int i,j,k;
    	for (i=0;i<n;i++)
    	{
    		j=(i+1)%n;
    		k=(j+1)%n;
    		s[dblcmp(p[j].sub(p[i]).det(p[k].sub(p[i])))+1]=1;
    		if (s[0]&&s[2])return 0;
    	}
    	return 1;
    }
    //3 点上
	//2 边上
	//1 内部
	//0 外部 
    int relationpoint(point q)
    {
    	int i,j;
    	for (i=0;i<n;i++)
    	{
    		if (p[i]==q)return 3;
    	}
    	getline();
    	for (i=0;i<n;i++)
    	{
    		if (l[i].pointonseg(q))return 2;
    	}
    	int cnt=0;
    	for (i=0;i<n;i++)
		{
			j=(i+1)%n;
			int k=dblcmp(q.sub(p[j]).det(p[i].sub(p[j])));
			int u=dblcmp(p[i].y-q.y);
			int v=dblcmp(p[j].y-q.y);
			if (k>0&&u<0&&v>=0)cnt++;
			if (k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
    }
    //1 在多边形内长度为正 
    //2 相交或与边平行
	//0 无任何交点 
    int relationline(line u)
    {
    	int i,j,k=0;
    	getline();
    	for (i=0;i<n;i++)
    	{
    		if (l[i].segcrossseg(u)==2)return 1;
    		if (l[i].segcrossseg(u)==1)k=1;
    	}
    	if (!k)return 0;
    	vector<point>vp; 
    	for (i=0;i<n;i++)
    	{
    		if (l[i].segcrossseg(u))
    		{
    			if (l[i].parallel(u))
    			{
	    			vp.pb(u.a);
	    			vp.pb(u.b);
	    			vp.pb(l[i].a);
	    			vp.pb(l[i].b);
	    			continue;
    			}
    			vp.pb(l[i].crosspoint(u));
    		}
    	}
    	sort(vp.begin(),vp.end());
    	int sz=vp.size();
    	for (i=0;i<sz-1;i++)
    	{
    		point mid=vp[i].add(vp[i+1]).div(2);
    		if (relationpoint(mid)==1)return 1;
    	}
    	return 2;
    }
    //直线u切割凸多边形左侧 
    //注意直线方向 
    void convexcut(line u,polygon &po)
    {
        int i,j,k;
        int &top=po.n;
        top=0;
        for (i=0;i<n;i++)
        {
            int d1=dblcmp(p[i].sub(u.a).det(u.b.sub(u.a)));
            int d2=dblcmp(p[(i+1)%n].sub(u.a).det(u.b.sub(u.a)));
            if (d1>=0)po.p[top++]=p[i];
            if (d1*d2<0)po.p[top++]=u.crosspoint(line(p[i],p[(i+1)%n]));
        }
    }
    double getcircumference()
    {
        double sum=0;
        int i;
        for (i=0;i<n;i++)
        {
            sum+=p[i].distance(p[(i+1)%n]);
        }
        return sum;
    }
    double getarea()
    {
        double sum=0;
        int i;
        for (i=0;i<n;i++)
        {
            sum+=p[i].det(p[(i+1)%n]);
        }
        return fabs(sum)/2;
    }
    bool getdir()//1代表逆时针 0代表顺时针 
    {
        double sum=0;
        int i;
        for (i=0;i<n;i++)
        {
            sum+=p[i].det(p[(i+1)%n]);
        }
        if (dblcmp(sum)>0)return 1;
        return 0;
    }
    point getbarycentre() // centroid
    {
        point ret(0,0);
        double area=0;
        int i;
        for (i=1;i<n-1;i++)
        {
            double tmp=p[i].sub(p[0]).det(p[i+1].sub(p[0]));
            if (dblcmp(tmp)==0)continue;
            area+=tmp;
            ret.x+=(p[0].x+p[i].x+p[i+1].x)/3*tmp;
            ret.y+=(p[0].y+p[i].y+p[i+1].y)/3*tmp;
        }
        if (dblcmp(area))ret=ret.div(area);
        return ret;
    }
    double areaintersection(polygon po) // refer: HPI
    {
    }
    double areaunion(polygon po)
    {
    	return getarea()+po.getarea()-areaintersection(po);
    }
    double areacircle(circle c)
    {
		int i,j,k,l,m;
		double ans=0;
		for (i=0;i<n;i++)
		{
			int j=(i+1)%n;
			if (dblcmp(p[j].sub(c.p).det(p[i].sub(c.p)))>=0)
			{
				ans+=c.areatriangle(p[i],p[j]);
			}
			else 
			{
				ans-=c.areatriangle(p[i],p[j]);
			}
		}
		return fabs(ans);
    }
    //多边形和圆关系
	//0 一部分在圆外
	//1 与圆某条边相切
	//2 完全在圆内 
    int relationcircle(circle c)
    {
    	getline();
    	int i,x=2;
    	if (relationpoint(c.p)!=1)return 0;
    	for (i=0;i<n;i++)
    	{
    		if (c.relationseg(l[i])==2)return 0;
    		if (c.relationseg(l[i])==1)x=1;
    	}
    	return x;
    }
    void find(int st,point tri[],circle &c)
    {
    	if (!st)
    	{
    		c=circle(point(0,0),-2);
    	}
    	if (st==1)
    	{
    		c=circle(tri[0],0);
    	}
    	if (st==2)
    	{
    		c=circle(tri[0].add(tri[1]).div(2),tri[0].distance(tri[1])/2.0);
    	}
    	if (st==3)
    	{
    		c=circle(tri[0],tri[1],tri[2]);
    	}
    }
    void solve(int cur,int st,point tri[],circle &c)
    {
    	find(st,tri,c);
    	if (st==3)return;
    	int i;
    	for (i=0;i<cur;i++)
    	{
    		if (dblcmp(p[i].distance(c.p)-c.r)>0)
    		{
    			tri[st]=p[i];
    			solve(i,st+1,tri,c);
    		}
    	}
    }
    circle mincircle()//点集最小圆覆盖
	{
		random_shuffle(p,p+n);
		point tri[4];
		circle c;
		solve(n,0,tri,c);
	 	return c;
	}
	int circlecover(double r)//单位圆覆盖 
	{
		int ans=0,i,j;
		vector<pair<double,int> >v;
		for (i=0;i<n;i++)
		{
			v.clear();
			for (j=0;j<n;j++)if (i!=j)
			{
				point q=p[i].sub(p[j]);
				double d=q.len();
				if (dblcmp(d-2*r)<=0)
				{
					double arg=atan2(q.y,q.x);
					if (dblcmp(arg)<0)arg+=2*pi;
					double t=acos(d/(2*r));
					v.push_back(make_pair(arg-t+2*pi,-1));
					v.push_back(make_pair(arg+t+2*pi,1));
				}
			}
			sort(v.begin(),v.end());
			int cur=0;
			for (j=0;j<v.size();j++)
			{
				if (v[j].second==-1)++cur;
				else --cur;
				ans=max(ans,cur);
			}
		}
		return ans+1;
	}			
	int pointinpolygon(point q)//点在凸多边形内部的判定 
	{
		if (getdir())reverse(p,p+n);
		if (dblcmp(q.sub(p[0]).det(p[n-1].sub(p[0])))==0)
		{
			if (line(p[n-1],p[0]).pointonseg(q))return n-1;
			return -1;
		}
		int low=1,high=n-2,mid;
		while (low<=high)
		{
			mid=(low+high)>>1;
			if (dblcmp(q.sub(p[0]).det(p[mid].sub(p[0])))>=0&&dblcmp(q.sub(p[0]).det(p[mid+1].sub(p[0])))<0)
			{
				polygon c;
				c.p[0]=p[mid];
				c.p[1]=p[mid+1];
				c.p[2]=p[0];
				c.n=3;
				if (c.relationpoint(q))return mid;
				return -1;
			}
			if (dblcmp(q.sub(p[0]).det(p[mid].sub(p[0])))>0)
			{
				low=mid+1;
			}
			else 
			{
				high=mid-1;
			}
		}
		return -1;
	}	
};
