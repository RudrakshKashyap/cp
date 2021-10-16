//https://codeforces.com/blog/entry/9901?#comment-153756
Well, imagine you an array [0..n - 1] and let us have an invariant:
some function F which returns True for every a[i] as an argument for any i from [0..k] and False for every a[j] for j from [k + 1..n - 1].
Then my binary search which actually finds the border between these two parts of the array looks the following way:
int l = -1, r = n, mid;
while(r - l > 1)
{
    mid = l + (r - l)/2;
    if(condition) l = mid;
    else r = mid;
}
here l always satisfy condition while r does not
You can easily prove that l = k and r = k + 1 by the end of the while loop. In this case no worries about whether to increase m by 1 or not.



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
