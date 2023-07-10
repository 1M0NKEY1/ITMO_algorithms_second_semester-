#include <iostream>
#include <vector>

using namespace std;

class CuckooHash {
private:
    int table_size;
    vector<string> hash_table;

    int hash1(string key) {
        int hash = 0;
        int _pow = 1;
        for (char c : key) {
            hash = (hash + (c - 'a' + 1) * _pow) % table_size;
            _pow = _pow * 193;
        }
        return hash;
    }

    int hash2(string key) {
        int hash = 0;
        int _pow = 1;
        for (char c : key) {
            hash = (hash + (c - 'a' + 1) * _pow) % table_size;
            _pow = _pow * 101;
        }
        return hash;
    }

    void rehash() {
        int old_size = table_size;
        table_size = 2 * old_size;
        vector<string> old_table = hash_table;
        vector<string> deleted_keys;
        hash_table = vector<string>(table_size, "");

        for (int i = 0; i < old_size; i++) {
            if (!old_table[i].empty()) {
                string curr_key = old_table[i];
                bool inserted = false;
                for (int j = 0; j < table_size; j++) {
                    int index1 = hash1(curr_key);
                    int index2 = hash2(curr_key);
                    if (hash_table[index1].empty()) {
                        swap(curr_key, hash_table[index1]);
                        inserted = true;
                        break;
                    } else if (hash_table[index2].empty()) {
                        swap(curr_key, hash_table[index2]);
                        inserted = true;
                        break;
                    } else if (hash_table[index1] == curr_key || hash_table[index2] == curr_key) {
                        inserted = true;
                        break;
                    }
                    swap(curr_key, hash_table[index1]);
                }
                if (!inserted) {
                    deleted_keys.push_back(old_table[i]);
                }
            }
        }

        for (string key : deleted_keys) {
            insert_key(key);
        }
    }
public:
    CuckooHash(int size) {
        table_size = size;
        hash_table = vector<string>(table_size, "");
    }

    bool search_key(string key) {
        int index1 = hash1(key);
        int index2 = hash2(key);
        if (hash_table[index1] == key || hash_table[index2] == key) {
            return true;
        }
        return false;
    }

    void insert_key(string key) {
        if (search_key(key)) {
            return;
        }

        string curr_key = key;
        string temp_key;

        for (int i = 0; i < table_size; i++) {
            int index1 = hash1(curr_key);
            int index2 = hash2(curr_key);
            if (hash_table[index1].empty()) {
                hash_table[index1] = curr_key;
                return;
            } else if (hash_table[index2].empty()) {
                hash_table[index2] = curr_key;
                return;
            } else {
                temp_key = curr_key;
                swap(curr_key, hash_table[index2]);
                if (curr_key == key) {
                    return;
                }
                if (curr_key == hash_table[index1] || curr_key == hash_table[index2]) {
                    rehash();
                    insert_key(key);
                    return;
                }
            }
        }

        rehash();
        insert_key(key);
    }

    void delete_key(string key) {
        int index1 = hash1(key);
        int index2 = hash2(key);

        if (hash_table[index1] == key) {
            hash_table[index1] = "";
        }
        if (hash_table[index2] == key) {
            hash_table[index2] = "";
        }
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

    int t = n * 113;

    CuckooHash hash_table(t);
    CuckooHash hash_table_ex(t);

    string str;
    vector<vector<string>> answers(3, vector<string>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> str;
            answers[i][j] = str;
        }
    }

    for (int i = 0; i < n; i++) {
        hash_table_ex.insert_key(answers[0][i]);
        hash_table.insert_key(answers[1][i]);
    }

    for (int i = 0; i < n; i++) {
        if (!hash_table.search_key(answers[2][i]) && !hash_table_ex.search_key(answers[2][i])) {
            counter3 += 3;
        } else if (!hash_table.search_key(answers[2][i]) || !hash_table_ex.search_key(answers[2][i])) {
            if (!hash_table.search_key(answers[2][i]) && hash_table_ex.search_key(answers[2][i])) {
                counter3++;
            } else if (hash_table.search_key(answers[2][i]) && !hash_table_ex.search_key(answers[2][i])) {
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
            if (!hash_table.search_key(answers[1][i]) && hash_table_ex.search_key(answers[1][i])) {
                counter2++;
            } else if (hash_table.search_key(answers[1][i]) && !hash_table_ex.search_key(answers[1][i])) {
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
            if (!hash_table.search_key(answers[0][i]) && hash_table_ex.search_key(answers[0][i])) {
                counter1++;
            } else if (hash_table.search_key(answers[0][i]) && !hash_table_ex.search_key(answers[0][i])) {
                counter1++;
            }
        }
    }

    cout << counter1 << ' ' << counter2 << ' ' << counter3;

    return 0;
}