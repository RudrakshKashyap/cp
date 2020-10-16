int P[SIZE * 2];

// Transform S into new string with special characters inserted.
string convert(string s) {
    string newString = "$";

    int len = s.size();

    for (int i = 0; i < len; i++) {
        newString += "#";
        newString += s[i];
    }

    newString += "#@";

    return newString;
}

string manacher(string s) {
    string Q = convert(s);

    int c = 0, r = 0;                // current center, right limit

    int len = Q.size();

    for (int i = 1; i < len - 1; i++) {
        // find the corresponding letter in the palidrome subString
        int iMirror = c - (i - c);

        if(i < r) {
            P[i] = min(r - i, P[iMirror]);
        }

        // expanding around center i
        while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]){
            P[i]++;
        }

        // Update c,r in case if the palindrome centered at i expands past r,
        if (i + P[i] > r) {
            c = i;              // next center = i
            r = i + P[i];
        }
    }

    // Find the longest palindrome length in p.

    int maxPalindrome = 0;
    int centerIndex = 0;

    for (int i = 1; i < len - 1; i++) {

        print(P[i]);
        if (maxPalindrome < P[i]) {
            maxPalindrome = P[i];
            centerIndex = i;
        }
    }

    cout << maxPalindrome << "\n";
    return s.substr( (centerIndex - 1 - maxPalindrome) / 2, maxPalindrome);
}
