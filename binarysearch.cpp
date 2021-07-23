int l=0,r=n-1;
while(l<=r)
{
    mid= l + (r-l)/2;
    if(condition) l=mid+1;
    else r=mid-1;
}
return l;

//nice ternary search videos
https://www.youtube.com/watch?v=7h86n97naH4&t=344s
https://www.youtube.com/watch?v=K1DIBa5UCMo

https://codeforces.com/contest/1538/submission/119002356
auto evaluate = [&](int64_t ab) -> long double {
    long double x = X - ab * A;
    long double y = Y - ab * B;
    return ab + min(x / B, y / A);
};

int64_t low = 0, high = min(X / A, Y / B);

while (low < high) {
    int64_t mid = low + (high - low) / 2;

    if (evaluate(mid) > evaluate(mid + 1))
        high = mid;
    else
        low = mid + 1;
}

// ans = low
