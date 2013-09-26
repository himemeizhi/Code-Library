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
    pv(double a=0,double b=0,double c=0):x(a),y(b),z(c){}
    pv operator-(const pv &i)const { return pv(x-i.x,y-i.y,z-i.z); }
    pv operator+(const pv &i)const { return pv(x+i.x,y+i.y,z+i.z); }
    pv operator*(double a)const{return pv(x*a,y*a,z*a);}
    pv cross(const pv &i)const{return pv(y*i.z-z*i.y,z*i.x-x*i.z,x*i.y-y*i.x);}
    double dot(const pv &i)const{return x*i.x+y*i.y+z*i.z;}
    pv operator*(const pv &i)const{return cross(i);}
    double operator^(const pv &i)const{return dot(i);}
    double len()const{return sqrt(x*x+y*y+z*z);}
};

struct pla
{
    int a,b,c;
    bool ok;
    pla(int aa=0,int bb=0,int cc=0):a(aa),b(bb),c(cc),ok(true){}
    void set();
};

std::vector<pla>fac(MAXX*MAXX);
int to[MAXX][MAXX];

inline void pla::set(){to[a][b]=to[b][c]=to[c][a]=fac.size();}

inline double vol(const pv &a,const pv &b,const pv &c,const pv &d)
{
    return (b-a)*(c-a)^(d-a);
}
inline double ptof(const pv &p,const pla &f)
{
    return vol(pnt[f.a],pnt[f.b],pnt[f.c],p);
}
inline double ptof(const pv &p,int f)
{
    return fabs(ptof(p,fac[f])/((pnt[fac[f].b]-pnt[fac[f].a])*(pnt[fac[f].c]-pnt[fac[f].a])).len());
}

void dfs(int,int);
void deal(int p,int a,int b)
{
    if(!fac[to[a][b]].ok)
        return;
    if(ptof(pnt[p],fac[to[a][b]])>eps)
        dfs(p,to[a][b]);
    else
    {
        pla add(p,b,a);
        add.set();
        fac.push_back(add);
    }
}
void dfs(int p,int now)
{
    fac[now].ok=false;
    deal(p,fac[now].b,fac[now].a);
    deal(p,fac[now].c,fac[now].b);
    deal(p,fac[now].a,fac[now].c);
}

inline void make(const int n)
{
    static int i,j,m;
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
    m=fac.size();
    fac.resize(0);
    for(i=0;i<m;++i)
        if(fac[i].ok)
            fac.push_back(fac[i]);
}

inline pv gc() //重心
{
    pv re(0,0,0),o(0,0,0);
    double all(0),v;
    for(int i=0;i<fac.size();++i)
    {
        v=vol(o,pnt[fac[i].a],pnt[fac[i].b],pnt[fac[i].c]);
        re+=(pnt[fac[i].a]+pnt[fac[i].b]+pnt[fac[i].c])*0.25f*v;
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
inline int facetcnt()
{
    int ans=0;
    static int i,j;
    for(i=0;i<fac.size();++i)
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
        return ((b-a)*(c-a)).len();
}

//表面积
inline double area()
{
    double ret(0);
    static int i;
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
