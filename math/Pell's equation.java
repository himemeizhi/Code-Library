/*
find the (x,y)pair that x^2-n*y^2=1
these is not solution if and only if n is a square number.

solution:
simply brute-force search the integer y, get (x1,y1). ( toooo slow in some situation )
or we can enumerate the continued fraction of sqrt(n), as (x/y), it will be much more faster

other solution pairs' matrix:
[ x1 n*y1 ]
[ y1 x1   ]
k-th solution is pow({matrix},k)
*/

import java.util.*;
import java.math.*;

public class Main 
{
    static BigInteger p,q,p1,p2,p3,q1,q2,q3,a1,a2,a0,h1,h2,g1,g2,n0;
    static int n,t;
    static void solve()
    {
        p2=BigInteger.ONE;
        p1=BigInteger.ZERO;
        q2=BigInteger.ZERO;
        q1=BigInteger.ONE;
        a0=a1=BigInteger.valueOf((long)Math.sqrt(n));
        g1=BigInteger.ZERO;
        h1=BigInteger.ONE;
        n0=BigInteger.valueOf(n);
        while(true)
        {
            g2=a1.multiply(h1).subtract(g1);
            h2=(n0.subtract(g2.multiply(g2))).divide(h1);
            a2=(g2.add(a0)).divide(h2);
            p=p2.multiply(a1).add(p1);
            q=q2.multiply(a1).add(q1);
            if(p.multiply(p).subtract(n0.multiply(q.multiply(q))).equals(BigInteger.ONE))
                return ;
            a1=a2;
            g1=g2;
            h1=h2;
            p1=p2;
            p2=p;
            q1=q2;
            q2=q;
        }
    }
    public static void main(String[] args) 
    {
        Scanner in=new Scanner(System.in);
        t=in.nextInt();
        for(int i=0;i<t;++i)
        {
            n=in.nextInt();
            solve();
            System.out.println(p+" "+q);
        }
    }
}
