#include<cstdio>
#include<cstring>

const int maxN = 1111, maxM = 1111;
const int max_size = maxN * maxM;
const int inf = 0x3f3f3f3f;

int L[max_size], R[max_size], U[max_size], D[max_size], CH[max_size], RH[max_size];
int S[maxM], O[maxM];
int head, size;

int node(int up, int down, int left, int right) {
    U[size] = up, D[size] = down;
    L[size] = left, R[size] = right;
    D[up] = U[down] = R[left] = L[right] = size;
    return size++;
}
bool mat[maxN][maxM];

void init(int N, int M) {
    size = 0;
    head = node(0, 0, 0, 0);
    for (int j = 1; j <= M; ++j) {
        CH[j] = node(size, size, L[head], head), S[j] = 0;
    }
    for (int i = 1; i <= N; ++i) {
        int row = -1, k;
        for (int j = 1; j <= M; ++j) {
            if (!mat[i][j]) continue;
            if (row == -1) {
                row = node(U[CH[j]], CH[j], size, size);
                RH[row] = i, CH[row] = CH[j], ++S[j];
            } else {
                k = node(U[CH[j]], CH[j], L[row], row);
                RH[k] = i, CH[k] = CH[j], ++S[j];
            }
        }
    }
}
void remove(const int &c) {
    L[R[c]] = L[c], R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j]) {
            U[D[j]] = U[j], D[U[j]] = D[j];
            --S[CH[j]];
        }
    }
}
void resume(const int &c) {
    for (int i = U[c]; i != c; i = U[i]) {
        for (int j = L[i]; j != i; j = L[j]) {
            ++S[CH[j]];
            U[D[j]] = D[U[j]] = j;
        }
    }
    L[R[c]] = R[L[c]] = c;
}
int len;
bool DLX(const int &k) {
    if (R[head] == head) {
        len = k - 1;
        return true;
    }
    int s = inf, c;
    for (int t = R[head]; t != head; t = R[t]) {
        if (S[t] < s) s = S[t], c = t;
    }
    remove(c);
    for (int i = D[c]; i != c; i = D[i]) {
        O[k] = RH[i];
        for (int j = R[i]; j != i; j = R[j]) {
            remove(CH[j]);
        }
        if (DLX(k + 1)) {
            return true;
        }
        for (int j = L[i]; j != i; j = L[j]) {
            resume(CH[j]);
        }
    }
    resume(c);
    return false;
}

int n,m,i,j,k;

int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        memset(mat,0,sizeof(mat));
        for(i=1;i<=n;++i)
        {
            scanf("%d",&j);
            while(j--)
            {
                scanf("%d",&k);
                mat[i][k]=true;
            }
        }
        init(n,m);
        if(!DLX(0))
            puts("NO");
        else
        {
            printf("%d",len+1);
            for(i=0;i<=len;++i)
                printf(" %d",O[i]);
            puts("");
        }
    }
    return 0;
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
