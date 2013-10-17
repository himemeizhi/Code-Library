void solve(int x)
{
    int i;
    if (!match[x])
    {
        path[++l]=x;
        return ;
    }
    for (i=1; i<=n; i++)
        if (b[x][i])
        {
            b[x][i]--;
            match[x]--;
            solve(i);
        }
    path[++l]=x;
}

int stack[M], top, len;
void dfs(int v)
{
    stack[++top] = v;
    while (top)
    {
        int x = stack[top];
        bool flag = true;
        for (int i = p[x]; i != -1; i = e[i].next)
            if (e[i].f)
            {
                e[i].f = false; // order here
                stack[++top] = e[i].v;
                flag = false;
                break;
            }
        if (flag) stack[top--] = 0;
    }
}

