//数组保存在val[0][1],val[0][n]的双闭区间中

template<class Tp>class DT
{
    public:
        int n;
        Tp val[20][MAXX],sorted[MAXX];
        inline void make()
        {
            std::sort(sorted+1,sorted+1+n);
            make(1,1,n,0);
        }
        inline int query(const int &l,const int &r,const int &k)
        {
            return query(1,1,n,l,r,k,0);
        }
    private:
        int toleft[20][MAXX],mid[MAXX<<2];
        // toleft: 有多少过数分到左边去了
        void make(const int &id,const int &l,const int &r,const int &d)
        {
            if(l!=r)
            {
                mid[id]=(l+r)>>1;
                int lsame(mid[id]-l+1),i;
                for(i=l;i<=r;++i)
                    if(val[d][i]<sorted[mid[id]])
                        --lsame;
                int lpos(l),rpos(mid[id]+1),same(0);
                for(i=l;i<=r;++i)
                {
                    if(i==l)
                        toleft[d][i]=0;
                    else
                        toleft[d][i]=toleft[d][i-1];
                    if(val[d][i]<sorted[mid[id]])
                    {
                        ++toleft[d][i];
                        val[d+1][lpos++]=val[d][i];
                    }
                    else
                        if(val[d][i]>sorted[mid[id]])
                            val[d+1][rpos++]=val[d][i];
                        else
                            if(same<lsame)
                            {
                                ++same;
                                ++toleft[d][i];
                                val[d+1][lpos++]=val[d][i];
                            }
                            else
                                val[d+1][rpos++]=val[d][i];
                }
                make(id<<1,l,mid[id],d+1);
                make(id<<1|1,mid[id]+1,r,d+1);
            }
        }
        int query(const int &id,const int &ll,const int &rr,const int &l,const int &r,const int &k,const int &d)
        {
            if(l==r)
                return val[d][l];
            int s,ss;
            if(l==ll)
            {
                s=toleft[d][r];
                ss=0;
            }
            else
            {
                s=toleft[d][r]-toleft[d][l-1];
                ss=toleft[d][l-1];
            }
            if(s>=k)
            {
                int newl(ll+ss),newr(ll+ss+s-1);
                return query(id<<1,ll,mid[id],newl,newr,k,d+1);
            }
            int bb(l-ll-ss),b(r-l+1-s),newl(mid[id]+bb+1),newr(mid[id]+bb+b);
            return query(id<<1|1,mid[id]+1,rr,newl,newr,k-s,d+1);
        }
};
