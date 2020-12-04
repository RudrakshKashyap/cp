struct Matrix
{
    vector< vector<ll> > mat; // the contents of matrix as a 2D-vector

    int n;

    Matrix(vector< vector<ll> > a): mat(a), n(a.size()){}

    static Matrix identity_matrix(int n)
    {
        // Return I_n - the identity matrix of size n.
        // This function is static, because it creates a new Matrix instance
        vector< vector<ll> > I(n, vector<ll>(n, 0));
        for(int i = 0; i < n; i++)
            I[i][i] = 1;
        return I;
    }

    Matrix operator*(const Matrix &other) const
    {
        vector< vector<ll> > result(n, vector<ll>(n, 0));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    result[i][j] += mat[i][k] * other.mat[k][j];
                    result[i][j] %= mod;
                }
            }
        // Multiply matrices as usual, then return the result as the new Matrix
        return Matrix(result);
    }
};


Matrix exp(Matrix m, ll k)
{
    Matrix result = Matrix::identity_matrix(m.n);

    while(k > 0)
    {
        if(k & 1) result = result * m;
        m = m * m;
        k /= 2;
    }

    return result;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, k;
    cin >> n >> k;
    vector< VL > a(n, VL(n));
    rep(i,n) rep(j,n) cin >> a[i][j];
    Matrix m = Matrix(a);
    Matrix res = exp(m, k);
    ll ans = 0;
    rep(i, n) rep(j, n) ans += res.mat[i][j], ans %= mod;
    print(ans);

    return 0;
}
