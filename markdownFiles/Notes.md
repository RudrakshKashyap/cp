* Mid in `odd/even` array
    ```cpp
    /* n = 6(even)
    [           mid = (L+R)/2                                ]
    [L          L + (R-L)/2      R - (R-L)/2               R ] */
    [0  1           2         |      3               4     5 ]
    [0 ...        (n-1)/2     |  n/2 = (n+1)/2      ...   n-1]


    /* n = 5(odd)
    [                       mid = (L+R)/2                          ]
    [L              L + (R-L)/2 = R - (R-L)/2                    R ] */
    [0      1                   2                   3            4 ]
    [0     ...          (n-1)/2 = n/2             (n+1)/2       n-1]

    ```