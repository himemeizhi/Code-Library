#include<cstdio>
#include<list>
#include<algorithm>
#include<cstring>

#define MAXX 100111
#define inf 0x5fffffff

short T,t;
int set[MAXX],min[MAXX],max[MAXX],ans[2][MAXX];
bool done[MAXX];
std::list<std::pair<int,int> >edge[MAXX];
std::list<std::pair<int,int> >q[MAXX];
int n,i,j,k,l,m;

struct node
{
    int a,b,id;
    node() {}
    node(const int &aa,const int &bb,const int &idd): a(aa),b(bb),id(idd){}
};

std::list<node>to[MAXX];

int find(const int &a)
{
    if(set[a]==a)
        return a;
    int b(set[a]);
    set[a]=find(set[a]);
    max[a]=std::max(max[a],max[b]);
    min[a]=std::min(min[a],min[b]);
    return set[a];
}

void tarjan(const int &now)
{
    done[now]=true;
    for(std::list<std::pair<int,int> >::const_iterator it(q[now].begin());it!=q[now].end();++it)
        if(done[it->first])
            if(it->second>0)
                to[find(it->first)].push_back(node(now,it->first,it->second));
            else
                to[find(it->first)].push_back(node(it->first,now,-it->second));
    for(std::list<std::pair<int,int> >::const_iterator it(edge[now].begin());it!=edge[now].end();++it)
        if(!done[it->first])
        {
            tarjan(it->first);
            set[it->first]=now;
            min[it->first]=it->second;
            max[it->first]=it->second;
        }
    for(std::list<node>::const_iterator it(to[now].begin());it!=to[now].end();++it)
    {
        find(it->a);
        find(it->b);
        ans[0][it->id]=std::min(min[it->b],min[it->a]);
        ans[1][it->id]=std::max(max[it->a],max[it->b]);
    }
}

int main()
{
    scanf("%hd",&T);
    for(t=1;t<=T;++t)
    {
        scanf("%d",&n);
        for(i=1;i<=n;++i)
        {
            edge[i].clear();
            q[i].clear();
            to[i].clear();
            done[i]=false;
            set[i]=i;
            min[i]=inf;
            max[i]=0;
        }
        for(i=1;i<n;++i)
        {
            scanf("%d%d%d",&j,&k,&l);
            edge[j].push_back(std::make_pair(k,l));
            edge[k].push_back(std::make_pair(j,l));
        }
        scanf("%d",&m);
        for(i=0;i<m;++i)
        {
            scanf("%d %d",&j,&k);
            q[j].push_back(std::make_pair(k,i));
            q[k].push_back(std::make_pair(j,-i));
        }
        tarjan(1);
        printf("Case %hd:\n",t);
        for(i=0;i<m;++i)
            printf("%d %d\n",ans[0][i],ans[1][i]);
    }
    return 0;
}
