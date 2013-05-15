inline void make(int *z,char *buf)
{
    int i,j,l,r;
    l=0;
    r=1;
    z[0]=strlen(buf);
    for(i=1;i<z[0];++i)
        if(r<=i || z[i-l]>=r-i)
        {
            j=std::max(i,r);
            while(j<z[0] && buf[j]==buf[j-i])
                ++j;
            z[i]=j-i;
            if(i<j)
            {
                l=i;
                r=j;
            }
        }
        else
            z[i]=z[i-l];
}

for(i=1;i<len && i+z[i]<len;++i); //i=可能最小循环节长度
