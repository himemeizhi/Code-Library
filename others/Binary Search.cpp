//[0,n)
inline int go(int A[],int n,int x) // return the least i that make A[i]==x;
{
    static int l,r,mid,re;
    l=0;
    r=n-1;
    re=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(A[mid]<x)
            l=mid+1;
        else
        {
            r=mid-1;
            if(A[mid]==x)
                re=mid;
        }
    }
    return re;
}

inline int go(int A[],int n,int x) // return the largest i that make A[i]==x;
{
    static int l,r,mid,re;
    l=0;
    r=n-1;
    re=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(A[mid]<=x)
        {
            l=mid+1;
            if(A[mid]==x)
                re=mid;
        }
        else
            r=mid-1;
    }
    return re;
}

inline int go(int A[],int n,int x) // retrun the largest i that make A[i]<x;
{
    static int l,r,mid,re;
    l=0;
    r=n-1;
    re=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(A[mid]<x)
        {
            l=mid+1;
            re=mid;
        }
        else
            r=mid-1;
    }
    return re;
}

inline int go(int A[],int n,int x)// return the largest i that make A[i]<=x;
{
    static int l,r,mid,re;
    l=0;
    r=n-1;
    re=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(A[mid]<=x)
        {
            l=mid+1;
            re=mid;
        }
        else
            r=mid-1;
    }
    return re;
}

inline int go(int A[],int n,int x)// return the least i that make A[i]>x;
{
    static int l,r,mid,re;
    l=0;
    r=n-1;
    re=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(A[mid]<=x)
            l=mid+1;
        else
        {
            r=mid-1;
            re=mid;
        }
    }
    return re;
}

inline int go(int A[],int n,int x)// upper_bound();
{
    static int l,r,mid;
    l=0;
    r=n-1;
    while(l<r)
    {
        mid=l+r>>1;
        if(A[mid]<=x)
            l=mid+1;
        else
            r=mid;
    }
    return r;
}

inline int go(int A[],int n,int x)// lower_bound();
{
    static int l,r,mid,;
    l=0;
    r=n-1;
    while(l<r)
    {
        mid=l+r>>1;
        if(A[mid]<x)
            l=mid+1;
        else
            r=mid;
    }
    return r;
}
