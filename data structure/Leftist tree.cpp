#include<cstdio>
#include<algorithm>

#define MAXX 100111

int val[MAXX],l[MAXX],r[MAXX],d[MAXX];

int set[MAXX];

int merge(int a,int b)
{
    if(!a)
        return b;
    if(!b)
        return a;
    if(val[a]<val[b]) // max-heap
        std::swap(a,b);
    r[a]=merge(r[a],b);
    if(d[l[a]]<d[r[a]])
        std::swap(l[a],r[a]);
    d[a]=d[r[a]]+1;
    set[l[a]]=set[r[a]]=a; // set a as father of its sons
    return a;
}

inline int find(int &a)
{
    while(set[a]) //brute-force to get the index of root
        a=set[a];
    return a;
}

inline void reset(int i)
{
    l[i]=r[i]=d[i]=set[i]=0;
}

int n,i,j,k;

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(i=1;i<=n;++i)
        {
            scanf("%d",val+i);
            reset(i);
        }
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            if(find(i)==find(j))
                puts("-1");
            else
            {
                k=merge(l[i],r[i]);
                val[i]>>=1;
                reset(i);
                set[i=merge(i,k)]=0;

                k=merge(l[j],r[j]);
                val[j]>>=1;
                reset(j);
                set[j=merge(j,k)]=0;

                set[k=merge(i,j)]=0;
                printf("%d\n",val[k]);
            }
        }
    }
    return 0;
}
