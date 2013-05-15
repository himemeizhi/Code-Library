#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

#define MAXX 71

struct mono
{
    long long weig,cost;
}goods[MAXX];

short n,T,t,i;
long long carry,sumw,sumc;
long long ans,las[MAXX];

int com(const void *n,const void *m)
{
    struct mono *a=(struct mono *)n,*b=(struct mono *)m;
    if(a->weig!=b->weig)
        return a->weig-b->weig;
    else
        return b->cost-a->cost;
}

bool comp(const struct mono a,const struct mono b)
{
    if(a.weig!=b.weig)
        return a.weig<b.weig;
    else
        return b.cost<a.cost;
}

void dfs(short i,long long cost_n,long long carry_n,short last)
{
    if(ans<cost_n)
        ans=cost_n;
    if(i==n || goods[i].weig>carry_n || cost_n+las[i]<=ans)
        return;
    if(last || (goods[i].weig!=goods[i-1].weig && goods[i].cost>goods[i-1].cost))
        dfs(i+1,cost_n+goods[i].cost,carry_n-goods[i].weig,1);
    dfs(i+1,cost_n,carry_n,0);
}

int main()
{
    //    freopen("asdf","r",stdin);
    scanf("%hd",&T);
    for(t=1;t<=T;++t)
    {
        scanf("%hd%lld",&n,&carry);
        sumw=0;
        sumc=0;
        ans=0;
        for(i=0;i<n;++i)
        {
            scanf("%lld%lld",&goods[i].weig,&goods[i].cost);
            sumw+=goods[i].weig;
            sumc+=goods[i].cost;
        }
        if(sumw<=carry)
        {
            printf("Case %hd: %lld\n",t,sumc);
            continue;
        }
//        qsort(goods,n,sizeof(struct mono),com);
        std::sort(goods,goods+n,comp);
        for(i=0;i<n;++i)
        {
//            printf("%lld %lld\n",goods[i].weig,goods[i].cost);
            las[i]=sumc;
            sumc-=goods[i].cost;
        }
        dfs(0,0,carry,1);
        printf("Case %hd: %lld\n",t,ans);
    }
    return 0;
}
