#include<cstdio>
#include<cstring>
#include<vector>

#define MAXX 1111
#define MAXE 10111
#define inf 0x3f3f3f3f

int n,m,i,j,k,ans,u,v,tn,rt,sum,on,om;
int pre[MAXX],id[MAXX],in[MAXX],vis[MAXX];

struct edge
{
    int a,b,c;
    edge(){}
    edge(int aa,int bb,int cc):a(aa),b(bb),c(cc){}
};
std::vector<edge>ed(MAXE);

int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        on=n;
        om=m;
        ed.resize(0);
        sum=1;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i!=j)
            {
                ed.push_back(edge(i,j,k));
                sum+=k;
            }
        }
        ans=0;
        rt=n;
        for(i=0;i<n;++i)
            ed.push_back(edge(n,i,sum));
        ++n;
        while(true)
        {
            memset(in,0x3f,sizeof in);
            for(i=0;i<ed.size();++i)
                if(ed[i].a!=ed[i].b && in[ed[i].b]>ed[i].c)
                {
                    in[ed[i].b]=ed[i].c;
                    pre[ed[i].b]=ed[i].a;
                    if(ed[i].a==rt)
                        j=i;
                }
            for(i=0;i<n;++i)
                if(i!=rt && in[i]==inf)
                    goto ot;
            memset(id,-1,sizeof id);
            memset(vis,-1,sizeof vis);
            tn=in[rt]=0;
            for(i=0;i<n;++i)
            {
                ans+=in[i];
                for(v=i;vis[v]!=i && id[v]==-1 && v!=rt;v=pre[v])
                    vis[v]=i;
                if(v!=rt && id[v]==-1)
                {
                    for(u=pre[v];u!=v;u=pre[u])
                        id[u]=tn;
                    id[v]=tn++;
                }
            }
            if(!tn)
                break;
            for(i=0;i<n;++i)
                if(id[i]==-1)
                    id[i]=tn++;
            for(i=0;i<ed.size();++i)
            {
                v=ed[i].b;
                ed[i].a=id[ed[i].a];
                ed[i].b=id[ed[i].b];
                if(ed[i].a!=ed[i].b)
                    ed[i].c-=in[v];
            }
            n=tn;
            rt=id[rt];
        }
        if(ans>=2*sum)
ot:            puts("impossible");
        else
            printf("%d %d\n",ans-sum,j-om);
        puts("");
    }
    return 0;
}
