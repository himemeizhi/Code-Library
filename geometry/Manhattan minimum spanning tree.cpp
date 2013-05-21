#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 60000;
struct node {int x, y, k[2];} b[maxn];
struct bian {int a, b, c;} g[maxn * 8];
struct point{int k[2];} d[maxn * 8];
long long s[maxn], ans;
int i, n, m, a[maxn], lim, h, mid, bh[maxn * 2], f[maxn], num, e[maxn * 2], next[maxn * 2], first[maxn], tot;
int comx(int p, int q) {return b[p].x < b[q].x;}
int comy(int p, int q) {return b[p].y < b[q].y;}
int comc(const bian &p, const bian &q) {return p.c < q.c;}
int dist(int p, int q) {return abs(b[p].x - b[q].x) + abs(b[p].y - b[q].y);}
int maxbh(int p, int q, int k) {return b[p].k[k] > b[q].k[k] ? p : q;}
int minbh(int p, int q, int k) {return b[p].k[k] < b[q].k[k] ? p : q;}
int getfa(int x) {if (f[x] != x) f[x] = getfa(f[x]); return f[x];}
long long gcd(long long p, long long q) {return (!p || !q) ? p + q : gcd(q, p % q);}
void link(int u, int v)
{
    e[++num] = v, next[num] = first[u], first[u] = num;
    e[++num] = u, next[num] = first[v], first[v] = num;
}
void add(int x, int k)
{
    int y = h + b[x].k[1]; d[y].k[0] = minbh(d[y].k[0], x, 0);
    for (y >>= 1; y; y >>= 1) d[y].k[0] = minbh(d[y << 1].k[0], d[y << 1 ^ 1].k[0], 0);
    y = h + b[x].k[0];
    d[y].k[1] = k ? maxbh(x, d[y].k[1], 1) : minbh(d[y].k[1], x, 1);
    for (y >>= 1; y; y >>= 1)
        d[y].k[1] = k ? maxbh(x, d[y << 1].k[1], 1) : minbh(d[y << 1 ^ 1].k[1], x, 1);
}
int ask(int l, int r, int k, int boss)
{
    for (mid = 0, l += h - 1, r += h + 1; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) mid = boss ? maxbh(mid, d[l + 1].k[k], k) : minbh(mid, d[r - 1].k[k], k);
        if (r & 1) mid = boss ? maxbh(mid, d[r - 1].k[k], k) : minbh(mid, d[r - 1].k[k], k);
    } return mid;
}
void manhattan()
{
    sort(bh + 1, bh + m + 1, comx);
    b[0].k[0] = maxn * 3, b[0].k[1] = -1;
    for (add(bh[m], 1), i = m - 1; i; add(bh[i], 1), --i)
    {
        g[++tot].a = bh[i], g[tot].b = ask(b[bh[i]].k[1], lim, 0, 0);
        g[tot].c = dist(g[tot].a, g[tot].b);
        if (g[tot].b == 0) --tot;
        g[++tot].a = bh[i], g[tot].b = ask(1, b[bh[i]].k[0], 1, 1);
        g[tot].c = dist(g[tot].a, g[tot].b);
        if (g[tot].b == 0) --tot;
    }
    b[0].k[1] = b[0].k[0];
    memset(d, 0, sizeof(d));
    sort(bh + 1, bh + m + 1, comy);
    for (add(bh[m], 0), i = m - 1; i; add(bh[i], 0), --i)
    {
        g[++tot].a = bh[i], g[tot].b = ask(1, b[bh[i]].k[1], 0, 0);
        g[tot].c = dist(g[tot].a, g[tot].b);
        if (g[tot].b == 0) --tot;
        g[++tot].a = bh[i], g[tot].b = ask(1, b[bh[i]].k[0], 1, 0);
        g[tot].c = dist(g[tot].a, g[tot].b);
        if (g[tot].b == 0) --tot;
    }
}
void kruskal()
{
    sort(g + 1, g + tot + 1, comc);
    for (i = 1; i <= tot; ++i)
    {
        int f1 = getfa(g[i].a), f2 = getfa(g[i].b);
        if (f1 != f2) link(g[i].a, g[i].b), f[f1] = f2;
    } tot = 0; memset(f, 0, sizeof(f));
}
void dfs(int x, int fa)
{
    bh[++tot] = x;
    for (int p = first[x]; p; p = next[p])
        if (e[p] != fa) dfs(e[p], x), bh[++tot] = x;    
}
void del(int l, int r)
{
    if (l > r) return ;
    for (int j = l; j <= r; ++j)
        ans -= 1LL * f[a[j]] * f[a[j]], ans += 1LL * (--f[a[j]]) * f[a[j]];
}
void ins(int l, int r)
{
    if (l > r) return ;
    for (int j = l; j <= r; ++j)
        ans -= 1LL * f[a[j]] * f[a[j]], ans += 1LL * (++f[a[j]]) * f[a[j]];
}
int main()
{
    freopen("hose.in", "r", stdin);
    freopen("hose.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", a+i);
    for (i = 1; i <= m; ++i) 
    {
        scanf("%d%d", &b[bh[i] = f[i] = i].x, &b[i].y);
        b[i].k[0] = b[i].x + b[i].y;
        b[i].k[1] = b[i].y - b[i].x + maxn;
        lim = max(lim, max(b[i].k[0], b[i].k[1]));
    }
    for (h = 1; h <= lim; h <<= 1);
    manhattan();
    kruskal();
    dfs(1, 0);
    ins(b[bh[1]].x, b[bh[1]].y);
    for (s[1] = ans, i = 2; i <= tot; s[bh[i]] = ans, ++i)
    {
        ins(b[bh[i]].x, b[bh[i - 1]].x - 1);
        ins(b[bh[i - 1]].y + 1, b[bh[i]].y);
        del(b[bh[i - 1]].x, b[bh[i]].x - 1);
        del(b[bh[i]].y + 1, b[bh[i - 1]].y);
    }
    for (i = 1; i <= m; ++i)
    {
        long long fz = s[i] - b[i].k[1] - 1 + maxn, fm = 1LL * (b[i].k[1] + 1 - maxn) * (b[i].k[1] - maxn);
        long long gys = gcd(fz, fm);
        printf("%lld/%lld\n", fz/gys, fm/gys);
    }
    return 0;
}
