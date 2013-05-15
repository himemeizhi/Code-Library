inline bool cmp(const Point& a,const Point& b)
{
    if (a.y*b.y <= 0)
    {
        if (a.y > 0 || b.y > 0) 
            return a.y < b.y;
        if (a.y == 0 && b.y == 0)   
            return a.x < b.x;
    }
    return a.cross(b) > 0;
}
