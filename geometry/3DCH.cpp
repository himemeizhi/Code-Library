#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>

#define MAXX 1111
#define eps 1e-8
#define inf 1e20

struct pv
{
    double x,y,z;
    pv(){}
    pv(const double &xx,const double &yy,const double &zz):x(xx),y(yy),z(zz){}
    inline pv operator-(const pv &i)const
    {
        return pv(x-i.x,y-i.y,z-i.z);
    }
    inline pv operator*(const pv &i)const //叉积
    {
        return pv(y*i.z-z*i.y,z*i.x-x*i.z,x*i.y-y*i.x);
    }
    inline double operator^(const pv &i)const //点积
    {
        return x*i.x+y*i.y+z*i.z;
    }
    inline double len()
    {
        return sqrt(x*x+y*y+z*z);
    }
};

struct pla
{
    short a,b,c;
    bool ok;
    pla(){}
    pla(const short &aa,const short &bb,const short &cc):a(aa),b(bb),c(cc),ok(true){}
    inline void set();
    inline void print()
    {
        printf("%hd %hd %hd\n",a,b,c);
    }
};

pv pnt[MAXX];
std::vector<pla>fac;
short to[MAXX][MAXX];

inline void pla::set()
{
    to[a][b]=to[b][c]=to[c][a]=fac.size();
}

inline double ptof(const pv &p,const pla &f) //点面距离?
{
    return (pnt[f.b]-pnt[f.a])*(pnt[f.c]-pnt[f.a])^(p-pnt[f.a]);
}

inline double vol(const pv &a,const pv &b,const pv &c,const pv &d)//有向体积*6，即六面体体积
{
    return (b-a)*(c-a)^(d-a);
}

inline double ptof(const pv &p,const short &f) //p点到f号面的距离
{
    return fabs(vol(pnt[fac[f].a],pnt[fac[f].b],pnt[fac[f].c],p)/((pnt[fac[f].b]-pnt[fac[f].a])*(pnt[fac[f].c]-pnt[fac[f].a])).len());
}

void dfs(const short&,const short&);

void deal(const short &p,const short &a,const short &b)
{
    if(fac[to[a][b]].ok)
        if(ptof(pnt[p],fac[to[a][b]])>eps)
            dfs(p,to[a][b]);
        else
        {
            pla add(b,a,p);
            add.set();
            fac.push_back(add);
        }
}

void dfs(const short &p,const short &now)
{
    fac[now].ok=false;
    deal(p,fac[now].b,fac[now].a);
    deal(p,fac[now].c,fac[now].b);
    deal(p,fac[now].a,fac[now].c);
}

inline void make()
{
    fac.resize(0);
    if(n<4)
        return;

    for(i=1;i<n;++i)
        if((pnt[0]-pnt[i]).len()>eps)
        {
            std::swap(pnt[i],pnt[1]);
            break;
        }
    if(i==n)
        return;

    for(i=2;i<n;++i)
        if(((pnt[0]-pnt[1])*(pnt[1]-pnt[i])).len()>eps)
        {
            std::swap(pnt[i],pnt[2]);
            break;
        }
    if(i==n)
        return;

    for(i=3;i<n;++i)
        if(fabs((pnt[0]-pnt[1])*(pnt[1]-pnt[2])^(pnt[2]-pnt[i]))>eps)
        {
            std::swap(pnt[3],pnt[i]);
            break;
        }
    if(i==n)
        return;

    for(i=0;i<4;++i)
    {
        pla add((i+1)%4,(i+2)%4,(i+3)%4);
        if(ptof(pnt[i],add)>0)
            std::swap(add.c,add.b);
        add.set();
        fac.push_back(add);
    }
    for(;i<n;++i)
        for(j=0;j<fac.size();++j)
            if(fac[j].ok && ptof(pnt[i],fac[j])>eps)
            {
                dfs(i,j);
                break;
            }

    short tmp(fac.size());
    fac.resize(0);
    for(i=0;i<tmp;++i)
        if(fac[i].ok)
            fac.push_back(fac[i]);
}

inline pv gc() //重心
{
    pv re(0,0,0),o(0,0,0);
    double all(0),v;
    for(i=0;i<fac.size();++i)
    {
        v=vol(o,pnt[fac[i].a],pnt[fac[i].b],pnt[fac[i].c]);
        re+=(pnt[fac[i].a]+pnt[fac[i].b]+pnt[fac[i].c])*0.25*v;
        all+=v;
    }
    return re*(1/all);
}

inline bool same(const short &s,const short &t) //两面是否相等
{
    pv &a=pnt[fac[s].a],&b=pnt[fac[s].b],&c=pnt[fac[s].c];
    return fabs(vol(a,b,c,pnt[fac[t].a]))<eps && fabs(vol(a,b,c,pnt[fac[t].b]))<eps && fabs(vol(a,b,c,pnt[fac[t].c]))<eps;
}

//表面多边形数目
inline short facetcnt()
{
    short ans=0;
    for(short i=0;i<fac.size();++i)
    {
        for(j=0;j<i;++j)
            if(same(i,j))
                break;
        if(j==i)
            ++ans;
    }
    return ans;
}

//表面三角形数目
inline short trianglecnt()
{
    return fac.size();
}

//三点构成的三角形面积*2
inline double area(const pv &a,const pv &b,const pv &c)
{
        return (b-a)*(c-a).len();
}

//表面积
inline double area()
{
    double ret(0);
    for(i=0;i<fac.size();++i)
        ret+=area(pnt[fac[i].a],pnt[fac[i].b],pnt[fac[i].c]);
    return ret/2;
}

//体积
inline double volume()
{
    pv o(0,0,0);
    double ret(0);
    for(short i(0);i<fac.size();++i)
        ret+=vol(o,pnt[fac[i].a],pnt[fac[i].b],pnt[fac[i].c]);
    return fabs(ret/6);
}
