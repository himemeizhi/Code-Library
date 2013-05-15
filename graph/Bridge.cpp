void dfs(const short &now,const short &fa)
{
    dfn[now]=low[now]=cnt++;
    for(int i(0);i<edge[now].size();++i)
        if(dfn[edge[now][i]]==-1)
        {
            dfs(edge[now][i],now);
            low[now]=std::min(low[now],low[edge[now][i]]);
            if(low[edge[now][i]]>dfn[now]) //如果子节点不能够走到父节点之前去,那么该边为桥
            {
                if(edge[now][i]<now)
                {
                    j=edge[now][i];
                    k=now;
                }
                else
                {
                    j=now;
                    k=edge[now][i];
                }
                ans.push_back(node(j,k));
            }
        }
        else
            if(edge[now][i]!=fa)
                low[now]=std::min(low[now],low[edge[now][i]]);
}
