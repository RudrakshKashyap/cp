http://www.numbertheory.org/php/squareroot.html
By default, C++ standard streams (like cin, cout, cerr, etc.) are synchronized with C standard I/O functions (like printf, scanf, fprintf, etc.)
Mixing C and C++ I/O: After disabling synchronization with ios::sync_with_stdio(0);, avoid mixing C++ streams (cin, cout) with C I/O (printf, scanf), as it can lead to undefined behavior.
Manual Flushing: If cin is untied from cout, you may need to manually flush cout (e.g., using cout << flush;) to ensure output is displayed before input.
 By default, cout is not tied to any other stream, so cout.tie(0); line has no effect in most cases.
	
__builtin_popcount(x);
__builtin_popcountll(x);
__builtin_clz(x)
__builtin_ctz(x)
#define mod0 19260817233333333
#define mod1 2047483517
#define mod2 2147483647
cpp produce negitive modulo but python doesnt ((x % 5) + 5) % 5
setw(5) ____1 //mimimum width 5
setfill('f') ffff1
setprecision(10)
fixed	// 0.100
cout.setf(ios::fixed);
scientific // 1.000e-001
cout.precision(17);
round(x);
rotate(vec.begin(), vec.begin() + k, vec.end()); //cyclic left shift of k
int a = std::numeric_limits<int>::max();

string rev = string(str.rbegin(),str.rend());

fill_n((int*)dp, sizeof(dp)/sizeof(int), -(int)1e9);

//it also works for array,vectors ,list etc
string s="123"
do {
	cout<<s<<'\n';
} while(next_permutation(s.begin(),s.end()));	//only increasing permutation
while(prev_permutation(s.begin(),s.end()));
//123
//132
//213
.. till //321 after that it will return false

//https://www.geeksforgeeks.org/stdstringerase-in-cpp/
strchr(str,'a'); used for finding occurrence of a character in a string.
str = to_string(a);
a = stoi(str);

vec.size(); vec.capacity(); vec.reserve(1000);

queue<int>qu; print(qu);

priority_queue<int> q; min max heap
p/q mod m = (p*(q^m-2))%m
~(-1)=0
~just flips the bit, -1 in 2's comp is 111111...11111

x & (x - 1) == 0	True if x is a power of 2, False otherwise
x = x & (x - 1)	Removes the rightmost set bit
Used in	Power of 2 checks, counting set bits, optimizations
	

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


 Use of strlen() can be avoided by:
for (i=0; s[i]; i++)
{
}
loop breaks when the character array ends.


bitset size must be declare at compile time
bitset<5> x ("11000");
bitset<5> y = stoi("11000");
If you want to print, say, last 20 bits of a numbercout << bitset<20>(n) << "\n";
#include <bitset>
int main()
{
    std::string binary = std::bitset<8>(128).to_string(); //to binary
    std::cout<<binary<<"\n";

    unsigned long decimal = std::bitset<8>(binary).to_ulong();
    std::cout<<decimal<<"\n";
    return 0;
}


for(i = 1; i <= n; i++)
    for(j = 1; j <= m; j++)
        cout << a[i][j] << " \n"[j == m];
And here is the reason: " \n" is a char*, " \n"[0] is ' ' and " \n"[1] is '\n'.
	
ll ceil_div(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b != 0); } --> (a^b) // focus on their 32th bit,
// it's written to handel -ve numbers, ceil_div(-5, 2) will give -1 as ans without it
	

bool ok = any_of(a.begin(), a.end(), [](int x) { return x == 9; });
bool ok = all_of(a.begin(), a.end(), [](int x) { return x == 9; });
bool ok = none_of(a.begin(), a.end(), [](int x) { return x == 9; });
int cnt = count(a.begin(), a.end(), x); //count elements equal to x
int idx = find(a.begin(), a.end(), x) - a.begin(); //returns the first iterator that compares equal to val, will return a.end() if element not present
int count_x = count_if(v.begin(), v.end(), [](int a) { return (a >= x); });


class player : public Entity	//will enherit from enitity class, whatever is public in there
{
};


vector<int> res(min(v1.size(), v2.size());
auto lst = set_intersection(all(v1), all(v2), res.begin()); // linear time
cout << lst - res.begin();
		

int &a = b; //setting a address to b address, here type of a is an integer so basically we have 2 variable names for same meomory address
int *a = &b; // here the type of a is pointer
		
vector.pop_back()
vector.pop_front()
vector.erase(position)
// or
vector.erase(left,right) // *([left,right))*
remove(v.begin(),v.end(),val) // return itreator to the new end of vector
                
stl list c++ https://www.geeksforgeeks.org/list-cpp-stl/
                
                
                
A destructor is a special member function that is called when the lifetime of an object ends. The purpose of the destructor is to free the resources that the object may have acquired during its lifetime.
                
struct GpuTimer
{
      cudaEvent_t start;
      cudaEvent_t stop;
 
      GpuTimer()    //constructor
      {
            cudaEventCreate(&start);
            cudaEventCreate(&stop);
      }
 
      ~GpuTimer()       //destructor    --> helpful to free memory if declared using maloc
      {
            cudaEventDestroy(start);
            cudaEventDestroy(stop);
      }
};

Summary of static Keyword
Context			Behavior
Static Local Variable	Retains value between function calls; lifetime = program execution.
Static Global Variable	Scope limited to the file; lifetime = program execution.
Static Function		Scope limited to the file.
Static Data Member	Shared across all objects of the class; must be defined outside the class.
Static Member Function	Independent of objects; can only access static members.

By default, a global variable has external linkage, meaning it can be accessed from other files using the extern keyword.
// File1.cpp
int globalVar = 10; // Global variable

// File2.cpp
extern int globalVar; // Access globalVar from File1.cpp
but you can't do this thing with static
g++ File1.cpp File2.cpp main.cpp -o program //need to link the files when compiling for extern to work

The inline keyword in C++ is a hint to the compiler to replace a function call with the actual code of the function at the point where the function is called. This is known as inline expansion or inlining. The purpose of inlining is to reduce the overhead of function calls, especially for small, frequently called functions, which can improve performance.


Key Concepts:
Iterator Invalidation:
When you erase an element from a std::set, the iterator pointing to that element becomes invalid. Using an invalid iterator leads to undefined behavior.
To avoid this, you need to advance the iterator before erasing the element.
Post-increment (it++):
The post-increment operator (it++) returns the current value of it (before incrementing it) and then increments it to point to the next element.
This ensures that the iterator is advanced before the element is erased.
s.erase(it) return the iterator to the next valid element
