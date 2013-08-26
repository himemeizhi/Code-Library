pv c;
double r;

inline double cal(const pv &a,const pv &b)
{
    static double A,B,C,x,y,ts;
    A=(b-c).len();
    B=(a-c).len();
    C=(a-b).len();
    if(A<r && B<r)
        return (a-c).cross(b-c)/2;
    x=((a-b).dot(c-b)+sqrt(r*r*C*C-sqr((a-b).cross(c-b))))/C;
    y=((b-a).dot(c-a)+sqrt(r*r*C*C-sqr((b-a).cross(c-a))))/C;
    ts=(a-c).cross(b-c)/2;

    if(A<r && B>=r)
        return asin(ts*(1-x/C)*2/r/B*(1-eps))*r*r/2+ts*x/C;
    if(A>=r && B<r)
        return asin(ts*(1-y/C)*2/r/A*(1-eps))*r*r/2+ts*y/C;

    if(fabs((a-c).cross(b-c))>=r*C || (b-a).dot(c-a)<=0 || (a-b).dot(c-b)<=0)
    {
        if((a-c).dot(b-c)<0)
        {
            if((a-c).cross(b-c)<0)
                return (-pi-asin((a-c).cross(b-c)/A/B*(1-eps)))*r*r/2;
            return (pi-asin((a-c).cross(b-c)/A/B*(1-eps)))*r*r/2;
        }
        return asin((a-c).cross(b-c)/A/B*(1-eps))*r*r/2;
    }

    return (asin(ts*(1-x/C)*2/r/B*(1-eps))+asin(ts*(1-y/C)*2/r/A*(1-eps)))*r*r/2+ts*((y+x)/C-1);
}

inline double get(pv *the,int n)
{
    double ans=0;
    for(int i=0;i<n;++i)
        ans+=cal(the[i],the[(i+1)%n]);
    return ans;
}
