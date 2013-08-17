/*
`有个很关键的剪枝，在计算完与mid点的距离后，我们应该先进入左右哪个子树？我们应该先进入对于当前维度，查询点位于的那一边。显然，在查询点所在的子树，更容易查找出正确解。`

`那么当进入完左或右子树后，以查询点为圆心做圆，如果当前维度，查询点距离mid的距离（另一个子树中的点距离查询点的距离肯定大于这个距离）比堆里的最大值还大，那么就不再递归另一个子树。注意一下：如果堆里的元素个数不足M，仍然还要进入另一棵子树。`

`说白了就是随便乱搞啦………………`
*/
// hysbz 2626
#include<cstdio>
#include<algorithm>
#include<queue>

inline long long sqr(long long a){ return a*a;}
typedef std::pair<long long,int> pli;

#define MAXX 100111
#define MAX (MAXX<<2)
#define inf 0x3f3f3f3fll
int idx;

struct PNT
{
    long long x[2];
    int lb;
    bool operator<(const PNT &i)const
    {
        return x[idx]<i.x[idx];
    }
    pli dist(const PNT &i)const
    {
        return pli(-(sqr(x[0]-i.x[0])+sqr(x[1]-i.x[1])),lb);
    }
}a[MAXX],the[MAX],p;

#define mid (l+r>>1)
#define lson (id<<1)
#define rson (id<<1|1)
#define lc lson,l,mid-1
#define rc rson,mid+1,r
int n,m;

long long rg[MAX][2][2];

void make(int id=1,int l=1,int r=n,int d=0)
{
    the[id].lb=-1;
    rg[id][0][0]=rg[id][1][0]=inf;
    rg[id][0][1]=rg[id][1][1]=-inf;
    if(l>r)
        return;
    idx=d;
    std::nth_element(a+l,a+mid,a+r+1);
    the[id]=a[mid];
    rg[id][0][0]=rg[id][0][1]=the[id].x[0];
    rg[id][1][0]=rg[id][1][1]=the[id].x[1];
    make(lc,d^1);
    make(rc,d^1);

    rg[id][0][0]=std::min(rg[id][0][0],std::min(rg[lson][0][0],rg[rson][0][0]));
    rg[id][1][0]=std::min(rg[id][1][0],std::min(rg[lson][1][0],rg[rson][1][0]));

    rg[id][0][1]=std::max(rg[id][0][1],std::max(rg[lson][0][1],rg[rson][0][1]));
    rg[id][1][1]=std::max(rg[id][1][1],std::max(rg[lson][1][1],rg[rson][1][1]));
}

inline long long cal(int id)
{
    static long long a[2];
    static int i;
    for(i=0;i<2;++i)
        a[i]=std::max(abs(p.x[i]-rg[id][i][0]),abs(p.x[i]-rg[id][i][1]));
    return sqr(a[0])+sqr(a[1]);
}

std::priority_queue<pli>ans;

void query(const int id=1,const int d=0)
{
    if(the[id].lb<0)
        return;
    pli tmp(the[id].dist(p));
    int a(lson),b(rson);
    if(p.x[d]<=the[id].x[d])
        std::swap(a,b);
    if(ans.size()<m)
        ans.push(tmp);
    else
        if(tmp<ans.top())
        {
            ans.push(tmp);
            ans.pop();
        }
    if(ans.size()<m || cal(a)>=-ans.top().first)
        query(a,d^1);
    if(ans.size()<m || cal(b)>=-ans.top().first)
        query(b,d^1);
}

int q,i,j,k;

int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {
        scanf("%lld %lld",&a[i].x[0],&a[i].x[1]);
        a[i].lb=i;
    }
    make();
    scanf("%d",&q);
    while(q--)
    {
        scanf("%lld %lld",&p.x[0],&p.x[1]);
        scanf("%d",&m);
        while(!ans.empty())
            ans.pop();
        query();
        printf("%d\n",ans.top().second);
    }
    return 0;
}
