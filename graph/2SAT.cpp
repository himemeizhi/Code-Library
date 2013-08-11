/*
x & y == true:
~x -> x
~y -> y

x & y == false:
x -> ~y
y -> ~x

x | y == true:
~x -> y
~y -> x

x | y == false:
x -> ~x
y -> ~y

x ^ y == true:
~x -> y
y -> ~x
x -> ~y
~y -> x

x ^ y == false:
x -> y
y -> x
~x -> ~y
~y -> ~x
*/
#include<cstdio>
#include<cstring>

#define MAXX 16111
#define MAXE 200111
#define v to[i]

int edge[MAXX],to[MAXE],nxt[MAXE],cnt;
inline void add(int a,int b)
{
    nxt[++cnt]=edge[a];
    edge[a]=cnt;
    to[cnt]=b;
}

bool done[MAXX];
int st[MAXX];

bool dfs(const int now)
{
    if(done[now^1])
        return false;
    if(done[now])
        return true;
    done[now]=true;
    st[cnt++]=now;
    for(int i(edge[now]);i;i=nxt[i])
        if(!dfs(v))
            return false;
    return true;
}

int n,m;
int i,j,k;

inline bool go()
{
    memset(done,0,sizeof done);
    for(i=0;i<n;i+=2)
        if(!done[i] && !done[i^1])
        {
            cnt=0;
            if(!dfs(i))
            {
                while(cnt)
                    done[st[--cnt]]=false;
                if(!dfs(i^1))
                    return false;
            }
        }
    return true;
}
//done array will be a solution with minimal lexicographical order
// or maybe we can solve it with dual SCC method, and get a solution by reverse the edges of DAG then product a topsort
