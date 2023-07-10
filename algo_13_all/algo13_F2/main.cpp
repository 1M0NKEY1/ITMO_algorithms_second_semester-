#include <iostream>
#include <vector>

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

        int count = 0;
        while (count < table_size) {
            int index1 = hash1(key);
            if (hash_table1[index1] == "") {
                hash_table1[index1] = key;
                return;
            }

            int index2 = hash2(key);
            if (hash_table2[index2] == "") {
                hash_table2[index2] = key;
                return;
            }

            string tmp = hash_table1[index1];
            hash_table1[index1] = key;
            key = tmp;
            if (rand() % 2 == 0) {
                swap(index2, index1);
            }
            count++;
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

    void clear() {
        fill(hash_table1.begin(), hash_table1.end(), "");
        fill(hash_table2.begin(), hash_table2.end(), "");
    }

};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    cin >> n;

    vector<vector<string>> answers(3, vector<string>(n));

    int t = n * 5;
    vector<int> counters(3, 0);

    CuckooHash hash_table(t);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> answers[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        hash_table.clear();

        for (int i = 0; i < 3; ++i) {
            hash_table.insert_key(answers[i][j]);
        }

        for (int i = 0; i < 3; ++i) {
            if (!hash_table.search_key(answers[i][j])) {
                counters[i] += 3;
            } else if (hash_table.search_key(answers[i][j])) {
                counters[i]++;
            }
        }

    }


    cout << counters[0] << ' ' << counters[1] << ' ' << counters[2];

    return 0;
}