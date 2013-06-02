#include<cstdio>
#include<cstring>

#define MAXX 50111
#define MAX 150111

int nx,p;
int i,j,k;
int x,y;
int ans;
bool flag;

int edge[MAXX],nxt[MAX],to[MAX],cnt;

int cx[MAXX],cy[MAXX];
int px[MAXX],py[MAXX];

int q[MAXX],*qf,*qb;

bool ag(int i)
{
    int j,k;
    for(k=edge[i];k;k=nxt[k])
        if(py[j=to[k]]==px[i]+1)
        {
            py[j]=0;
            if(cy[j]==-1 || ag(cy[j]))
            {
                cx[i]=j;
                cy[j]=i;
                return true;
            }
        }
    return false;
}

int main()
{
    scanf("%d %*d %d",&nx,&p);
    while(p--)
    {
        scanf("%d %d",&i,&j);
        nxt[++cnt]=edge[i];
        edge[i]=cnt;
        to[cnt]=j;
    }
    memset(cx,-1,sizeof cx);
    memset(cy,-1,sizeof cy);
    while(true)
    {
        memset(px,0,sizeof(px));
        memset(py,0,sizeof(py));
        qf=qb=q;
        flag=false;

        for(i=1;i<=nx;++i)
            if(cx[i]==-1)
                *qb++=i;
        while(qf!=qb)
            for(k=edge[i=*qf++];k;k=nxt[k])
                if(!py[j=to[k]])
                {
                    py[j]=px[i]+1;
                    if(cy[j]==-1)
                        flag=true;
                    else
                    {
                        px[cy[j]]=py[j]+1;
                        *qb++=cy[j];
                    }
                }
        if(!flag)
            break;
        for(i=1;i<=nx;++i)
            if(cx[i]==-1 && ag(i))
                ++ans;
    }
    printf("%d\n",ans);
    return 0;
}
