## Binary Search

* https://codeforces.com/blog/entry/9901?#comment-153756
    ```cpp
    int l = -1, r = n, mid;
    while(r - l > 1) // bc if r - l = 1 then they are already boundary points
    {
        mid = l + (r - l)/2;
        if(condition) l = mid;  //l will always satisfy the condition
        else r = mid;   //r will never satisfy the condtion
    }

    //same as above just the l & r boundaries will be swapped in the end
    int l = 0, r = n-1, mid;
    while(l <= r)
    {
        mid = l + (r-l)/2;
        if(condition) l = mid + 1;  //l will never satisfy the condition
        else r = mid - 1;   //r will always satisfy the condition
    }
    ```

* **For Unimodal functions** - https://codeforces.com/blog/entry/53818?#comment-378377
    ```cpp
    // https://codeforces.com/blog/entry/11497

    int lo = 0, hi = n-1; //inclusive boundaries
    while(lo < hi) //loop ends when lo == hi == peak
    {    
        int mid = (lo + hi) >> 1;
        if(f(mid) < f(mid+1)) lo = mid + 1;   // lo = peak
        else hi = mid;                        // hi = peak
    }
    ```

## [Ternary Search](https://cp-algorithms.com/num_methods/ternary_search.html)

- https://www.youtube.com/watch?v=7h86n97naH4&t=344s
- https://www.youtube.com/watch?v=K1DIBa5UCMo
- https://codeforces.com/blog/entry/126959?#comment-1126785
    ```cpp
    // in case of integers , change every thing to ll and make eps = 5, 
    // then brute force the rest of the interval [l,r]
    db ternary_search(db l, db r){
        db eps = 1e-12;              //set the error limit here
        while(r - l > eps){
            db m1 = l + (r - l) / 3;
            db m2 = r - (r - l) / 3;
            if(f(m1) < f(m2)) l = m1;
            else r = m2;
        }
        return f(l);             //return the maximum of f(x) in [l, r]
    }
    ```
    `eps = 2` should also work in case for integers i guess
## [Golden Search](https://codeforces.com/blog/entry/11497?#comment-453387)
    