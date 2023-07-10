#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class CuckooHash {
private:
    int table_size;
    vector<string> hash_table1;
    vector<string> hash_table2;

    int hash1(string key) {
        int hash = 0;
        int _pow = 0;
        for (char c : key) {
            hash = (hash + (c - 'a' + 1) * _pow) % table_size;
            _pow = (_pow * 31) % table_size;
        }
        return hash;
    }

    int hash2(string key) {
        int hash = 0;
        int _pow = 0;
        for (char c : key) {
            hash = (hash + (c - 'a' + 1) * _pow) % table_size;
            _pow = (_pow * 17) % table_size;
        }
        return hash;
    }

    void rehash() {
        int new_size = table_size * 2;
        vector<string> new_table1(new_size, "");
        vector<string> new_table2(new_size, "");

        for (string key: hash_table1) {
            if (!key.empty()) {
                string curr_key = key;
                for (int i = 0; i < table_size; i++) {
                    swap(curr_key, new_table1[hash1(curr_key) % new_size]);
                    if (curr_key.empty()) {
                        break;
                    }
                    swap(curr_key, new_table2[hash2(curr_key) % new_size]);
                    if (curr_key.empty()) {
                        break;
                    }
                }
            }
        }

        hash_table1 = new_table1;
        hash_table2 = new_table2;
        table_size = new_size;
    }

public:
    CuckooHash(int size) {
        table_size = size;
        hash_table1 = vector<string>(table_size, "");
        hash_table2 = vector<string>(table_size, "");
    }

    void insert_key(string key) {
        if (search_key(key)) {
            return;
        }

        string curr_key = key;
        for (int i = 0; i < table_size; i++) {
            swap(curr_key, hash_table1[hash1(curr_key)]);
            if (curr_key.empty()) {
                hash_table1[hash1(key)] = key;
                return;
            }

            swap(curr_key, hash_table2[hash2(curr_key)]);
            if (curr_key.empty()) {
                hash_table2[hash2(key)] = key;
                return;
            }
        }

        rehash();
    }

    void delete_key(string key) {
        int index1 = hash1(key);
        int index2 = hash2(key);

        if (search_key(key)) {
            if (hash_table1[index1] == key) {
                hash_table1[index1] = "";
            } else if (hash_table2[index2] == key) {
                hash_table2[index2] = "";
            } else {
                return;
            }
        }
    }

    bool search_key(string key) {
        int index1 = hash1(key);
        int index2 = hash2(key);
        if (hash_table1[index1] == key || hash_table2[index2] == key) {
            return true;
        }
        return false;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    cin >> n;

    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;

    int t = n * 14;

    CuckooHash hash_table(t);
    CuckooHash hash_table_ex(t);

    vector<vector<string>> answers(3, vector<string>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> answers[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        hash_table_ex.insert_key(answers[0][i]);
        hash_table.insert_key(answers[1][i]);
    }

    for (int i = 0; i < n; i++) {
        if(!hash_table.search_key(answers[2][i]) && !hash_table_ex.search_key(answers[2][i])) {
            counter3 += 3;
        } else if(!hash_table.search_key(answers[2][i]) || !hash_table_ex.search_key(answers[2][i])) {
            if (hash_table.search_key(answers[2][i]) && !hash_table_ex.search_key(answers[2][i])) {
                counter3++;
            } else if (!hash_table.search_key(answers[2][i]) && hash_table_ex.search_key(answers[2][i])) {
                counter3++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        hash_table.delete_key(answers[1][i]);
    }


    for (int i = 0; i < n; i++) {
        hash_table.insert_key(answers[2][i]);
    }

    for (int i = 0; i < n; i++) {
        if (!hash_table.search_key(answers[1][i]) && !hash_table_ex.search_key(answers[1][i])) {
            counter2 += 3;
        } else if (!hash_table.search_key(answers[1][i]) || !hash_table_ex.search_key(answers[1][i])) {
            if (hash_table.search_key(answers[1][i]) && !hash_table_ex.search_key(answers[1][i])) {
                counter2++;
            } else if (!hash_table.search_key(answers[1][i]) && hash_table_ex.search_key(answers[1][i])) {
                counter2++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        hash_table.delete_key(answers[2][i]);
        hash_table_ex.delete_key(answers[0][i]);
    }


    for (int i = 0; i < n; i++) {
        hash_table.insert_key(answers[2][i]);
        hash_table_ex.insert_key(answers[1][i]);
    }

    for (int i = 0; i < n; i++) {
        if (!hash_table.search_key(answers[0][i]) && !hash_table_ex.search_key(answers[0][i])) {
            counter1 += 3;
        } else if (!hash_table.search_key(answers[0][i]) || !hash_table_ex.search_key(answers[0][i])) {
            if (hash_table.search_key(answers[0][i]) && !hash_table_ex.search_key(answers[0][i])) {
                counter1++;
            } else if (!hash_table.search_key(answers[0][i]) && hash_table_ex.search_key(answers[0][i])) {
                counter1++;
            }
        }
    }

    cout << counter1 << ' ' << counter2 << ' ' << counter3;

    return 0;
}