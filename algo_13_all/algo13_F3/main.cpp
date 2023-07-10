#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Cuckoo {
private:
    int table_size;
    vector<int> hash_table1;
    vector<int> hash_table2;

    int hash(int key) const {
        return key % table_size;
    }

    void rehash() {
        int new_size = 2 * table_size;
        vector<int> new_hash_table1(new_size, -1);
        vector<int> new_hash_table2(new_size, -1);

        for (int key : hash_table1) {
            if (key != -1) {
                int new_place = key % new_size;
                if (new_hash_table1[new_place] != -1) {
                    swap(key, new_hash_table1[new_place]);
                    new_place = key % new_size;
                }

                new_hash_table1[new_place] = key;
            }
        }

        for (int key : hash_table2) {
            if (key != -1) {
                int new_place = key % new_size;
                if (new_hash_table2[new_place] != -1) {
                    swap(key, new_hash_table2[new_place]);
                    new_place = key % new_size;
                }

                new_hash_table2[new_place] = key;
            }
        }

        table_size = new_size;
        hash_table1 = new_hash_table1;
        hash_table2 = new_hash_table2;
    }

public:
    Cuckoo(int _size) : table_size(_size), hash_table1(_size, -1), hash_table2(_size, -1) {}

    bool insert(int key) {
        if (search(key)) {
            return false;
        }

        int curr_key = key;
        for (int i = 0; i < table_size; ++i) {
            swap(curr_key, hash_table1[hash(curr_key)]);
            if (curr_key == -1) {
                hash_table1[hash(key)] = key;
                return true;
            }

            swap(curr_key, hash_table2[hash(curr_key)]);
            if (curr_key == -1) {
                hash_table2[hash(key)] = key;
                return true;
            }
        }

        rehash();
        return insert(key);
    }

    bool search(int key) const {
        return hash_table1[hash(key)] == key || hash_table2[hash(key)] == key;
    }

    void clear() {
        fill(hash_table1.begin(), hash_table1.end(), -1);
        fill(hash_table2.begin(), hash_table2.end(), -1);
    }

};

int main() {
    int n;
    cin >> n;

    Cuckoo hash_table(n * 2);

    vector<vector<string>> answers(3, vector<string>(n));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> answers[i][j];
        }
    }

    vector<int> counter(3, 0);
    for (int j = 0; j < n; ++j) {
        hash_table.clear();

        for (int i = 0; i < 3; ++i) {
            hash_table.insert(hash<string>()(answers[i][j]));
        }

        for (int i = 0; i < 3; ++i) {
            if (!hash_table.search(hash<string>()(answers[i][j]))) {
                counter[i] += 3;
            } else if (hash_table.insert(hash<string>()(answers[i][j]))) {
                counter[i]++;
            }
        }

    }

    for (int i = 0; i < 3; i++) {
        cout << counter[i] << ' ';
    }

    return 0;
}