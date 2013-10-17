/* hit 1789 Electricity
 * the graph may not connected
 * cnt records the number of BCC, it's an cut P if != 0*/
const int V = 10000;
vector<int> adj[V];
int low[V], dfn[V], cnt[V], depth;
void initialize(int n) 
{
    REP(i, 0, n) adj[i].clear();
    CC(cnt, 0);CC(dfn, 0);
    depth = 0;
}
void dfs(int x, const int ROOT) 
{
    low[x] = dfn[x] = ++depth;
    int s = adj[x].size(), w, num = 0;
    REP(i, 0, s) 
    {
        w = adj[x][i];
        if (!dfn[w]) 
        {
            num++;
            dfs(w, ROOT);
            low[x] = min(low[w], low[x]);
            if (x == ROOT && num >= 2)
                cnt[x]++;
            if (x != ROOT && dfn[x] <= low[w])
                cnt[x]++;
        }
        else low[x] = min(low[x], dfn[w]);
    }
}
int solve(int n) 
{
    int cc = 0;
    REP(i, 0, n) 
    {
        if (dfn[i] == 0) 
        {
            dfs(i, i);
            cc++;
        }
    }
    return cc;
}
int main() 
{
    int n, m, x, y;
    while (scanf("%d %d", &n, &m) == 2 && n + m) 
    {
        initialize(n);
        REP(i, 0, m) 
        {
            scanf("%d %d", &x, &y);
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        int ans = solve(n);
        if (m == 0) printf("%d\n", n - 1);
        else printf("%d\n", ans + *max_element(cnt, cnt + n));
    }
    return 0;
}
