//abc解析几何方式
inline pv ins(const pv &p1,const pv &p2)
{
    u=fabs(a*p1.x+b*p1.y+c);  
    v=fabs(a*p2.x+b*p2.y+c); 
    return pv((p1.x*v+p2.x*u)/(u+v),(p1.y*v+p2.y*u)/(u+v));
}

inline void get(const pv& p1,const pv& p2,double & a,double & b,double & c)  
{  
    a=p2.y-p1.y;  
    b=p1.x-p2.x;  
    c=p2.x*p1.y-p2.y*p1.x;  
}  

inline pv ins(const pv &x,const pv &y)
{
    get(x,y,d,e,f);
    return pv((b*f-c*e)/(a*e-b*d),(a*f-c*d)/(b*d-a*e));
}

std::vector<pv>p[2];
inline bool go()
{
    k=0;
    p[k].resize(0);
    p[k].push_back(pv(-inf,inf));
    p[k].push_back(pv(-inf,-inf));
    p[k].push_back(pv(inf,-inf));
    p[k].push_back(pv(inf,inf));
    for(i=0;i<n;++i)
    {
        get(pnt[i],pnt[(i+1)%n],a,b,c);
        c+=the*sqrt(a*a+b*b);
        p[!k].resize(0);
        for(l=0;l<p[k].size();++l)
            if(a*p[k][l].x+b*p[k][l].y+c<eps)
                p[!k].push_back(p[k][l]);
            else
            {
                m=(l+p[k].size()-1)%p[k].size();
                if(a*p[k][m].x+b*p[k][m].y+c<-eps)
                    p[!k].push_back(ins(p[k][m],p[k][l]));
                m=(l+1)%p[k].size();
                if(a*p[k][m].x+b*p[k][m].y+c<-eps)
                    p[!k].push_back(ins(p[k][m],p[k][l]));
            }
        k=!k;
        if(p[k].empty())
            break;
    }
    //`结果在p[k]中`
    return p[k].empty();
}

//计算几何方式
//本例求多边形核

inline pv ins(const pv &a,const pv &b)
{
    u=fabs(ln.cross(a-pnt[i]));
    v=fabs(ln.cross(b-pnt[i]))+u;
    tl=b-a;
    return pv(u*tl.x/v+a.x,u*tl.y/v+a.y);
}

int main()
{
    j=0;
    for(i=0;i<n;++i)
    {
        ln=pnt[(i+1)%n]-pnt[i];
        p[!j].resize(0);
        for(k=0;k<p[j].size();++k)
            if(ln.cross(p[j][k]-pnt[i])<=0)
                p[!j].push_back(p[j][k]);
            else
            {
                l=(k-1+p[j].size())%p[j].size();
                if(ln.cross(p[j][l]-pnt[i])<0)
                    p[!j].push_back(ins(p[j][k],p[j][l]));
                l=(k+1)%p[j].size();
                if(ln.cross(p[j][l]-pnt[i])<0)
                    p[!j].push_back(ins(p[j][k],p[j][l]));
            }
        j=!j;
    }
    //结果在p[j]中
}

struct hp
{
    pv p,v; // from point p with vector v, left of it
    double k;
    hp(){}
    hp(const pv &i,const pv &j):p(i),v(j),k(atan2(j.y,j.x)){}
    bool operator<(const hp &i)const { return k<i.k; }
    bool onleft(const pv &pnt)const { return v.cross(pnt-p)>=0;}//>eps; }
    pv ins(const hp &b)const { return p+v*(b.v.cross(p-b.p)/v.cross(b.v)); } //line-line intersection
};
std::vector<hp>ln(MAXX);

inline void hpi(std::vector<hp>&l,std::vector<pv>&ot)
{
    static hp q[MAXX];
    static pv p[MAXX];
    static int i,qh,qt;
    ot.resize(0);
    std::sort(l.begin(),l.end());
    q[qh=qt=0]=l[0];
    for(i=0;i<l.size();++i)
    {
        while(qh<qt && !l[i].onleft(p[qt-1]))
            --qt;
        while(qh<qt && !l[i].onleft(p[qh]))
            ++qh;
        q[++qt]=l[i];
        if(fabs(q[qt].v.cross(q[qt-1].v))<eps)
        {
            --qt;
            if(q[qt].onleft(l[i].p))
                q[qt]=l[i];
        }
        if(qh<qt)
            p[qt-1]=q[qt].ins(q[qt-1]);
    }
    while(qh<qt && !q[qh].onleft(p[qt-1]))
        --qt;
    if(qh>=qt)
        return;
    if(qh<qt)
        p[qt]=q[qh].ins(q[qt]);
    for(i=qh;i<=qt;++i)
        ot.push_back(p[i]);
}
