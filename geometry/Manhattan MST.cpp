#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
const int srange = 10000000;      //坐标范围
const int ra = 131072;     //线段树常量
int c[ ra * 2 ], d[ ra * 2 ];     //线段树
int a[ 100000 ], b[ 100000 ];   //排序临时变量
int order[ 400000 ], torder[ 100000 ]; //排序结果
int Index[ 100000 ];     //排序结果取反（为了在常数时间内取得某数的位置）
int road[ 100000 ][ 8 ];    //每个点连接出去的8条边
int y[ 100000 ], x[ 100000 ];     //点坐标
int n;         //点个数

int swap( int &a, int &b )    //交换两个数
{
    int t = a; a = b; b = t;
}

int insert( int a, int b, int i ) //向线段树中插入一个数
{
    a += ra;
    while ( a != 0 )
    {
        if ( c[ a ] > b )
        {
            c[ a ] = b;
            d[ a ] = i;
        }
        else break;
        a >>= 1;
    }
}

int find( int a )      //从c[0..a]中找最小的数，线段树查询
{
    a += ra;
    int ret = d[ a ], max = c[ a ];
    while ( a > 1 )
    {
        if ( ( a & 1 ) == 1 )
            if ( c[ --a ] < max )
            {
                max = c[ a ];
                ret = d[ a ];
            }
        a >>= 1;
    }
    return ret;
}

int ta[ 65536 ], tb[ 100000 ];    //基数排序临时变量

int radixsort( int *p )     //基数排序，以p为基准
{
    memset( ta, 0, sizeof( ta ) );
    for (int i = 0; i < n; i++ ) ta[ p[ i ] & 0xffff ]++;
    for (int i = 0; i < 65535; i++ ) ta[ i + 1 ] += ta[ i ];
    for (int i = n - 1; i >= 0; i-- ) tb[ --ta[ p[ order[ i ] ] & 0xffff ] ] = order[ i ];
    memmove( order, tb, n * sizeof( int ) );
    memset( ta, 0, sizeof( ta ) );
    for (int i = 0; i < n; i++ ) ta[ p[ i ] >> 16 ]++;
    for (int i = 0; i < 65535; i++ ) ta[ i + 1 ] += ta[ i ];
    for (int i = n - 1; i >= 0; i-- ) tb[ --ta[ p[ order[ i ] ] >> 16 ] ] = order[ i ];
    memmove( order, tb, n * sizeof( int ) );
}

int work( int ii )                //求每个点在一个方向上最近的点
{
    for (int i = 0; i < n; i++ ) //排序前的准备工作
    {
        a[ i ] = y[ i ] - x[ i ] + srange;
        b[ i ] = srange - y[ i ];
        order[ i ] = i;
    }
    radixsort( b );      //排序
    radixsort( a );
    for (int i = 0; i < n; i++ )
    {
        torder[ i ] = order[ i ];
        order[ i ] = i;
    }
    radixsort( a );      //为线段树而做的排序
    radixsort( b );
    for (int i = 0; i < n; i++ )
    {
        Index[ order[ i ] ] = i; //order取反，求Index
    }
    for (int i = 1; i < ra + n; i++ ) c[ i ] = 0x7fffffff; //线段树初始化
    memset( d, 0xff, sizeof( d ) );
    for (int i = 0; i < n; i++ ) //线段树插入删除调用
    {
        int tt = torder[ i ];
        road[ tt ][ ii ] = find( Index[ tt ] );
        insert( Index[ tt ], y[ tt ] + x[ tt ], tt );
    }
}

int distanc( int a, int b )       //求两点的距离，之所以少一个e是因为编译器不让使用distance作为函数名
{
    return abs( x[ a ] - x[ b ] ) + abs( y[ a ] - y[ b ] );
}

int ttb[ 400000 ];      //边排序的临时变量
int rx[ 400000 ], ry[ 400000 ], rd[ 400000 ]; //边的存储
int rr = 0;

int radixsort_2( int *p )    //还是基数排序，copy+paste的产物
{
    memset( ta, 0, sizeof( ta ) );
    for (int i = 0; i < rr; i++ ) ta[ p[ i ] & 0xffff ]++;
    for (int i = 0; i < 65535; i++ ) ta[ i + 1 ] += ta[ i ];
    for (int i = rr - 1; i >= 0; i-- ) ttb[ --ta[ p[ order[ i ] ] & 0xffff ] ] = order[ i ];
    memmove( order, ttb, rr * sizeof( int ) );
    memset( ta, 0, sizeof( ta ) );
    for (int i = 0; i < rr; i++ ) ta[ p[ i ] >> 16 ]++;
    for (int i = 0; i < 65535; i++ ) ta[ i + 1 ] += ta[ i ];
    for (int i = rr - 1; i >= 0; i-- ) ttb[ --ta[ p[ order[ i ] ] >> 16 ] ] = order[ i ];
    memmove( order, ttb, rr * sizeof( int ) );
}

int father[ 100000 ], rank[ 100000 ];    //并查集
int findfather( int x )                  //并查集寻找代表元
{
    if ( father[ x ] != -1 )
        return ( father[ x ] = findfather( father[ x ] ) );
    else return x;
}

long long kruskal()                      //最小生成树
{
    rr = 0;
    int tot = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++ )         //得到边表
    {
        for (int j = 0; j < 4; j++ )
        {
            if ( road[ i ][ j ] != -1 )
            {
                rx[ rr ] = i;
                ry[ rr ] = road[ i ][ j ];
                rd[ rr++ ] = distanc( i, road[ i ][ j ] );
            }
        }
    }
    for (int i = 0; i < rr; i++ ) order[ i ] = i; //排序
    radixsort_2( rd );
    memset( father, 0xff, sizeof( father ) ); //并查集初始化
    memset( rank, 0, sizeof( rank ) );
    for (int i = 0; i < rr; i++ )     //kruskal最小生成树标准算法
    {
        if ( tot == n - 1 ) break;
        int t = order[ i ];
        int x = findfather( rx[ t ] ), y = findfather( ry[ t ] );
        if ( x != y )
        {
            ans += rd[ t ];
            tot++;
            int &rkx = rank[ x ], &rky = rank[ y ];
            if ( rkx > rky ) father[ y ] = x;
            else
            {
                father[ x ] = y;
                if ( rkx == rky ) rky++;
            }
        }
    }
    return ans;
}

int casenum = 0;

int main()
{
    while ( cin >> n )
    {
        if ( n == 0 ) break;
        for (int i = 0; i < n; i++ )
            scanf( "%d %d", &x[ i ], &y[ i ] );
        memset( road, 0xff, sizeof( road ) );
        for (int i = 0; i < 4; i++ )             //为了减少编程复杂度，work()函数只写了一种，其他情况用转换坐标的方式类似处理
        {           //为了降低算法复杂度，只求出4个方向的边
            if ( i == 2 )
            {
                for (int j = 0; j < n; j++ ) swap( x[ j ], y[ j ] );
            }
            if ( ( i & 1 ) == 1 )
            {
                for (int j = 0; j < n; j++ ) x[ j ] = srange - x[ j ];
            }
            work( i );
        }
        printf( "Case %d: Total Weight = ", ++casenum );
        cout << kruskal() << endl;
    }
    return 0;
}
