https://codeforces.com/blog/entry/55782?#comment-395139

intt trie[maxx][26], finish[maxx];
intt nxt = 1;
void Add (string s){
    intt node = 0;
    for (intt i = 0; s[i] != '\0'; i++) {
        if(trie[node][s[i] - 'a'] == 0) {
            node = trie[node][s[i] - 'a'] = nxt;
            nxt++;
        } else {
            node = trie[node][s[i] - 'a'];
        }
    }
    finish[node - 1] = 1;   //finish[nxt - 1] = 1;
}

intt Find (string s) {
    intt idx = 0;
    for (intt i = 0; i < s.size(); i++)
        if (trie[idx][s[i] - 'a'] == 0)
            return 0;
        else
            idx = trie[idx][s[i] - 'a'];
    return finish[idx];
}
