#include<cstdlib>
#include<ctime>
#include<cstring>

struct node
{
    node *ch[2];
    int sz,val,key;
    node(){memset(this,0,sizeof(node));}
    node(int a);
}*null;

node::node(int a):sz(1),val(a),key(rand()-1){ch[0]=ch[1]=null;}

class Treap
{
    inline void up(node *pos)
    {
        pos->sz=pos->ch[0]->sz+pos->ch[1]->sz+1;
    }
    inline void rot(node *&pos,int tp)
    {
        node *k(pos->ch[tp]);
        pos->ch[tp]=k->ch[tp^1];
        k->ch[tp^1]=pos;
        up(pos);
        up(k);
        pos=k;
    }

    void insert(node *&pos,int val)
    {
        if(pos!=null)
        {
            int t(val>=pos->val);
            insert(pos->ch[t],val);
            if(pos->ch[t]->key<pos->key)
                rot(pos,t);
            else
                up(pos);
            return;
        }
        pos=new node(val);
    }
    void rec(node *pos)
    {
        if(pos!=null)
        {
            rec(pos->ch[0]);
            rec(pos->ch[1]);
            delete pos;
        }
    }
    inline int sel(node *pos,int k)
    {
        while(pos->ch[0]->sz+1!=k)
            if(pos->ch[0]->sz>=k)
                pos=pos->ch[0];
            else
            {
                k-=pos->ch[0]->sz+1;
                pos=pos->ch[1];
            }
        return pos->val;
    }
    void del(node *&pos,int val)
    {
        if(pos!=null)
        {
            if(pos->val==val)
            {
                int t(pos->ch[1]->key<pos->ch[0]->key);
                if(pos->ch[t]==null)
                {
                    delete pos;
                    pos=null;
                    return;
                }
                rot(pos,t);
                del(pos->ch[t^1],val);
            }
            else
                del(pos->ch[val>pos->val],val);
            up(pos);
        }
    }
    public:
    node *rt;

    Treap():rt(null){}
    inline void insert(int val)
    {
        insert(rt,val);
    }
    inline void reset()
    {
        rec(rt);
        rt=null;
    }
    inline int sel(int k)
    {
        if(k<1 || k>rt->sz)
            return 0;
        return sel(rt,rt->sz+1-k);
    }
    inline void del(int val)
    {
        del(rt,val);
    }
    inline int size()
    {
        return rt->sz;
    }
}treap[MAXX];

init:
{
    srand(time(0));
    null=new node();
    null->val=0xc0c0c0c0;
    null->sz=0;
    null->key=RAND_MAX;
    null->ch[0]=null->ch[1]=null;
    for(i=0;i<MAXX;++i)
        treap[i].rt=null;
}
