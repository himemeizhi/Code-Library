/*
射线法, 多边形可以是凸的或凹的
poly的顶点数目要大于等于3
返回值为：
0  -- 点在poly内
1  -- 点在poly边界上
2  -- 点在poly外
*/

int inPoly(pv p,pv poly[], int n)
{
	int i, count;
	Line ray, side;
    
	count = 0;
	ray.s	= p;
	ray.e.y  = p.y;
	ray.e.x  = -1;  //-INF，注意取值防止越界！
    
	for (i = 0; i < n; i++)
	{
		side.s = poly[i];
		side.e = poly[(i+1)%n];
        
		if(OnSeg(p, side))
			return 1;
        
		// 如果side平行x轴则不作考虑
		if (side.s.y == side.e.y)
			continue;

        if (OnSeg(side.s, ray))
        {
            if (side.s.y > side.e.y) 
                count++;
        }
        else
            if (OnSeg(side.e, ray))
            {
                if (side.e.y > side.s.y) 
                    count++;
            }
            else
                if (inter(ray, side))
                    count++;
	}
	return ((count % 2 == 1) ? 0 : 2);
}
