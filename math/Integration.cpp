// `simpson公式用到的函数`
double F(double x) {
  return sqrt(1 + 4*a*a*x*x);
}

// `三点simpson法。这里要求F是一个全局函数`
double simpson(double a, double b) {
  double c = a + (b-a)/2;
  return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

// `自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点simpson值A`
double asr(double a, double b, double eps, double A) {
  double c = a + (b-a)/2;
  double L = simpson(a, c), R = simpson(c, b);
  if(fabs(L+R-A) <= 15*eps) 
      return L+R+(L+R-A)/15.0;
  return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}

// `自适应Simpson公式（主过程）`
double asr(double a, double b, double eps) 
{
  return asr(a, b, eps, simpson(a, b));
}

// `用自适应Simpson公式计算宽度为w，高度为h的抛物线长`
double parabola_arc_length(double w, double h) 
{
  a = 4.0*h/(w*w); // `修改全局变量a，从而改变全局函数F的行为`
  return asr(0, w/2, 1e-5)*2;
}

// thx for mzry
inline double f(double)
{
    /*
    define the function
    */
}

inline double simp(double l,double r)
{
    double h = (r-l)/2.0;
    return h*(f(l)+4*f((l+r)/2.0)+f(r))/3.0;
}

inline double rsimp(double l,double r) // call here
{
    double mid = (l+r)/2.0;
    if(fabs((simp(l,r)-simp(l,mid)-simp(mid,r)))/15 < eps)
        return simp(l,r);
    else
        return rsimp(l,mid)+rsimp(mid,r);
}

//Romberg

/* `Romberg 求定积分`
 * `输入：积分区间[a,b]，被积函数f(x,y,z)`
 * `输出：积分结果`
 * `f(x,y,z)示例：`
 * double f0( double x, double l, double t )
 * {
 * return sqrt(1.0+l*l*t*t*cos(t*x)*cos(t*x));
 * }
 */
double Integral(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t);

inline double Romberg (double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t)
{
#define MAX_N 1000
    int i, j, temp2, min;
    double h, R[2][MAX_N], temp4;
    for (i=0; i<MAX_N; i++) 
    {
        R[0][i] = 0.0;
        R[1][i] = 0.0;
    }
    h = b-a;
    min = (int)(log(h*10.0)/log(2.0)); //h should be at most 0.1
    R[0][0] = ((*f)(a, l, t)+(*f)(b, l, t))*h*0.50;
    i = 1;
    temp2 = 1;
    while (i<MAX_N)
    {
        i++;
        R[1][0] = 0.0;
        for (j=1; j<=temp2; j++)
            R[1][0] += (*f)(a+h*((double)j-0.50), l, t);
        R[1][0] = (R[0][0] + h*R[1][0])*0.50;
        temp4 = 4.0;
        for (j=1; j<i; j++) 
        {
            R[1][j] = R[1][j-1] + (R[1][j-1]-R[0][j-1])/(temp4-1.0);
            temp4 *= 4.0;
        }
        if ((fabs(R[1][i-1]-R[0][i-2])<eps) && (i>min))
            return R[1][i-1];
        h *= 0.50;
        temp2 *= 2;
        for (j=0; j<i; j++)
            R[0][j] = R[1][j];
    }
    return R[1][MAX_N-1];
}

inline double Integral(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t)
{
    const double pi(acos(-1.0f));
    int n;
    double R, p, res;
    n = (int)(floor)(b * t * 0.50 / pi);
    p = 2.0 * pi / t;
    res = b - (double)n * p;
    if (n)
        R = Romberg (a, p, f0, eps/(double)n, l, t);
    R = R * (double)n + Romberg( 0.0, res, f0, eps, l, t );
    return R/100.0;
}

//
inline double romberg(double a,double b)
{
#define MAXN 111
    double t[MAXN][MAXN];
    int n,k,i,m;
    double h,g,p;
    h=(double)(b-a)/2;
    t[0][0]=h*(func(a)+func(b));
    k=n=1;
    do
    {
        g=0;
        for(i=1;i<=n;i++)
            g+=func((a+((2*i-1)*h)));
        t[k][0]=(t[k-1][0]/2)+(h*g);
        p = 1.0;
        for(m=1;m<=k;m++)
        {
            p=p*4.0f;
            t[k-m][m]=(p*t[k-m+1][m-1]-t[k-m][m-1])/(p-1);
        }
        m-=1;
        h/=2;
        n*=2;
        k+=1;

    }
    while (fabs(t[0][m]-t[0][m-1])>eps);
    return t[0][m];
}
