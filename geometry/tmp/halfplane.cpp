struct halfplane:public line
{
	double angle;
	halfplane(){}
	//表示向量 a->b逆时针(左侧)的半平面
	halfplane(point _a,point _b)
	{
		a=_a;
		b=_b;
	}
	halfplane(line v)
	{
		a=v.a;
		b=v.b;
	}
	void calcangle()
	{
		angle=atan2(b.y-a.y,b.x-a.x);
	}
	bool operator<(const halfplane &b)const 
	{
		return angle<b.angle;
	}
};
struct halfplanes 
{
	int n;
	halfplane hp[maxp];
	point p[maxp];
	int que[maxp];
	int st,ed;
	void push(halfplane tmp)
	{
		hp[n++]=tmp;
	}
	void unique()
	{
		int m=1,i;
		for (i=1;i<n;i++)
		{
			if (dblcmp(hp[i].angle-hp[i-1].angle))hp[m++]=hp[i];
			else if (dblcmp(hp[m-1].b.sub(hp[m-1].a).det(hp[i].a.sub(hp[m-1].a))>0))hp[m-1]=hp[i];
		}
		n=m;
	}
	bool halfplaneinsert()
	{
		int i;
		for (i=0;i<n;i++)hp[i].calcangle();
		sort(hp,hp+n);
		unique();
		que[st=0]=0;
		que[ed=1]=1;
		p[1]=hp[0].crosspoint(hp[1]);
		for (i=2;i<n;i++)
		{
			while (st<ed&&dblcmp((hp[i].b.sub(hp[i].a).det(p[ed].sub(hp[i].a))))<0)ed--;
			while (st<ed&&dblcmp((hp[i].b.sub(hp[i].a).det(p[st+1].sub(hp[i].a))))<0)st++;
			que[++ed]=i;
			if (hp[i].parallel(hp[que[ed-1]]))return false;
			p[ed]=hp[i].crosspoint(hp[que[ed-1]]);
		}
		while (st<ed&&dblcmp(hp[que[st]].b.sub(hp[que[st]].a).det(p[ed].sub(hp[que[st]].a)))<0)ed--;
		while (st<ed&&dblcmp(hp[que[ed]].b.sub(hp[que[ed]].a).det(p[st+1].sub(hp[que[ed]].a)))<0)st++;
		if (st+1>=ed)return false;
		return true;
	}
	void getconvex(polygon &con)
	{
		p[st]=hp[que[st]].crosspoint(hp[que[ed]]);
		con.n=ed-st+1;
		int j=st,i=0;
		for (;j<=ed;i++,j++)
		{
			con.p[i]=p[j];
		}
	}
};
