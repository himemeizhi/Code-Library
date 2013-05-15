int num[MAXX][MAXX],max[MAXX][MAXX][10];
short lg[MAXX];

int main()
{
    for(i=2;i<MAXX;++i)
        lg[i]=lg[i>>1]+1;
    scanf("%hd %d",&n,&q);
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        {
            scanf("%d",num[i]+j);
            max[i][j][0]=num[i][j];
        }
    for(k=1;k<=lg[n];++k)
    {
        l=n+1-(1<<k);
        for(i=0;i<l;++i)
            for(j=0;j<l;++j)
                max[i][j][k]=std::max(std::max(max[i][j][k-1],max[i+(1<<(k-1))][j][k-1]),std::max(max[i][j+(1<<(k-1))][k-1],max[i+(1<<(k-1))][j+(1<<(k-1))][k-1]));
    }
    printf("Case %hd:\n",t);
    while(q--)
    {
        scanf("%hd %hd %hd",&i,&j,&l);
        --i;
        --j;
        k=lg[l];
        printf("%d\n",std::max(std::max(max[i][j][k],max[i][j+l-(1<<k)][k]),std::max(max[i+l-(1<<k)][j][k],max[i+l-(1<<k)][j+l-(1<<k)][k])));
    }
}
