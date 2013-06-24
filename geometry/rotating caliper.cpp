//最远点对

inline double go()
{
    l=ans=0;
    for(i=0;i<n;++i)
    {
        tl=pnt[(i+1)%n]-pnt[i];
        while(abs(tl.cross(pnt[(l+1)%n]-pnt[i]))>=abs(tl.cross(pnt[l]-pnt[i])))
            l=(l+1)%n;
        ans=std::max(ans,std::max(dist(pnt[l],pnt[i]),dist(pnt[l],pnt[(i+1)%n])));
    }
    return ans;
}

//两凸包最近距离
double go()
{
    sq=sp=0;
    for(i=1;i<ch[1].size();++i)
        if(ch[1][sq]<ch[1][i])
            sq=i;
    tp=sp;
    tq=sq;
    ans=(ch[0][sp]-ch[1][sq]).len();
    do
    {
        a1=ch[0][sp];
        a2=ch[0][(sp+1)%ch[0].size()];
        b1=ch[1][sq];
        b2=ch[1][(sq+1)%ch[1].size()];
        tpv=b1-(b2-a1);
        tpv.x = b1.x - (b2.x - a1.x);
        tpv.y = b1.y - (b2.y - a1.y);
        len=(tpv-a1).cross(a2-a1);
        if(fabs(len)<eps)
        {
            ans=std::min(ans,p2l(a1,b1,b2));
            ans=std::min(ans,p2l(a2,b1,b2));
            ans=std::min(ans,p2l(b1,a1,a2));
            ans=std::min(ans,p2l(b2,a1,a2));
            sp=(sp+1)%ch[0].size();
            sq=(sq+1)%ch[1].size();
        }
        else
            if(len<-eps)
            {
                ans=std::min(ans,p2l(b1,a1,a2));
                sp=(sp+1)%ch[0].size();
            }
            else
            {
                ans=std::min(ans,p2l(a1,b1,b2));
                sq=(sq+1)%ch[1].size();
            }
    }while(tp!=sp || tq!=sq);
    return ans;
}

//外接矩形 by mzry
inline void solve()
{
    resa = resb = 1e100;
    double dis1,dis2;
    Point xp[4];
    Line l[4];
    int a,b,c,d;
    int sa,sb,sc,sd;
    a = b = c = d = 0;
    sa = sb = sc = sd = 0;
    Point va,vb,vc,vd;
    for (a = 0; a < n; a++)
    {
        va = Point(p[a],p[(a+1)%n]);
        vc = Point(-va.x,-va.y);
        vb = Point(-va.y,va.x);
        vd = Point(-vb.x,-vb.y);
        if (sb < sa)
        {
            b = a;
            sb = sa;
        }
        while (xmult(vb,Point(p[b],p[(b+1)%n])) < 0)
        {
            b = (b+1)%n;
            sb++;
        }
        if (sc < sb)
        {
            c = b;
            sc = sb;
        }
        while (xmult(vc,Point(p[c],p[(c+1)%n])) < 0)
        {
            c = (c+1)%n;
            sc++;
        }
        if (sd < sc)
        {
            d = c;
            sd = sc;
        }
        while (xmult(vd,Point(p[d],p[(d+1)%n])) < 0)
        {
            d = (d+1)%n;
            sd++;
        }

        //`卡在p[a],p[b],p[c],p[d]上`
        sa++;
    }
}

//合并凸包
给定凸多边形 P = { p(1) , ... , p(m) } 和 Q = { q(1) , ... , q(n) }，一个点对 (p(i), q(j)) 形成 P 和 Q 之间的桥当且仅当：

(p(i), q(j)) 形成一个并踵点对。
p(i-1), p(i+1), q(j-1), q(j+1) 都位于由 (p(i), q(j)) 组成的线的同一侧。 

假设多边形以标准形式给出并且顶点是以顺时针序排列， 算法如下：

1、分别计算 P 和 Q 拥有最大 y 坐标的顶点。 如果存在不止一个这样的点， 取 x 坐标最大的。
2、构造这些点的遂平切线， 以多边形处于其右侧为正方向（因此他们指向 x 轴正方向）。
3、同时顺时针旋转两条切线直到其中一条与边相交。 得到一个新的并踵点对 (p(i), q(j)) 。 对于平行边的情况， 得到三个并踵点对。
4、对于所有有效的并踵点对 (p(i), q(j))： 判定 p(i-1), p(i+1), q(j-1), q(j+1) 是否都位于连接点 (p(i), q(j)) 形成的线的同一侧。 如果是， 这个并踵点对就形成了一个桥， 并标记他。
5、重复执行步骤3和步骤4直到切线回到他们原来的位置。
6、所有可能的桥此时都已经确定了。 通过连续连接桥间对应的凸包链来构造合并凸包。 

上述的结论确定了算法的正确性。 运行时间受步骤1，5，6约束。 他们都为 O(N) 运行时间（N 是顶点总数）。 因此算法拥有现行的时间复杂度。

一个凸多边形间的桥实际上确定了另一个有用的概念：多边形间公切线。 同时， 桥也是计算凸多边形交的算法核心。

//临界切线
1、计算 P 上 y 坐标值最小的顶点（称为 yminP ） 和 Q 上 y 坐标值最大的顶点（称为 ymaxQ）。
2、为多边形在 yminP 和 ymaxQ 处构造两条切线 LP 和 LQ 使得他们对应的多边形位于他们的右侧。 此时 LP 和 LQ 拥有不同的方向， 并且 yminP 和 ymaxQ 成为了多边形间的一个对踵点对。
3、令 p(i)= yminP， q(j)= ymaxQ。 (p(i), q(j)) 构成了多边形间的一个对踵点对。 检测是否有 p(i-1),p(i+1) 在线 (p(i), q(j)) 的一侧， 并且 q(j-1),q(j+1) 在另一侧。 如果成立， (p(i), q(j)) 确定了一条CS线。
4、旋转这两条线， 直到其中一条和其对应的多边形的边重合。
5、一个新的对踵点对确定了。 如果两条线都与边重合， 总共三对对踵点对（原先的顶点和新的顶点的组合）需要考虑。 对于所有的对踵点对， 执行上面的测试。
6、重复执行步骤4和步骤5， 直到新的点对为(yminP,ymaxQ)。
7、输出CS线。 

//最小/最大周长/面积外接矩形
1、计算全部四个多边形的端点， 称之为 xminP， xmaxP， yminP， ymaxP。
2、通过四个点构造 P 的四条切线。 他们确定了两个“卡壳”集合。
3、如果一条（或两条）线与一条边重合， 那么计算由四条线决定的矩形的面积， 并且保存为当前最小值。 否则将当前最小值定义为无穷大。
4、顺时针旋转线直到其中一条和多边形的一条边重合。
5、计算新矩形的周长/面积， 并且和当前最小值比较。 如果小于当前最小值则更新， 并保存确定最小值的矩形信息。
6、重复步骤4和步骤5， 直到线旋转过的角度大于90度。
7、输出外接矩形的最小周长。 
