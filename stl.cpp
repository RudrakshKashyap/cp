__builtin_popcount(x);
__builtin_popcountll(x);
__builtin_clz(x)
__builtin_ctz(x)
cpp produce negitive modulo but python doesnt ((x % 5) + 5) % 5
setw(5) ____1 //mimimum width 5
setfill('f') ffff1
setprecision(10)
fixed	// 0.100
scientific // 1.000e-001
cout.precision(17);
round(x);
rotate(vec.begin(), vec.begin() + k, vec.end()); //cyclic left shift of k
int a = std::numeric_limits<int>::max();
priority_queue<int,vector<int>,greater<int>> pq ; min heap
If you want to print, say, last 20 bits of a numbercout << bitset<20>(n) << "\n";
string rev = string(str.rbegin(),str.rend());

//it also works for array,vectors ,list etc
string s="123"
do {
	cout<<s<<'\n';
} while(next_permutation(s.begin(),s.end()));
//123
//132
//213
.. till //321 after that it will return false


strchr(str,'a'); used for finding occurrence of a character in a string.
str = to_string(a);
a = stoi(str);
it=itreatrator of map---- it->first,it->second
vec.size(); vec.capacity(); vec.reserve(1000);
deque<int> dq; dq.push_front(5);
queue<int>qu; print(qu);
stack<int> stk;
priority_queue<int> q; min max heap
p/q mod m = (p*(q^m-2))%m
~(-1)=0


	

v = { 1, 1, 3, 3, 3, 10, 1, 3, 3, 7, 7, 8 }
vec.resize(unique(all(vec)) - vec.begin());
1 3 10 1 3 7 8 //3 apper twice thats why sort before resizing

// Using copy_n() to copy contents
    copy_n(ar, 6, ar1);

// Initailising starting value as 100
    int st = 100;

    std::iota(numbers, numbers + 10, st);
Elements are : 100 101 102 103 104 105 106 107 108 109

// A quick way to swap a and b
a ^= b;
b ^= a;
a ^= b;

if (num & 1)
   cout << "ODD";
else
   cout << "EVEN";

 Use of strlen() can be avoided by:
for (i=0; s[i]; i++)
{
}
loop breaks when the character array ends.