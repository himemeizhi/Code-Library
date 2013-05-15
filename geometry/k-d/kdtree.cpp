#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <algorithm>
using namespace std;
#define MAXN 100010
typedef long long ll;
struct Point{
    ll x,y;
    void operator =(const Point &p){
        x=p.x; y=p.y;
    }
    ll dis(const Point &a){
        return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
    }
}point[MAXN],pp[MAXN];

struct Node{
    int split;//{0,1}  0表示垂直于x轴的超平面，1表示垂直于y轴的超平面
    Point p;//点
}tree[MAXN*4];

bool cmpx(const Point &a,const Point &b)
{
    return a.x<b.x;
}

bool cmpy(const Point &a,const Point &b)
{
    return a.y<b.y; 
}

void initTree(int x,int y,int split,int pos)
{
    if(y<x) return ;
    int mid=(x+y)>>1;
    random_shuffle(point+x,point+y);    
    if(split==0) nth_element(point+x,point+mid,point+y+1,cmpx);
    else nth_element(point+x,point+mid,point+y+1,cmpy);
    tree[pos].split=split;
    tree[pos].p=point[mid];
    initTree(x,mid-1,(split^1),2*pos); 
    initTree(mid+1,y,(split^1),2*pos+1);
}

ll ans;
void insert(int x,int y,Point &p,int pos)
{
    if(y<x) return ;
    int mid=(x+y)>>1;
    ll temp=p.dis(tree[pos].p);
    if(temp!=0) ans=min(ans,temp);
    if(tree[pos].split==0){
        if(p.x<=tree[pos].p.x){
            insert(x,mid-1,p,2*pos);
            if(ans>=(p.x-tree[pos].p.x)*(p.x-tree[pos].p.x))
                insert(mid+1,y,p,2*pos+1);
        }
        else{
            insert(mid+1,y,p,2*pos+1); 
            if(ans>=(p.x-tree[pos].p.x)*(p.x-tree[pos].p.x))
                insert(x,mid-1,p,2*pos);       
        }                  
    }
    else
    {
        if(p.y<=tree[pos].p.y){
            insert(x,mid-1,p,2*pos);
            if(ans>=(p.y-tree[pos].p.y)*(p.y-tree[pos].p.y))
                insert(mid+1,y,p,2*pos+1);
        }
        else{
            insert(mid+1,y,p,2*pos+1); 
            if(ans>=(p.y-tree[pos].p.y)*(p.y-tree[pos].p.y))
                insert(x,mid-1,p,2*pos);       
        }
    }
}

int main()
{
    int cases,n;
    scanf("%d",&cases);
    while(cases--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%I64d%I64d",&pp[i].x,&pp[i].y);
            point[i]=pp[i];    
        }
        initTree(1,n,0,1);
        for(int i=1;i<=n;i++){
            ans=1LL<<62;
            insert(1,n,pp[i],1);
            printf("%I64d\n",ans);    
        }               
    }
    return 0;
}

