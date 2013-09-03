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

/*
Simplex C(n+m)(n)
maximize:
    `$\sum\limits_{i=1}^n{(c[i]\times x[i])}$`
subject to
    `$ \forall i \in [1,m]$`
    `$ \sum\limits_{j=1}^n{(a[i][j]\times x[j])} \leq rhs[i]$`
`限制:`
    `传入的矩阵必须是标准形式的.`
sample:
3 3
15 17 20
0 1 -1 2
3 3 5 15
3 2 1 8
out:
OPTIMAL
76.00000
x[ 1 ] = 0.333333
x[ 2 ] = 3.000000
x[ 3 ] = 1.000000
*/

#include <cstdio>
#include <cstring>
#include <cmath>

#define eps 1e-8
#define inf 1e15
#define OPTIMAL -1 //`最优解`
#define UNBOUNDED -2 //`无边界的`
#define FEASIBLE -3 //`可行的`
#define INFEASIBLE -4 //`无解`
#define PIVOT_OK 1 //`还可以松弛`

#define N 45 //`变量个数`
#define M 45 //`约束个数`

int basic[N],row[M],col[N];
double c0[N];

inline double dcmp(double x) 
{
    if(x>eps)
        return 1;
    if(x<-eps)
        return -1;
    return 0;
}

inline int Pivot(int n,int m,double *c,double a[M][N],double *rhs,int &i,int &j) 
{
    double min=inf;
    int k=-1;
    for(j=0;j<=n;j++)
        if(!basic[j] && dcmp(c[j])>0)
            if(k<0 || dcmp(c[j]-c[k])>0)
                k=j;
    j=k;
    if(k<0) 
        return OPTIMAL;
    for(k=-1,i=1;i<=m;i++)
        if(dcmp(a[i][j])>0 && dcmp(rhs[i]/a[i][j]-min)<0) 
        {
            min=rhs[i]/a[i][j];
            k=i;
        }
    i=k;
    if(k<0) 
        return UNBOUNDED;
    return PIVOT_OK;
}

inline int PhaseII(int n,int m,double *c,double a[M][N],double *rhs,double &ans,int PivotIndex) 
{
    static int i,j,k,l;
    static double tmp;
    while((k=Pivot(n,m,c,a,rhs,i,j))==PIVOT_OK || PivotIndex) 
    {
        if(PivotIndex) 
        {
            i=PivotIndex;
            j=PivotIndex=0;
        }
        basic[row[i]]=0;
        col[row[i]]=0;
        basic[j]=1;
        col[j]=i;
        row[i]=j;
        tmp=a[i][j];
        for(k=0;k<=n;k++)
            a[i][k]/=tmp;
        rhs[i]/=tmp;
        for(k=1;k<=m;k++)
            if(k!=i && dcmp(a[k][j])) 
            {
                tmp=-a[k][j];
                for(l=0;l<=n;l++)
                    a[k][l]+=tmp*a[i][l];
                rhs[k]+=tmp*rhs[i];
            }
        tmp=-c[j];
        for(l=0;l<=n;l++)
            c[l]+=a[i][l]*tmp;
        ans-=tmp*rhs[i];
    }
    return k;
}

inline int PhaseI(int n,int m,double *c,double a[M][N],double *rhs,double &ans) 
{
    int i,j,k=-1;
    double tmp,min=0,ans0=0;
    for(i=1;i<=m;i++)
        if(dcmp(rhs[i]-min)<0)
        {
            min=rhs[i];
            k=i;
        }
    if(k<0)
        return FEASIBLE;
    for(i=1;i<=m;i++)
        a[i][0]=-1;
    for(j=1;j<=n;j++) 
        c0[j]=0;
    c0[0]=-1;
    PhaseII(n,m,c0,a,rhs,ans0,k);
    if(dcmp(ans0)<0)
        return INFEASIBLE;
    for(i=1;i<=m;i++) 
        a[i][0]=0;
    for(j=1;j<=n;j++)
        if(dcmp(c[j]) && basic[j]) 
        {
            tmp=c[j];
            ans+=rhs[col[j]]*tmp;
            for(i=0;i<=n;i++)
                c[i]-=tmp*a[col[j]][i];
        }
    return FEASIBLE;
}
inline int simplex(int n,int m,double *c,double a[M][N],double *rhs,double &ans,double *x) 
{
    int i,j,k;
    for(i=1;i<=m;i++) 
    {
        for(j=n+1;j<=n+m;j++)
            a[i][j]=0;
        a[i][n+i]=1;
        a[i][0]=0;
        row[i]=n+i;
        col[n+i]=i;
    }
    k=PhaseI(n+m,m,c,a,rhs,ans);
    if(k==INFEASIBLE)
        return k; //无解
    k=PhaseII(n+m,m,c,a,rhs,ans,0);
    for(j=0;j<=n+m;j++)
        x[j] = 0;
    for(i=1;i<=m;i++)
        x[row[i]] = rhs[i];
    return k;
}

double c[M],ans,a[M][N],rhs[M],x[N];

int main() 
{
    int i,j,n,m;
    while(scanf("%d%d",&n,&m)!=EOF) 
    {
        for(int i=0;i<=n+m;i++) 
        {
            for(int j=0;j<=n+m;j++)
                a[i][j]=0;
            basic[i]=0;
            row[i]=0;
            col[i]=0;
            c[i]=0;
            rhs[i]=0;
        }
        ans=0;

        for(j=1;j<=n;++j)
            scanf("%lf",c+j);
        for(i=1;i<=m;++i) 
        {
            for(j=1;j<=n;++j)
                scanf("%lf",a[i]+j);
            scanf("%lf",rhs+i);
        }

        switch(simplex(n,m,c,a,rhs,ans,x)) 
        {
            case OPTIMAL:
                printf("Nasa can spend %.0f taka.\n",ceil(m*ans));
                //for(j=1;j<=n;j++)
                //    printf("x[ %2d ] = %10lf\n",j,x[j]);
                break;
            case UNBOUNDED:
                puts("UNBOUNDED");
                break;
            case INFEASIBLE:
                puts("INFEASIBLE");
                break;
        }
    }
    return 0;
}
