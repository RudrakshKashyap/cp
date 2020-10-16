https://codeforces.com/blog/entry/55782?#comment-395139

const int maxx=100005;
int trie[maxx][26], finish[maxx];
int nxt = 1;
void Add (string s){
    int node = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if(trie[node][s[i] - 'a'] == 0) {
            node = trie[node][s[i] - 'a'] = nxt;
            nxt++;
        } else {
            node = trie[node][s[i] - 'a'];
        }
    }
    finish[node - 1] = 1;
}

int Find (string s) {
    int idx = 0;
    int sz=s.size();
    for (int i = 0; i < sz; i++)
        if (trie[idx][s[i] - 'a'] == 0)
            return 0;
        else
            idx = trie[idx][s[i] - 'a'];
    return finish[idx];
}


////////////////////////////////////////////////////////////////// with delete
const int maxx=100005;
int trie[maxx][26], finish[maxx], freq[maxx];
int nxt = 1;
void Add (string s){
    int node = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if(trie[node][s[i] - 'a'] == 0) {
            node = trie[node][s[i] - 'a'] = nxt;
            freq[node]++;
            nxt++;
        } else {
            node = trie[node][s[i] - 'a'];
            freq[node]++;
        }
    }
    finish[node - 1]++;
}

int Find (string s) {
    int idx = 0;
    int sz=s.size();
    for (int i = 0; i < sz; i++)
        if (trie[idx][s[i] - 'a'] == 0 || freq[trie[idx][s[i]-'a']] <= 0)
            return 0;
        else
            idx = trie[idx][s[i] - 'a'];
    return finish[idx - 1];
}

void Delete(string s)
{
    int node = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        node = trie[node][s[i] - 'a'];
        freq[node]--;
    }
    finish[node - 1]--;
}


/////////////////////////////////////////////////////////////////////////////leetcode
class Trie {
    struct Trienode
    {
        Trienode* next[26];
        bool is_word = false;
    };
public:
    Trienode *root;
    
    
    /** Initialize your data structure here. */
    Trie() {
        root = new Trienode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string s) {
        Trienode* p = root;
        for(int i = 0; i < s.size(); i++)
        {
            if(p -> next[s[i] - 'a'] == NULL)
                p -> next[s[i] - 'a'] = new Trienode();
            
            p = p -> next[s[i] - 'a'];
        }
        p -> is_word = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trienode* p = root;
        for(int i = 0; i < word.size() && p != NULL; i++)
            p = p -> next[word[i] - 'a'];
        
        return p!=NULL && p -> is_word;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        Trienode* p = root;
        for(int i = 0; i < word.size() && p != NULL; i++)
            p = p -> next[word[i] - 'a'];
        
        return p!=NULL;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
