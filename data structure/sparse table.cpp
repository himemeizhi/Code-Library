int num[MAXX],min[MAXX][20];
int lg[MAXX];


int main()
{
    for(i=2;i<MAXX;++i)
        lg[i]=lg[i>>1]+1;
    scanf("%d %d",&n,&q);
    for(i=1;i<=n;++i)
    {
        scanf("%d",num+i);
        min[i][0]=num[i];
    }
    for(j=1;j<=lg[n];++j)
    {
        l=n+1-(1<<j);
        j_=j-1;
        j__=(1<<j_);
        for(i=1;i<=l;++i)
            min[i][j]=std::min(min[i][j_],min[i+j__][j_]);
    }
    printf("Case %hd:\n",t);
    while(q--)
    {
        scanf("%d %d",&i,&j);
        k=lg[j-i+1];
        printf("%d\n",std::min(min[i][k],min[j-(1<<k)+1][k]));
    }
}
