#include<cstdio>  
#include<algorithm>  
#include<map>  

#define MAXX 5555  
#define MAX MAXX<<3  
#define inf 10011  

int n,i;  
int mid[MAX],cnt[MAX],len[MAX],seg[MAX];  
bool rt[MAX],lf[MAX];  

std::map<int,int>map;  
std::map<int,int>::iterator it;  
int rmap[inf];  
long long sum;  
int x1,x2,y1,y2,last;  

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
    if(l==ll && rr==r)  
    {  
        cnt[id]+=val;  
        if(cnt[id])  
        {  
            rt[id]=lf[id]=true;  
            len[id]=rmap[r]-rmap[l-1];  
            seg[id]=1;  
        }  
        else  
            if(l!=r)  
            {  
                len[id]=len[id<<1]+len[id<<1|1];  
                seg[id]=seg[id<<1]+seg[id<<1|1];  
                if(rt[id<<1] && lf[id<<1|1])  
                    --seg[id];  
                rt[id]=rt[id<<1|1];  
                lf[id]=lf[id<<1];  
            }  
            else  
            {  
                len[id]=0;  
                rt[id]=lf[id]=false;  
                seg[id]=0;  
            }  
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
    {  
        len[id]=len[id<<1]+len[id<<1|1];  
        seg[id]=seg[id<<1]+seg[id<<1|1];  
        if(rt[id<<1] && lf[id<<1|1])  
            --seg[id];  
        rt[id]=rt[id<<1|1];  
        lf[id]=lf[id<<1];  
    }  
}  

struct node  
{  
    int l,r,h;  
    char val;  
    inline bool operator<(const node &a)const  
    {  
        return h==a.h?val<a.val:h<a.h;   // trick watch out. val<a.val? val>a.val?
    }  
    inline void print()  
    {  
        printf("%d %d %d %d\n",l,r,h,val);  
    }  
}ln[inf];  

int main()  
{  
    make(1,1,inf);  
    scanf("%d",&n);  
    n<<=1;  
    map.clear();  
    for(i=0;i<n;++i)  
    {  
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);  
        ln[i].l=x1;  
        ln[i].r=x2;  
        ln[i].h=y1;  
        ln[i].val=1;  
        ln[++i].l=x1;  
        ln[i].r=x2;  
        ln[i].h=y2;  
        ln[i].val=-1;  
        map[x1]=1;  
        map[x2]=1;  
    }  
    i=1;  
    for(it=map.begin();it!=map.end();++it,++i)  
    {  
        it->second=i;  
        rmap[i]=it->first;  
    }  
    i=0;  
    std::sort(ln,ln+n);  
    update(1,1,inf,map[ln[0].l]+1,map[ln[0].r],ln[0].val);  
    sum+=len[1];  
    last=len[1];  
    for(i=1;i<n;++i)  
    {  
        sum+=2*seg[1]*(ln[i].h-ln[i-1].h);  
        update(1,1,inf,map[ln[i].l]+1,map[ln[i].r],ln[i].val);  
        sum+=abs(len[1]-last);  
        last=len[1];  
    }  
    printf("%lld\n",sum);  
    return 0;  
} 
