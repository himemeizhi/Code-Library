/*
`$\frac{(x-h)^2}{a^2} + \frac{(y-k)^2}{b^2} = 1$`

`$x=h+a \times \cos(t)$`
`$y=k+b \times \sin(t)$`

area=`$\pi \times a \times b$`
distance from center to focus: `$f=\sqrt{a^2-b^2}$`
eccentricity: `$e=\sqrt{a-\frac{b}{a}^2}=\frac{f}{a}$`
focal parameter: `$\frac{b^2}{\sqrt{a^2-b^2}}=\frac{b^2}{f}$`
*/

inline double circumference(double a,double b) // accuracy: pow(0.5,53);
{
    static double digits=53;
    static double tol=sqrt(pow(0.5,digits));
    double x=a;
    double y=b;
    if(x<y)
        std::swap(x,y);
    if(digits*y<tol*x)
        return 4*x;
    double s=0,m=1;
    while(x>(tol+1)*y)
    {
        double tx=x;
        double ty=y;
        x=0.5f*(tx+ty);
        y=sqrt(tx*ty);
        m*=2;
        s+=m*pow(x-y,2);
    }
    return pi*(pow(a+b,2)-s)/(x+y);
}