https://codeforces.com/blog/entry/55782?#comment-395139

```cpp
const int maxx = 100005;
int trie[maxx+1][26], finish[maxx+1], freq[maxx+1];
int nxt = 1;
void Add (string s) {
    int node = 0;
    for (int i = 0; i < s.size(); i++) {
        if(trie[node][s[i] - 'a'] == 0) {
            node = trie[node][s[i] - 'a'] = nxt;
            freq[node]++;
            nxt++;
        } else {
            node = trie[node][s[i] - 'a'];
            freq[node]++;
        }
    }
    finish[node]++;
}

int Find (string s) {
    int idx = 0;
    for (int i = 0; i < s.size(); i++)
        if (trie[idx][s[i] - 'a'] == 0 || freq[trie[idx][s[i]-'a']] <= 0)
            return 0;
        else
            idx = trie[idx][s[i] - 'a'];

    return finish[idx];
}

void Delete(string s) {
    int node = 0;
    for (int i = 0; i < s.size(); i++)
    {
        node = trie[node][s[i] - 'a'];
        freq[node]--;
    }
    finish[node]--;
}

array<int, 2> query_min(int x) {
    int node = 0, res_xor = 0, val = 0;
    for (int bit = 30; bit >= 0; bit--) {
        int b = (x >> bit) & 1; //bit we need
        if (trie[node][b] == -1 || freq[trie[node][b]] == 0) {
            val += (1^b) << bit;
            res_xor += 1 << bit;
            node = trie[node][1^b];
        }
        else {
            val += b << bit;
            node = trie[node][b];
        }
    }
    return {res_xor, val};
}
```

---

```
////////////////////////////
https://codeforces.com/blog/entry/11080 - check 5th useful link
http://www.opensource.apple.com/source/llvmgcc42/llvmgcc42-2336.9/libstdc++-v3/testsuite/ext/pb_ds/example/trie_prefix_search.cc

```

```cpp
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

class Trie {
    struct Trienode
    {
        Trienode* next[26] = {};
        bool is_word = false;
        int freq = 0;
    };
public:
    Trienode *root;

    Trie() {
        root = new Trienode();
        root->freq = 1;
    }
    // ~Trie() {
    //     deleteTrie(root);
    // }

    //d = -1 for delete, only delete if present
    void insert(string s, int d) {
        Trienode* p = root;
        for(int i = 0; i < s.size(); i++)
        {
            int idx = s[i] - 'a';
            if(p->next[idx] == NULL) p->next[idx] = new Trienode();

            p = p->next[idx];
            p->freq += d;
        }
        p->is_word = (p->freq > 0);
    }

    bool search(string word) {
        Trienode* p = root;
        for(int i = 0; i < word.size() && p != NULL; i++)
        {
            int idx = word[i] - 'a';
            if(p->next[idx] == NULL  || p->next[idx]->freq <= 0) 
                return false;

            p = p->next[idx];
        }

        return p->is_word;
    }

    bool startsWith(string word) {
        Trienode* p = root;
        for(int i = 0; i < word.size() && p != NULL && p->freq > 0; i++)
                p = p->next[word[i] - 'a'];

        return p != NULL && p->freq > 0;
    }
};
```
