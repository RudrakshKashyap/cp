int l=0,r=n-1;
while(l<=r)
{
    mid= l + (r-l)/2;
    if(condition) l=mid+1;
    else r=mid-1;
}
return l;
