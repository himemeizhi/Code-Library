bool map[MAXX][MAXX],done[MAXX];
int in[MAXX],n,m;

bool dfs(int now)
{
    for(int i=0;i<m;i++)
        if(!done[i] && map[now][i])
        {
            done[i] = true;
            if(in[i]==-1 || dfs(in[i]))
            {
                in[i]=now;
                return true;
            }
        }
    return false;
}

inline int go()
{
    memset(in,-1,sizeof(in));
    static int ans,i;
    for(ans=i=0;i<n;i++)
    {
        memset(done,false,sizeof done);
        if (dfs(i))
            ++ans;
    }
    return ans;
}
