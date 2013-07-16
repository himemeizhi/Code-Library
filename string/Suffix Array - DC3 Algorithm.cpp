#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXX 1111
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[MAXX],wb[MAXX],wv[MAXX],ws[MAXX];

inline bool c0(const int *str,const int &a,const int &b)
{
    return str[a]==str[b] && str[a+1]==str[b+1] && str[a+2]==str[b+2];
}

inline bool c12(const int *str,const int &k,const int &a,const int &b)
{
    if(k==2)
        return str[a]<str[b] || str[a]==str[b] && c12(str,1,a+1,b+1);
    else
        return str[a]<str[b] || str[a]==str[b] && wv[a+1]<wv[b+1];
}

inline void sort(int *str,int *a,int *b,const int &n,const int &m)
{
    memset(ws,0,sizeof(ws));
    int i;
    for(i=0;i<n;++i)
        ++ws[wv[i]=str[a[i]]];
    for(i=1;i<m;++i)
        ws[i]+=ws[i-1];
    for(i=n-1;i>=0;--i)
        b[--ws[wv[i]]]=a[i];
}

inline void dc3(int *str,int *sa,const int &n,const int &m)
{
    int *strn(str+n);
    int *san(sa+n),tb((n+1)/3),ta(0),tbc(0),i,j,k;
    str[n]=str[n+1]=0;
    for(i=0;i<n;++i)
        if(i%3)
            wa[tbc++]=i;
    sort(str+2,wa,wb,tbc,m);
    sort(str+1,wb,wa,tbc,m);
    sort(str,wa,wb,tbc,m);
    for(i=j=1,strn[F(wb[0])]=0;i<tbc;++i)
        strn[F(wb[i])]=c0(str,wb[i-1],wb[i])?j-1:j++;
    if(j<tbc)
        dc3(strn,san,tbc,j);
    else
        for(i=0;i<tbc;++i)
            san[strn[i]]=i;
    for(i=0;i<tbc;++i)
        if(san[i]<tb)
            wb[ta++]=san[i]*3;
    if(n%3==1)
        wb[ta++]=n-1;
    sort(str,wb,wa,ta,m);
    for(i=0;i<tbc;++i)
        wv[wb[i]=G(san[i])]=i;
    for(i=j=k=0;i<ta && j<tbc;)
        sa[k++]=c12(str,wb[j]%3,wa[i],wb[j])?wa[i++]:wb[j++];
    while(i<ta)
        sa[k++]=wa[i++];
    while(j<tbc)
        sa[k++]=wb[j++];
}

int rk[MAXX],lcpa[MAXX],sa[MAXX*3];
int str[MAXX*3]; //必须int

int main()
{
    scanf("%d %d",&n,&j);
    for(i=0;i<n;++i)
    {
        scanf("%d",&k);
        num[i]=k-j+100;
        j=k;
    }
    num[n]=0;

    dc3(num,sa,n+1,191); //191: str中取值范围，桶排序

    for(i=1;i<=n;++i) // rank数组
        rk[sa[i]]=i;
    for(i=k=0;i<n;++i) // lcp数组
        if(!rk[i])
            lcpa[0]=0;
        else
        {
            j=sa[rk[i]-1];
            if(k>0)
                --k;
            while(num[i+k]==num[j+k])
                ++k;
            lcpa[rk[i]]=k;
        }


    for(i=1;i<=n;++i)
        sptb[0][i]=i;
    for(i=1;i<=lg[n];++i)  //sparse table RMQ
    {
        k=n+1-(1<<i);
        for(j=1;j<=k;++j)
        {
            a=sptb[i-1][j];
            b=sptb[i-1][j+(1<<(i-1))];
            sptb[i][j]=lcpa[a]<lcpa[b]?a:b;
        }
    }
}

inline int ask(int l,int r)
{
    a=lg[r-l+1];
    r-=(1<<a)-1;
    l=sptb[a][l];
    r=sptb[a][r];
    return lcpa[l]<lcpa[r]?l:r;
}

inline int lcp(int l,int r) // 字符串上[l,r]区间的rmq
{
    l=rk[l];
    r=rk[r];
    if(l>r)
        std::swap(l,r);
    return lcpa[ask(l+1,r)];
}
