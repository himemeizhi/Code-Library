#include<iostream>
#include<cstdio>
#include<algorithm>

#define MAXX 310

int mat[MAXX][MAXX];
int table[9][9][MAXX][MAXX];
int n;
short lg[MAXX];

int main()
{
    for(int i(2);i<MAXX;++i)
        lg[i]=lg[i>>1]+1;
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) 
            {
                std::cin >> mat[i][j];
                table[0][0][i][j] = mat[i][j];
            }
        
        // 从小到大计算，保证后来用到的都已经计算过
        for(int i=0;i<=lg[n];++i) // width
        {
            for(int j=0;j<=lg[n];++j) //height
            {
                if(i==0 && j==0)
                    continue;
                for(int ii=0;ii+(1<<j)<=n;++ii)
                    for(int jj=0;jj+(1<<i)<=n;++jj)
                        if(i==0)
                            table[i][j][ii][jj]=std::min(table[i][j-1][ii][jj],table[i][j-1][ii+(1<<(j-1))][jj]);
                        else
                            table[i][j][ii][jj]=std::min(table[i-1][j][ii][jj],table[i-1][j][ii][jj+(1<<(i-1))]);
            }
        }
        long long N;
        std::cin >> N;
        int r1, c1, r2, c2;
        for (int i = 0; i < N; ++i) 
        {
            scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
            --r1;
            --c1;
            --r2;
            --c2;
            int w=lg[c2-c1+1];
            int h=lg[r2-r1+1];
            printf("%d\n",std::min(table[w][h][r1][c1],std::min(table[w][h][r1][c2-(1<<w)+1],std::min(table[w][h][r2-(1<<h)+1][c1],table[w][h][r2-(1<<h)+1][c2-(1<<w)+1]))));
        }
    }
    return 0;
}
