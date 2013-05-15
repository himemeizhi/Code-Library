void dfs(int now,int fa)  // now从1开始
{
    int p(0);
    dfn[now]=low[now]=cnt++;
    for(std::list<int>::const_iterator it(edge[now].begin());it!=edge[now].end();++it)
        if(dfn[*it]==-1)
        {
            dfs(*it,now);
            ++p;
            low[now]=std::min(low[now],low[*it]);
            if((now==1 && p>1) || (now!=1 && low[*it]>=dfn[now])) // 如果从出发点出发的子节点不能由兄弟节点到达，那么出发点为割点。 如果现节点不是出发点，但是其子孙节点不能达到祖先节点，那么该节点为割点
                ans.insert(now);
        }
        else
            if(*it!=fa)
                low[now]=std::min(low[now],dfn[*it]);
}
