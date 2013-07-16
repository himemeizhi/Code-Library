#include<cstdio>
#include<algorithm>
#include<map>

#define MAXX 111
#define inf 333
#define MAX inf*5

int mid[MAX],cnt[MAX];
double len[MAX];

int n,i,cas;
double x1,x2,y1,y2;
double ans;
std::map<double,int>map;
std::map<double,int>::iterator it;
double rmap[inf];

void make(int id,int l,int r)
{
    mid[id]=(l+r)>>1;
    if(l!=r)
    {
        make(id<<1,l,mid[id]);
        make(id<<1|1,mid[id]+1,r);
    }
}

void update(int id,int ll,int rr,int l,int r,int val)
{
    if(ll==l && rr==r)
    {
        cnt[id]+=val;
        if(cnt[id])
            len[id]=rmap[r]-rmap[l-1];
        else
            if(l!=r)
                len[id]=len[id<<1]+len[id<<1|1];
            else
                len[id]=0;
        return;
    }
    if(mid[id]>=r)
        update(id<<1,ll,mid[id],l,r,val);
    else
        if(mid[id]<l)
            update(id<<1|1,mid[id]+1,rr,l,r,val);
        else
        {
            update(id<<1,ll,mid[id],l,mid[id],val);
            update(id<<1|1,mid[id]+1,rr,mid[id]+1,r,val);
        }
    if(!cnt[id])
        len[id]=len[id<<1]+len[id<<1|1];
}

struct node
{
    double l,r,h;
    char f;
    inline bool operator<(const node &a)const
    {
        return h<a.h;
    }
    inline void print()
    {
        printf("%lf %lf %lf %d\n",l,r,h,f);
    }
}ln[inf];

int main()
{
    make(1,1,inf);
    while(scanf("%d",&n),n)
    {
        n<<=1;
        map.clear();
        for(i=0;i<n;++i)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            if(x1>x2)
                std::swap(x1,x2);
            if(y1>y2)
                std::swap(y1,y2);
            ln[i].l=x1;
            ln[i].r=x2;
            ln[i].h=y1;
            ln[i].f=1;
            ln[++i].l=x1;
            ln[i].r=x2;
            ln[i].h=y2;
            ln[i].f=-1;
            map[x1]=1;
            map[x2]=1;
        }
        i=1;
        for(it=map.begin();it!=map.end();++it,++i)
        {
            it->second=i;
            rmap[i]=it->first;
        }
        std::sort(ln,ln+n);
        ans=0;
        update(1,1,inf,map[ln[0].l]+1,map[ln[0].r],ln[0].f);
        for(i=1;i<n;++i)
        {
            ans+=len[1]*(ln[i].h-ln[i-1].h);
            update(1,1,inf,map[ln[i].l]+1,map[ln[i].r],ln[i].f);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",++cas,ans);
    }
    return 0;
}
