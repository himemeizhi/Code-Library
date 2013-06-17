#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

#define N 256
#define MAXN N*22
#define MAXM N*5
#define inf 0x3f3f3f3f
const int MAXX(MAXN*MAXM);

bool mat[MAXN][MAXM];

int u[MAXX],d[MAXX],l[MAXX],r[MAXX],ch[MAXX],rh[MAXX];
int sz[MAXM];
std::vector<int>ans(MAXX);
int hd,cnt;

inline int node(int up,int down,int left,int right)
{
    u[cnt]=up;
    d[cnt]=down;
    l[cnt]=left;
    r[cnt]=right;
    u[down]=d[up]=l[right]=r[left]=cnt;
    return cnt++;
}

inline void init(int n,int m)
{
    cnt=0;
    hd=node(0,0,0,0);
    static int i,j,k,r;
    for(j=1;j<=m;++j)
    {
        ch[j]=node(cnt,cnt,l[hd],hd);
        sz[j]=0;
    }
    for(i=1;i<=n;++i)
    {
        r=-1;
        for(j=1;j<=m;++j)
            if(mat[i][j])
            {
                if(r==-1)
                {
                    r=node(u[ch[j]],ch[j],cnt,cnt);
                    rh[r]=i;
                    ch[r]=ch[j];
                }
                else
                {
                    k=node(u[ch[j]],ch[j],l[r],r);
                    rh[k]=i;
                    ch[k]=ch[j];
                }
                ++sz[j];
            }
    }
}

inline void rm(int c)
{
    l[r[c]]=l[c];
    r[l[c]]=r[c];
    static int i,j;
    for(i=d[c];i!=c;i=d[i])
        for(j=r[i];j!=i;j=r[j])
        {
            u[d[j]]=u[j];
            d[u[j]]=d[j];
            --sz[ch[j]];
        }
}

inline void add(int c)
{
    static int i,j;
    for(i=u[c];i!=c;i=u[i])
        for(j=l[i];j!=i;j=l[j])
        {
            ++sz[ch[j]];
            u[d[j]]=d[u[j]]=j;
        }
    l[r[c]]=r[l[c]]=c;
}

bool dlx(int k)
{
    if(hd==r[hd])
    {
        ans.resize(k);
        return true;
    }
    int s=inf,c;
    int i,j;
    for(i=r[hd];i!=hd;i=r[i])
        if(sz[i]<s)
        {
            s=sz[i];
            c=i;
        }
    rm(c);
    for(i=d[c];i!=c;i=d[i])
    {
        ans[k]=rh[i];
        for(j=r[i];j!=i;j=r[j])
            rm(ch[j]);
        if(dlx(k+1))
            return true;
        for(j=l[i];j!=i;j=l[j])
            add(ch[j]);
    }
    add(c);
    return false;
}

#include <cstdio>
#include <cstring>

#define N 1024
#define M 1024*110
using namespace std;

int l[M], r[M], d[M], u[M], col[M], row[M], h[M], res[N], cntcol[N];
int dcnt = 0;
//初始化一个节点
inline void addnode(int &x)
{
    ++x;
    r[x] = l[x] = u[x] = d[x] = x;
}
//将x加入到rowx后
inline void insert_row(int rowx, int x)
{
    r[l[rowx]] = x;
    l[x] = l[rowx];
    r[x] = rowx;
    l[rowx] = x;
}
//将x加入到colx后
inline void insert_col(int colx, int x)
{
    d[u[colx]] = x;
    u[x] = u[colx];
    d[x] = colx;
    u[colx] = x;
}
//全局初始化
inline void dlx_init(int cols)
{
    memset(h, -1, sizeof(h));
    memset(cntcol, 0, sizeof(cntcol));
    dcnt = -1;
    addnode(dcnt);
    for (int i = 1; i <= cols; ++i)
    {
        addnode(dcnt);
        insert_row(0, dcnt);
    }
}
//删除一列以及相关的所有行
inline void remove(int c)
{
    l[r[c]] = l[c];
    r[l[c]] = r[c];
    for (int i = d[c]; i != c; i = d[i])
        for (int j = r[i]; j != i; j = r[j])
        {
            u[d[j]] = u[j];
            d[u[j]] = d[j];
            cntcol[col[j]]--;
        }
}
//恢复一列以及相关的所有行
inline void resume(int c)
{
    for (int i = u[c]; i != c; i = u[i])
        for (int j = l[i]; j != i; j = l[j])
        {
            u[d[j]] = j;
            d[u[j]] = j;
            cntcol[col[j]]++;
        }
    l[r[c]] = c;
    r[l[c]] = c;
}
//搜索部分
bool DLX(int deep)
{
    if (r[0] == 0)
    {
//Do anything you want to do here
        printf("%d", deep);
        for (int i = 0; i < deep; ++i) printf(" %d", res[i]);
        puts("");
        return true;
    }
    int min = INT_MAX, tempc;
    for (int i = r[0]; i != 0; i = r[i])
        if (cntcol[i] < min)
        {
            min = cntcol[i];
            tempc = i;
        }
    remove(tempc);
    for (int i = d[tempc]; i != tempc; i = d[i])
    {
        res[deep] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (DLX(deep + 1)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
    }
    resume(tempc);
    return false;
}
//插入矩阵中的"1"节点
inline void insert_node(int x, int y)
{
    cntcol[y]++;
    addnode(dcnt);
    row[dcnt] = x;
    col[dcnt] = y;
    insert_col(y, dcnt);
    if (h[x] == -1) h[x] = dcnt;
    else insert_row(h[x], dcnt);
}
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        dlx_init(m);
        for (int i = 1; i <= n; ++i)
        {
            int k, x;
            scanf("%d", &k);
            while (k--)
            {
                scanf("%d", &x);
                insert_node(i, x);
            }
        }
        if (!DLX(0)) 
            puts("NO");
    }
    return 0;
}
