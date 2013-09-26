//normal
int num[MAXX],min[MAXX][20];
int lg[MAXX];

inline int init(int n)
{
    static int i,j,k,l,j_,j__;
    for(i=2;i<MAXX;++i)
        lg[i]=lg[i>>1]+1;
    for(i=1;i<=n;++i)
        min[i][0]=num[i];
    for(j=1;j<=lg[n];++j)
    {
        l=n+1-(1<<j);
        j_=j-1;
        j__=(1<<j_);
        for(i=1;i<=l;++i)
            min[i][j]=std::min(min[i][j_],min[i+j__][j_]);
    }
}

inline int query(int i,int j)
{
    static int k;
    k=lg[j-i+1];
    return std::min(min[i][k],min[j-(1<<k)+1][k]);
}

//rectangle
int lg[MAXX];
int table[9][9][MAXX][MAXX];
int mat[MAXX][MAXX]

inline void init(int n)
{
    static int i,j,ii,jj;
    for(i=2;i<MAXX;++i)
        lg[i]=lg[i>>1]+1;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            table[0][0][i][j]=mat[i][j];
    for(i=0;i<=lg[n];++i)
        for(j=0;j<=lg[n];++j)
        {
            if(i==0 && j==0)
                continue;
            for(ii=0;ii+(1<<j)<=n;++ii)
                for(jj=0;jj+(1<<i)<=n;++jj)
                    if(i==0)
                        table[i][j][ii][jj]=std::min(table[i][j-1][ii][jj],table[i][j-1][ii+(1<<(j-1))][jj]);
                    else
                        table[i][j][ii][jj]=std::min(table[i-1][j][ii][jj],table[i-1][j][ii][jj+(1<<(i-1))]);
        }
}

inline int query(int r1,int c1,int r2,int c2)
{
    --r1;
    --c1;
    --r2;
    --c2;
    static int w,h;
    w=lg[c2-c1+1];
    h=lg[r2-r1+1];
    return std::min(table[w][h][r1][c1],std::min(table[w][h][r1][c2-(1<<w)+1],std::min(table[w][h][r2-(1<<h)+1][c1],table[w][h][r2-(1<<h)+1][c2-(1<<w)+1])));
}

//square
int num[MAXX][MAXX],max[MAXX][MAXX][10];
int lg[MAXX];

inline void init(int n)
{
    static int i,j,k,l;
    for(i=2;i<MAXX;++i)
        lg[i]=lg[i>>1]+1;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            max[i][j][0]=num[i][j];
    for(k=1;k<=lg[n];++k)
    {
        l=n+1-(1<<k);
        for(i=0;i<l;++i)
            for(j=0;j<l;++j)
                max[i][j][k]=std::max(std::max(max[i][j][k-1],max[i+(1<<(k-1))][j][k-1]),std::max(max[i][j+(1<<(k-1))][k-1],max[i+(1<<(k-1))][j+(1<<(k-1))][k-1]));
    }
}

inline int query(int i,int j,int l)
{
    static int k;
    --i;
    --j;
    k=lg[l];
    return std::max(std::max(max[i][j][k],max[i][j+l-(1<<k)][k]),std::max(max[i+l-(1<<k)][j][k],max[i+l-(1<<k)][j+l-(1<<k)][k]));
}
