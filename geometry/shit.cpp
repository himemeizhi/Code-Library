struct pv
{
    double x,y;
    pv(double a=0,double b=0):x(a),y(b){}
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
    inline double dot(const pv &i)const
    {
        return x*i.x+y*i.y;
    }
    inline double len()
    {
        return hypot(x,y);
    }
};

struct line
{
    pv pnt[2];
    line(double a,double b,double c) // a*x + b*y + c = 0
    {
#define maxl 1e2 //preciseness should not be too high ( compare with eps )
        if(fabs(b)>eps)
        {
            pnt[0]=pv(maxl,(c+a*maxl)/(-b));
            pnt[1]=pv(-maxl,(c-a*maxl)/(-b));
        }
        else
        {
            pnt[0]=pv(-c/a,maxl);
            pnt[1]=pv(-c/a,-maxl);
        }
#undef maxl
    }
    pv cross(const line &v)const
    {
        double a=(v.pnt[1]-v.pnt[0]).cross(pnt[0]-v.pnt[0]);
        double b=(v.pnt[1]-v.pnt[0]).cross(pnt[1]-v.pnt[0]);
        return pv((pnt[0].x*b-pnt[1].x*a)/(b-a),(pnt[0].y*b-pnt[1].y*a)/(b-a));
    }
};

inline std::pair<pv,double> getcircle(const pv &a,const pv &b,const pv &c)
{
    static pv ct;
    ct=line(2*(b.x-a.x),2*(b.y-a.y),a.len()-b.len()).cross(line(2*(c.x-b.x),2*(c.y-b.y),b.len()-c.len()));
    return std::make_pair(ct,sqrt((ct-a).len()));
}

//sort with polar angle
inline bool cmp(const Point& a,const Point& b)
{
    if (a.y*b.y <= 0)
    {
        if (a.y > 0 || b.y > 0) 
            return a.y < b.y;
        if (a.y == 0 && b.y == 0)   
            return a.x < b.x;
    }
    return a.cross(b) > 0;
}

//graham
inline bool com(const pv &a,const pv &b)
{
    static double t;
    if(fabs(t=(a-pnt[0]).cross(b-pnt[0]))>eps)
        return t>0;
    return (a-pnt[0]).len()<(b-pnt[0]).len();
}

inline void graham(std::vector<pv> &ch,const int n)
{
    std::nth_element(pnt,pnt,pnt+n);
    std::sort(pnt+1,pnt+n,com);
    ch.resize(0);
    ch.push_back(pnt[0]);
    ch.push_back(pnt[1]);
    static int i;
    for(i=2;i<n;++i)
        if(fabs((pnt[i]-ch[0]).cross(ch[1]-ch[0]))>eps)
        {
            ch.push_back(pnt[i++]);
            break;
        }
        else
            ch.back()=pnt[i];
    for(;i<n;++i)
    {
        while((ch.back()-ch[ch.size()-2]).cross(pnt[i]-ch[ch.size()-2])<eps)
            ch.pop_back();
        ch.push_back(pnt[i]);
    }
}
