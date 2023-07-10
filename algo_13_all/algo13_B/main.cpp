#include <iostream>
#include <vector>

using namespace std;

class HashTable {
private:
    struct Pair {
        int key;
        int value;
    };

public:
    vector<vector<Pair>> table;

    HashTable(int table_size) : table(table_size) {}

    int hash(int key) {
        return key % table.size();
    }

    void insert(int key, int value) {
        int h = hash(key);
        for (auto& p : table[h]) {
            if (p.key == key) {
                p.value = value;
                return;
            }
        }
        table[h].push_back({key, value});
    }

    void remove(int key) {
        int h = hash(key);
        for (auto it = table[h].begin(); it != table[h].end(); ++it) {
            if (it->key == key) {
                table[h].erase(it);
                return;
            }
        }
    }

    int find(int key) {
        int h = hash(key);
        for (auto& p : table[h]) {
            if (p.key == key) {
                return p.value;
            }
        }
        return -1;
    }
};

int main() {
    int n, m;
    cin >> n;
    vector<int> word1(n);
    for (int i = 0; i < n; i++) {
        cin >> word1[i];
    }

    cin >> m;
    vector<int> word2(m);
    for (int i = 0; i < m; i++) {
        cin >> word2[i];
    }

    int ans = 0;
    for (int len = 1; len <= m; len++) {
        HashTable table(100000);
        for (int j = 0; j < len - 1; j++) {
            table.insert(word2[j], j);
        }
        for (int j = len - 1; j < m; j++) {
            table.insert(word2[j], j);
            int start = j - len + 1;
            int end = j;
            bool found = true;
            for (int k = start; k <= end; k++) {
                if (table.find(word1[k]) == -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                ans = len;
            }
            table.remove(word2[start]);
        }
    }

    cout << ans << '\n';
    return 0;
}