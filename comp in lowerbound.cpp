
// vector<int> v1;
// /// compares the subarray of array v1 starting at index i1 with array v2
// // i1 is the index of suffix array and v2 is the pattern
// bool comp(int i1, vector<int> v2) {
// 	int len1 = v1.size() - i1;
// 	int len2 = v2.size();
// 	int len = min(len1, len2);
// 	for (int i = 0 ; i < len ; i++)
// 		if (v1[i1 + i] != v2[i]) {
// 			return v1[i1 + i] < v2[i];
// 		}
// 	if (len1 != len2) return len1 < len2;
// 	return false;
// }
//
// int findNumberOfOccurences(vector<int> v, vector<int> &pattern) {
//     if (pattern.size() == 0) return v.size() + 1;
//
// 	v.push_back(IntMinVal);
//     // pattern.pb(IntMinVal);
// 	vector<int> suffixArray = sa(v);
//     // rep(i,SZ(pattern)) cout<<pattern[i]<<' ';
//     // watch('f');
//
// 	v1 = v;
//
// 	vector<int>::iterator it1 = lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);
//     // cout<<*(it1-2)<<'\n';
//     // watch(pattern.back());
// 	pattern.back()++;
// 	vector<int>::iterator it2 = lower_bound(suffixArray.begin(), suffixArray.end(), pattern, comp);
//
// 	return it2 - it1;
// }
