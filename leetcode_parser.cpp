vector<vector<int>> vec2d(string s)
{
    // s = [[1,2,3],[44,5,62]]
    cin >> s;
    vector<string> v;
    vector<vector<int>> mat;
    stringstream ss(s);
    while(ss.good())
    {
        string sub;
        getline(ss,sub,']');
        if(sub.size())
        {
            v.push_back(sub.substr(2,sub.size()-2));
            mat.push_back(vector<int>());
        }
    }
    
    int n = mat.size();
    for(int i = 0; i < n; i++)
    {
        stringstream row(v[i]);
        while(row.good())
        {
            string num;
            getline(row, num, ',');
            if(num.size()) mat[i].push_back(stoi(num));
        }
    }
    
    int m = mat[0].size();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cout << mat[i][j] << " \n"[j == m-1];

    return mat;
}
