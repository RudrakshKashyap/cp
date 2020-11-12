const int k = 16;   //maxlog floor
const int maxn = 1e5;  //maxn

int n;  //size of arr
long long table[maxn][k + 1]; // k + 1 because we need to access table[r][MAXLOG]
int arr[maxn];
int numlog[maxn+1];


void build()
{
    numlog[1] = 0;
    for (int i = 2; i <= n; i++)
        numlog[i] = numlog[i / 2] + 1;

    // build Sparse Table
    for(int i = 0; i < n; i++)
        table[i][0] = arr[i];
    for(int j = 1; j <= numlog[n]; j++)
    {
        for(int i = 0; i <= n - (1 << j); i++)
            table[i][j] = table[i][j - 1] + table[i + (1 << (j - 1))][j - 1];
    }
}

int getMax(int l, int r)    //these l and r are inclusive [l,r]
{
    int curlog = numlog[r - l + 1];
    return max(table[l][curlog], table[r - (1 << curlog) + 1][curlog]);
}

long long query(int l, int r) 
{ 
    // boundaries of next query, 0-indexed 
    long long answer = 0; 
    for (int j = numlog[n]; j >= 0; j--) { 
        if (l + (1 << j) - 1 <= r) { 
            answer = answer + table[l][j]; 
  
            // instead of having L', we 
            // increment L directly 
            l += 1 << j; 
        } 
    } 
    return answer; 
} 
