const int maxn=500;
struct circles 
{
	circle c[maxn];
	double ans[maxn];//ans[i]表示被覆盖了i次的面积 
	double pre[maxn];
	int n;
	circles(){}
	void add(circle cc)
	{
		c[n++]=cc;
	}
	bool inner(circle x,circle y)
	{
		if (x.relationcircle(y)!=1)return 0;
		return dblcmp(x.r-y.r)<=0?1:0;
	}
	void init_or()//圆的面积并去掉内含的圆 
	{
		int i,j,k=0;
		bool mark[maxn]={0};
		for (i=0;i<n;i++)
		{
			for (j=0;j<n;j++)if (i!=j&&!mark[j])
			{
				if ((c[i]==c[j])||inner(c[i],c[j]))break;
			}
			if (j<n)mark[i]=1;
		}
		for (i=0;i<n;i++)if (!mark[i])c[k++]=c[i];
		n=k;
	}
	void init_and()//圆的面积交去掉内含的圆 
	{
		int i,j,k=0;
		bool mark[maxn]={0};
		for (i=0;i<n;i++)
		{
			for (j=0;j<n;j++)if (i!=j&&!mark[j])
			{
				if ((c[i]==c[j])||inner(c[j],c[i]))break;
			}
			if (j<n)mark[i]=1;
		}
		for (i=0;i<n;i++)if (!mark[i])c[k++]=c[i];
		n=k;
	}
	double areaarc(double th,double r)
    {
    	return 0.5*sqr(r)*(th-sin(th));
    }
	void getarea()
	{
		int i,j,k;
		memset(ans,0,sizeof(ans));
		vector<pair<double,int> >v;
		for (i=0;i<n;i++)
		{
			v.clear();
			v.push_back(make_pair(-pi,1));
			v.push_back(make_pair(pi,-1));
			for (j=0;j<n;j++)if (i!=j)
			{
				point q=c[j].p.sub(c[i].p);
				double ab=q.len(),ac=c[i].r,bc=c[j].r;
				if (dblcmp(ab+ac-bc)<=0)
    			{
       				v.push_back(make_pair(-pi,1));
					v.push_back(make_pair(pi,-1));
           			continue;
       			}
    			if (dblcmp(ab+bc-ac)<=0)continue;
    			if (dblcmp(ab-ac-bc)>0) continue;
				double th=atan2(q.y,q.x),fai=acos((ac*ac+ab*ab-bc*bc)/(2.0*ac*ab));
				double a0=th-fai;
				if (dblcmp(a0+pi)<0)a0+=2*pi;
				double a1=th+fai;
				if (dblcmp(a1-pi)>0)a1-=2*pi;
				if (dblcmp(a0-a1)>0)
				{
					v.push_back(make_pair(a0,1));
					v.push_back(make_pair(pi,-1));
					v.push_back(make_pair(-pi,1));
					v.push_back(make_pair(a1,-1));
				}
				else 
				{
					v.push_back(make_pair(a0,1));
					v.push_back(make_pair(a1,-1));
				}
			}
			sort(v.begin(),v.end());
			int cur=0;
			for (j=0;j<v.size();j++)
			{
				if (cur&&dblcmp(v[j].first-pre[cur]))
				{
					ans[cur]+=areaarc(v[j].first-pre[cur],c[i].r);
					ans[cur]+=0.5*point(c[i].p.x+c[i].r*cos(pre[cur]),c[i].p.y+c[i].r*sin(pre[cur])).det(point(c[i].p.x+c[i].r*cos(v[j].first),c[i].p.y+c[i].r*sin(v[j].first)));	
				}
				cur+=v[j].second;
				pre[cur]=v[j].first;
			}
		}
		for (i=1;i<=n;i++)
		{
			ans[i]-=ans[i+1];
		}
	}
};
