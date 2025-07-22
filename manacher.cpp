string convert(string s) {
    string q = "$";

    int len = s.size();

    for (int i = 0; i < len; i++) {
        q += "#";
        q += s[i];
    }

    q += "#@";

    return q;
}

/*
    https://youtu.be/nbTSfrEfo6M?si=_gaAN9hXf3ibnQGP
    
    s[i]            0     1     2     3     4    5     6     7     8
    q[i]      0  1  2  3  4  5  6  7  8  9  10   .  .  .  .  .  .  .

                                <----------ans--------->
    s    =          a     Z     b     d     e    d     b     X     a
    Q    =    $  #  a  #  Z  #  b  #  d  #  e #  d  #  b  #  X  #  a  #  @
    P[i] =                   5  4  3  2  1  0             ^                    <-- P[i] in reverse order actually
    center                                  c             r
    i            <---------------------------------------------------->

    ans = s.substr(2, 5)
        = b d e d b
        = (q[i] / 2) - 1
        = ((c - p[i] + 1) / 2) - 1 = index of b

    
    total palindormes = sum of [(P[i]+1)/2] for every i 
    abcdedcba is a palindrome with center e, radius 4: but e, ded, cdedc, bcdedcb, and abcdedcba are all palindromes.
*/

string manacher(string s) {
    string Q = convert(s);
    
    vector<int> P(Q.size());

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
