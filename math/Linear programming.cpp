#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

#define MAXN 33
#define MAXM 33
#define eps 1e-8

double a[MAXN][MAXM],b[MAXN],c[MAXM];
double x[MAXM],d[MAXN][MAXM];
int ix[MAXN+MAXM];
double ans;
int n,m;
int i,j,k,r,s;
double D;

inline bool simplex()
{
    r=n;
    s=m++;
    for(i=0;i<n+m;++i)
        ix[i]=i;
    memset(d,0,sizeof d);
    for(i=0;i<n;++i)
    {
        for(j=0;j+1<m;++j)
            d[i][j]=-a[i][j];
        d[i][m-1]=1;
        d[i][m]=b[i];
        if(d[r][m]>d[i][m])
            r=i;
    }
    for(j=0;j+1<m;++j)
        d[n][j]=c[j];
    d[n+1][m-1]=-1;
    while(true)
    {
        if(r<n)
        {
            std::swap(ix[s],ix[r+m]);
            d[r][s]=1./d[r][s];
            for(j=0;j<=m;++j)
                if(j!=s)
                    d[r][j]*=-d[r][s];
            for(i=0;i<=n+1;++i)
                if(i!=r)
                {
                    for(j=0;j<=m;++j)
                        if(j!=s)
                            d[i][j]+=d[r][j]*d[i][s];
                    d[i][s]*=d[r][s];
                }
        }
        r=-1;
        s=-1;
        for(j=0;j<m;++j)
            if((s<0 || ix[s]>ix[j]) && (d[n+1][j]>eps || (d[n+1][j]>-eps && d[n][j]>eps)))
                s=j;
        if(s<0)
            break;
        for(i=0;i<n;++i)
            if(d[i][s]<-eps && (r<0 || (D=(d[r][m]/d[r][s]-d[i][m]/d[i][s]))<-eps || (D<eps && ix[r+m]>ix[i+m])))
                r=i;
        if(r<0)
            return false;
    }
    if(d[n+1][m]<-eps)
        return false;
    for(i=m;i<n+m;++i)
        if(ix[i]+1<m)
            x[ix[i]]=d[i-m][m]; // answer
    ans=d[n][m]; // maxium value
    return true;
}

int main()
{
    while(scanf("%d %d",&m,&n)!=EOF)
    {
        for(i=0;i<m;++i)
            scanf("%lf",c+i);  // max{ sum{c[i]*x[i]} }
        for(i=0;i<n;++i)
        {
            for(j=0;j<m;++j)
                scanf("%lf",a[i]+j); // sum{ a[i]*x[i] } <= b
            scanf("%lf",b+i);
            b[i]*=n;
        }
        simplex();
        printf("Nasa can spend %.0lf taka.\n",ceil(ans));
    }
    return 0;
}
