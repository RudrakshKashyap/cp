const int k = 16;   //maxlog floor
const int N = 1e5;  //maxn

int n;
long long table[N][k + 1]; // k + 1 because we need to access table[r][MAXLOG]
int Arr[N];
int numlog[N];


void build()
{
    numlog[1] = 0;
    for (int i = 2; i <= n; i++)
        numlog[i] = numlog[i / 2] + 1;

    // build Sparse Table
    for(int i = 0; i < n; i++)
        table[i][0] = Arr[i];
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

long long query(int L, int R) 
{ 
    // boundaries of next query, 0-indexed 
    long long answer = 0; 
    for (int j = numlog[n]; j >= 0; j--) { 
        if (L + (1 << j) - 1 <= R) { 
            answer = answer + table[L][j]; 
  
            // instead of having L', we 
            // increment L directly 
            L += 1 << j; 
        } 
    } 
    return answer; 
} 
