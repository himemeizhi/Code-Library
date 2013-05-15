//对于每个预备队列中的对象，及被匹配对象，先按照喜好程度排列匹配对象

while(!g.empty())  // 预备匹配队列
{
    if(dfn[edge[g.front()].front()]==-1)
        dfn[edge[g.front()].front()]=g.front(); // 如果目前还没尝试匹配过的对象没有被任何别的对象占据
    else
    {
        for(it=edge[edge[g.front()].front()].begin();it!=edge[edge[g.front()].front()].end();++it)
            if(*it==dfn[edge[g.front()].front()] || *it==g.front()) //如果被匹配对象更喜欢正在被匹配的人或现在准备匹配的对象
                break;
        if(*it==g.front()) //如果更喜欢新的
        {
            g.push_back(dfn[edge[g.front()].front()]);
            dfn[edge[g.front()].front()]=g.front();
        }
        else
            g.push_back(g.front()); //否则放到队尾，重新等待匹配
    }
    edge[g.front()].pop_front(); //每组匹配最多只考虑一次
    g.pop_front();
}
