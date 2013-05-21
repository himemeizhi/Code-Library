int gcd(int a,int b) //gcd都能忘，真是弱得不能多说
{
    return b?gcd(b,a%b):a;
}
