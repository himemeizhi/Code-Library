struct polygons
{
	vector<polygon>p;
	polygons()
	{
		p.clear();
	}
	void clear()
	{
		p.clear();
	}
	void push(polygon q)
	{
		if (dblcmp(q.getarea()))p.pb(q);
	}
	vector<pair<double,int> >e;
	void ins(point s,point t,point X,int i)
	{
		double r=fabs(t.x-s.x)>eps?(X.x-s.x)/(t.x-s.x):(X.y-s.y)/(t.y-s.y);
		r=min(r,1.0);r=max(r,0.0);
		e.pb(mp(r,i));
	}
	double polyareaunion()
	{
		double ans=0.0;
		int c0,c1,c2,i,j,k,w;
		for (i=0;i<p.size();i++)
		{
			if (p[i].getdir()==0)reverse(p[i].p,p[i].p+p[i].n);
		}
		for (i=0;i<p.size();i++)
		{
			for (k=0;k<p[i].n;k++)
			{
				point &s=p[i].p[k],&t=p[i].p[(k+1)%p[i].n];
				if (!dblcmp(s.det(t)))continue;
				e.clear();
				e.pb(mp(0.0,1));
				e.pb(mp(1.0,-1));
				for (j=0;j<p.size();j++)if (i!=j)
				{
					for (w=0;w<p[j].n;w++)
					{
						point a=p[j].p[w],b=p[j].p[(w+1)%p[j].n],c=p[j].p[(w-1+p[j].n)%p[j].n];
						c0=dblcmp(t.sub(s).det(c.sub(s)));
						c1=dblcmp(t.sub(s).det(a.sub(s)));
						c2=dblcmp(t.sub(s).det(b.sub(s)));
						if (c1*c2<0)ins(s,t,line(s,t).crosspoint(line(a,b)),-c2);
						else if (!c1&&c0*c2<0)ins(s,t,a,-c2);
						else if (!c1&&!c2)
						{
							int c3=dblcmp(t.sub(s).det(p[j].p[(w+2)%p[j].n].sub(s)));
							int dp=dblcmp(t.sub(s).dot(b.sub(a)));
							if (dp&&c0)ins(s,t,a,dp>0?c0*((j>i)^(c0<0)):-(c0<0));
							if (dp&&c3)ins(s,t,b,dp>0?-c3*((j>i)^(c3<0)):c3<0);
						}
					}
				}
				sort(e.begin(),e.end());
				int ct=0;
				double tot=0.0,last;
				for (j=0;j<e.size();j++)
				{
					if (ct==p.size())tot+=e[j].first-last;
					ct+=e[j].second;
					last=e[j].first;
				}
				ans+=s.det(t)*tot;
			}
		}
		return fabs(ans)*0.5;
	}
};
