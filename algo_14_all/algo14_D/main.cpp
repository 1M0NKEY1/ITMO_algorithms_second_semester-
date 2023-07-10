#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 26;

struct TrieNode {
    bool isEnd;
    int cnt;
    vector<int> books;
    TrieNode* next[MAXN];

    TrieNode() {
        isEnd = false;
        cnt = 0;
        books = vector<int>();
        for (int i = 0; i < MAXN; i++) {
            next[i] = NULL;
        }
    }
};

TrieNode* add_word(TrieNode* root, string word, int book) {
    TrieNode* cur = root;
    int n = word.size();
    for (int i = 0; i < n; i++) {
        int ind = word[i] - 'a';
        if (cur->next[ind] == NULL) {
            cur->next[ind] = new TrieNode();
        }
        cur = cur->next[ind];
        cur->cnt++;
    }
    cur->isEnd = true;
    cur->books.push_back(book);
    return root;
}

int query_k_th(TrieNode* root, int k) {
    TrieNode* cur = root;
    while (k > 0) {
        for (int i = 0; i < MAXN; i++) {
            if (cur->next[i] != NULL) {
                if (cur->next[i]->cnt >= k) {
                    cur = cur->next[i];
                    k--;
                    break;
                } else {
                    k -= cur->next[i]->cnt;
                }
            }
        }
    }
    return cur->books[cur->books.size() - 1];
}

int main() {
    int n, book_cnt = 0;
    TrieNode* root = new TrieNode();
    cin >> n;

    for (int i = 0; i < n; i++) {
        char c;
        string input;
        getline(cin, input);
        input = c + input;
        if (isdigit(c)) {
            root = add_word(root, input, ++book_cnt);
        } else {

            cout << query_k_th(root, ::isdigit(c)) << '\n';
        }
    }
    return 0;
}