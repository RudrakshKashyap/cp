// https://www.youtube.com/watch?v=O7_w001f58c
// C++ program for implementation of Aho Corasick algorithm
// for string matching
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

typedef long long int ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int,int> PI;
typedef pair<ll,ll> PL;
typedef map<int,int> MI;
typedef vector<vector<int,int>> VII;
typedef pair<int,pair<int,int>> PII;

#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define mp make_pair
#define repa(i,a,n) for(ll i=a;i<n;i++)
#define rep(i,n) for(ll i=0;i<n;i++)
#define pera(i,a,n) for(ll i=a;i>=n;i--)
#define per(i,n) for(ll i=n;i>=0;i--)
#define all(x) (x).begin(),(x).end()
#define MS0(x) memset((x), 0, sizeof((x)))
#define MS1(x) memset((x), -1, sizeof((x)))
#define MEM(a, b) memset(a, b, sizeof(a))
#define SZ(x) ((ll)(x).size())
#define TIME    cerr << "\nTime elapsed: " << setprecision(5) <<1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
const int MAXS = 500,MAXC = 26;

int out[MAXS],f[MAXS],g[MAXS][MAXC];

int buildMatchingMachine(string arr[], int k)
{
	MS0(out);
    MS1(g);

	int states = 1;

    rep(i,k)
	{
		const string &word = arr[i];
		int cur = 0;

		rep(j,SZ(word))
		{
			int ch = word[j] - 'a';

			if (g[cur][ch] == -1)
				g[cur][ch] = states++;

			cur = g[cur][ch];
		}

		out[cur] |= (1 << i);
	}

    rep(ch,MAXC)
		if (g[0][ch] == -1)
			g[0][ch] = 0;

    MS1(f);

	queue<int> q;
	for (int ch = 0; ch < MAXC; ++ch)
	{
		if (g[0][ch] != 0)
		{
			f[g[0][ch]] = 0;
			q.push(g[0][ch]);
		}
	}

	while (q.size())
	{
		int state = q.front();
		q.pop();

		for (int ch = 0; ch <= MAXC; ++ch)
		{
			if (g[state][ch] != -1)
			{
				int fail = f[state];
				while (g[fail][ch] == -1)
					fail = f[fail];

				fail = g[fail][ch];
				f[g[state][ch]] = fail;

				out[g[state][ch]] |= out[fail];
				q.push(g[state][ch]);
			}
		}
	}

	return states;
}

int findNextState(int cur, char nextInput)
{
	int ch = nextInput - 'a';

	// If goto is not defined, use fail function
	while (g[cur][ch] == -1)
		cur = f[cur];

	return g[cur][ch];
}

void searchWords(string arr[], int k, string text)
{
	buildMatchingMachine(arr, k);

	int cur = 0;

	rep(i,SZ(text))
	{
		cur = findNextState(cur, text[i]);

		// If match not found, move to next state
		if (out[cur] == 0)
			continue;

		// Match found, print all matching words of arr[]
		// using output function.
		rep(j,k)
		{
			if (out[cur] & (1 << j))
			{
				cout << "Word " << arr[j] << " appears from " << i - arr[j].size() + 1 << " to " << i << endl;
			}
		}
	}
}

// Driver program to test above
int main()
{
	string arr[] = {"he", "she", "hers", "his"};
	string text = "ahishers";
	int k = sizeof(arr)/sizeof(arr[0]);

	searchWords(arr, k, text);

	return 0;
}
