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
