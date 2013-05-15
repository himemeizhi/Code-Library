//演算法笔记1

struct Point {double x, y;} p[10], t[10];
bool cmpx(const Point& i, const Point& j) {return i.x < j.x;}
bool cmpy(const Point& i, const Point& j) {return i.y < j.y;}

double DnC(int L, int R)
{
    if (L >= R) return 1e9; // 沒有點、只有一個點。
    
    /* Divide：把所有點分成左右兩側，點數盡量一樣多。 */
    
    int M = (L + R) / 2;
    
    /* Conquer：左側、右側分別遞迴求解。 */
    
    double d = min(DnC(L,M), DnC(M+1,R));
    //  if (d == 0.0) return d; // 提早結束
    
    /* Merge：尋找靠近中線的點，並依Y座標排序。O(NlogN)。 */
    
    int N = 0;  // 靠近中線的點數目
    for (int i=M;   i>=L && p[M].x - p[i].x < d; --i) t[N++] = p[i];
    for (int i=M+1; i<=R && p[i].x - p[M].x < d; ++i) t[N++] = p[i];
    sort(t, t+N, cmpy); // Quicksort O(NlogN)
    
    /* Merge：尋找橫跨兩側的最近點對。O(N)。 */
    
    for (int i=0; i<N-1; ++i)
        for (int j=1; j<=2 && i+j<N; ++j)
            d = min(d, distance(t[i], t[i+j]));
    
    return d;
}

double closest_pair()
{
    sort(p, p+10, cmpx);
    return DnC(0, N-1);
}


//演算法笔记2

struct Point {double x, y;} p[10], t[10];
bool cmpx(const Point& i, const Point& j) {return i.x < j.x;}
bool cmpy(const Point& i, const Point& j) {return i.y < j.y;}

double DnC(int L, int R)
{
    if (L >= R) return 1e9; // 沒有點、只有一個點。
    
    /* Divide：把所有點分成左右兩側，點數盡量一樣多。 */
    
    int M = (L + R) / 2;
    
    // 先把中線的X座標記起來，因為待會重新排序之後會跑掉。
    double x = p[M].x;
    
    /* Conquer：左側、右側分別遞迴求解。 */
    
    // 遞迴求解，並且依照Y座標重新排序。
    double d = min(DnC(L,M), DnC(M+1,R));
    //  if (d == 0.0) return d; // 提早結束
    
    /* Merge：尋找靠近中線的點，並依Y座標排序。O(N)。 */
    
    // 尋找靠近中線的點，先找左側。各點已照Y座標排序了。
    int N = 0;  // 靠近中線的點數目
    for (int i=0; i<=M; ++i)
        if (x - p[i].x < d)
            t[N++] = p[i];
    
    // 尋找靠近中線的點，再找右側。各點已照Y座標排序了。
    int P = N;  // P為分隔位置
    for (int i=M+1; i<=R; ++i)
        if (p[i].x - x < d)
            t[N++] = p[i];
    
    // 以Y座標排序。使用Merge Sort方式，合併已排序的兩陣列。
    inplace_merge(t, t+P, t+N, cmpy);
    
    /* Merge：尋找橫跨兩側的最近點對。O(N)。 */
    
    for (int i=0; i<N; ++i)
        for (int j=1; j<=2 && i+j<N; ++j)
            d = min(d, distance(t[i], t[i+j]));
    
    /* Merge：重新以Y座標排序所有點。O(N)。 */
    
    // 如此一來，更大的子問題就可以直接使用Merge Sort。
    inplace_merge(p+L, p+M+1, p+R+1, cmpy);
    
    return d;
}

double closest_pair()
{
    sort(p, p+10, cmpx);
    return DnC(0, N-1);
}

//mzry
//分治
double calc_dis(Point &a ,Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
//别忘了排序
bool operator<(const Point &a ,const Point &b) {
	if(a.y != b.y) return a.x < b.x;
	return a.x < b.x;
}
double Gao(int l ,int r ,Point pnts[]) {
	double ret = inf;
	if(l == r) return ret;
	if(l+1 ==r) {
		ret = min(calc_dis(pnts[l],pnts[l+1]) ,ret);
		return ret;
	}
	if(l+2 ==r) {
		ret = min(calc_dis(pnts[l],pnts[l+1]) ,ret);
		ret = min(calc_dis(pnts[l],pnts[l+2]) ,ret);
		ret = min(calc_dis(pnts[l+1],pnts[l+2]) ,ret);
		return ret;
	}
    
	int mid = l+r>>1;
	ret = min (ret ,Gao(l ,mid,pnts));
	ret = min (ret , Gao(mid+1, r,pnts));
    
	for(int c = l ; c<=r; c++)
		for(int d = c+1; d <=c+7 && d<=r; d++) {
			ret = min(ret , calc_dis(pnts[c],pnts[d]));
		}
	return ret;
}

//增量
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#define Point pair<double,double>
using namespace std;

const int step[9][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
int n,x,y,nx,ny;
map<pair<int,int>,vector<Point > > g;
vector<Point > tmp;
Point p[20000];
double tx,ty,ans,nowans;
vector<Point >::iterator it,op,ed;
pair<int,int> gird;
bool flag;

double Dis(Point p0,Point p1)
{
	return sqrt((p0.first-p1.first)*(p0.first-p1.first)+
				(p0.second-p1.second)*(p0.second-p1.second));
}

double CalcDis(Point p0,Point p1,Point p2)
{
	return Dis(p0,p1)+Dis(p0,p2)+Dis(p1,p2);
}

void build(int n,double w)
{
	g.clear();
	for (int i = 0;i < n;i++)
		g[make_pair((int)floor(p[i].first/w),(int)floor(p[i].second/w))].push_back(p[i]);
}

int main()
{
	int t;
	scanf("%d",&t);
	for (int ft = 1;ft <= t;ft++)
	{
		scanf("%d",&n);
		for (int i = 0;i < n;i++)
		{
			scanf("%lf%lf",&tx,&ty);
			p[i] = make_pair(tx,ty);
		}
		random_shuffle(p,p+n);
		ans = CalcDis(p[0],p[1],p[2]);
		build(3,ans/2.0);
		for (int i = 3;i < n;i++)
		{
			x = (int)floor(2.0*p[i].first/ans);
			y = (int)floor(2.0*p[i].second/ans);
			tmp.clear();
			for (int k = 0;k < 9;k++)
			{
				nx = x+step[k][0];
				ny = y+step[k][1];
				gird = make_pair(nx,ny);
				if (g.find(gird) != g.end())
				{
					op = g[gird].begin();
					ed = g[gird].end();
					for (it = op;it != ed;it++)
						tmp.push_back(*it);
				}
			}
			flag = false;
			for (int j = 0;j < tmp.size();j++)
				for (int k = j+1;k < tmp.size();k++)
				{
					nowans = CalcDis(p[i],tmp[j],tmp[k]);
					if (nowans < ans)
					{
						ans = nowans;
						flag = true;
					}
				}
			if (flag == true)
				build(i+1,ans/2.0);
			else
				g[make_pair((int)floor(2.0*p[i].first/ans),(int)floor(2.0*p[i].second/ans))].push_back(p[i]);
		}
		printf("%.3f\n",ans);
	}
}
