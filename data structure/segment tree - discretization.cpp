std::map<double,short>map;  //正向hash
std::map<double,short>::iterator it;
double rmap[inf];  //逆向hash

short mid[MAX],cnt[MAX];
double len[MAX];

void make(const short &id,const short &l,const short &r)
{
    mid[id]=(l+r)>>1;
    if(l!=r)
    {
        make(id<<1,l,mid[id]);
        make(id<<1|1,mid[id]+1,r);
    }
}

void update(const short &id,const short &ll,const short &rr,const short &l,const short &r,const char &val)
{
    if(ll==l && rr==r)
    {
        cnt[id]+=val;
        if(cnt[id])
            len[id]=rmap[r]-rmap[l-1];
        else
            if(l!=r)
                len[id]=len[id<<1]+len[id<<1|1];
            else
                len[id]=0;
        return;
    }
    if(mid[id]>=r)
        update(id<<1,ll,mid[id],l,r,val);
    else
        if(mid[id]<l)
            update(id<<1|1,mid[id]+1,rr,l,r,val);
        else
        {
            update(id<<1,ll,mid[id],l,mid[id],val);
            update(id<<1|1,mid[id]+1,rr,mid[id]+1,r,val);
        }
    if(!cnt[id])
        len[id]=len[id<<1]+len[id<<1|1];
}

int main()
{
    n<<=1;
    map.clear();
    for(i=0;i<n;++i)
    {
        scanf("%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&d);
        if(x1>x2)
            std::swap(x1,x2);
        if(y1>y2)
            std::swap(y1,y2);
        sum+=(x2-x1)*(y2-y1)*d;
        ln[i].l=x1;
        ln[i].r=x2;
        ln[i].h=y1;
        ln[i].up=1;
        ln[++i].l=x1;
        ln[i].r=x2;
        ln[i].h=y2;
        ln[i].up=-1;
        map[x1]=1;
        map[x2]=1;
    }
    k=1;
    for(it=map.begin();it!=map.end();++it,++k) //离散化
    {
        it->second=k;
        rmap[k]=it->first;
    }
    std::sort(ln,ln+n);
    update(1,1,inf,map[ln[0].l]+1,map[ln[0].r],ln[0].up);
    for(i=1;i<n;++i)
    {
        //依次铺线，len[1]为当前状态总长
        //ln[i].h-ln[i-1].h 为两条线直接的高度差
        update(1,1,inf,map[ln[i].l]+1,map[ln[i].r],ln[i].up);
    }
}
