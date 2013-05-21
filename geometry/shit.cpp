struct pv
{
    double x,y;
    pv():x(0),y(0){}
    pv(double xx,double yy):x(xx),y(yy){}
    inline pv operator+(const pv &i)const
    {
        return pv(x+i.x,y+i.y);
    }
    inline pv operator-(const pv &i)const
    {
        return pv(x-i.x,y-i.y);
    }
    inline bool operator ==(const pv &i)const
    {
        return fabs(x-i.x)<eps && fabs(y-i.y)<eps;
    }
    inline bool operator<(const pv &i)const
    {
        return y==i.y?x<i.x:y<i.y;
    }
    inline double cross(const pv &i)const
    {
        return x*i.y-y*i.x;
    }
    inline int dot(const pv &i)const
    {
        return x*i.x+y*i.y;
    }
    inline double len()
    {
        return sqrt(x*x+y*y);
    }
    inline pv rotate(pv p,double theta)
    {
        static pv v;
        v=*this-p;
        static double c,s;
        c=cos(theta);
        s=sin(theta);
        return pv(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
    }
};

inline int cross(pv *a,pv *b)
{
    static pv vecta,vectb;
    vecta=a[1]-a[0];
    vectb=b[1]-b[0];
    static double c,d;
    c=vecta.cross(b[1]-a[0])*vecta.cross(b[0]-a[0]);
    d=vectb.cross(a[1]-b[0])*vectb.cross(a[0]-b[0]);
    if(c>eps || d>eps)
        return -1;
    if(c<-eps && b<-eps)
        return 1;
    return 0;
}

pv rotate(pv v,pv p,double theta,double sc=1) // rotate vector v, theta∈[0,2π]
{
    static pv re;
    re=p;
    v=v-p;
    p.x=sc*cos(theta);
    p.y=sc*sin(theta);
    re.x+=v.x*p.x-v.y*p.y;
    re.y+=v.x*p.y+v.y*p.x;
    return re;
}
