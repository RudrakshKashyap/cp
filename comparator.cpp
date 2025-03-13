std::priority_queue does not support iteration because it is designed to provide access only to the top element.

////custom comp for pq

bool Compare(Node a, Node b);
                                             //passing the type         //passing the actual function
std::priority_queue<Node, std::vector<Node>, decltype(&Compare)> openSet(Compare);

struct My_less
{
    auto operator()( int const a, int const b ) const
        -> bool
    { return a < b; }
};

std::priority_queue< int, std::vector<int>, My_less > pq;

My_less is defined as a struct with an overloaded operator(). 
This makes it a function object (or functor), which is a callable object that can be used like a function. 
The priority_queue template expects the Compare parameter to be a type that can be called like a function, 
and a struct or class with an overloaded operator() satisfies this requirement.


0 1 2 3 4 ----> will be arraage like(from bottom to top in priority queue)
				      4		
				  2     3
				0   1






//can use struct also
// Custom comparator class
class comp {
public:
    int* b; // Pointer to the external array
    comp(vector<int>& a) {
        b = &a[0]; // Initialize the pointer to the first element of the array
    }
    bool operator()(ar o1, ar o2) {
        // Compare based on the custom rule
        return b[o1[0]] * b[o2[1]] > b[o2[0]] * b[o1[1]];
    }
};

int main() {
    // External array
    vector<int> arr = {2, 3, 5};

    // Priority queue with custom comparator
    priority_queue<ar, vector<ar>, comp> pq(arr);

    // Insert pairs into the queue
    pq.push({0, 1});
    pq.push({1, 2});
    pq.push({0, 2});

    // Process the queue
    while (!pq.empty()) {
        ar top = pq.top();
        pq.pop();
        cout << "{" << top[0] << ", " << top[1] << "} ";
    }

    return 0;
}
output->{0, 2} {1, 2} {0, 1}



struct customCompFunctor {
    bool operator()(const string& a, const string& b) const {
        return a.length() < b.length(); // Sort by string length in ascending order
    }
};
//for a vector
sort(words.begin(), words.end(), customCompFunctor());//it takes the instance rather than taking the type, customCompFunctor() will create an instance







vector<int> v1;
/// compares the subarray of array v1 starting at index i1 with array v2
// i1 is the index of suffix array and v2 is the pattern
bool comp(int i1, vector<int> v2) {
	int len1 = v1.size() - i1;
	int len2 = v2.size();
	int len = min(len1, len2);
	for (int i = 0 ; i < len ; i++)
		if (v1[i1 + i] != v2[i]) {
			return v1[i1 + i] < v2[i];
		}
	if (len1 != len2) return len1 < len2;
	return false;
}

int findNumberOfOccurences(vector<int> v, vector<int> &pattern) {
    if (pattern.size() == 0) return v.size() + 1;

	v.push_back(IntMinVal);
    // pattern.pb(IntMinVal);
	vector<int> suffixArray = sa(v);
    // rep(i,SZ(pattern)) cout<<pattern[i]<<' ';
    // watch('f');

	v1 = v;

	vector<int>::iterator it1 = lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);
    // cout<<*(it1-2)<<'\n';
    // watch(pattern.back());
	pattern.back()++;
	vector<int>::iterator it2 = lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);

	return it2 - it1;
}
