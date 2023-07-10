#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

class HashTable {
private:
    struct Pair {
        int isu;
        int points;
    };

public:
    list<Pair>* table;
    int size;

    HashTable(int table_size) {
        size = table_size;
        table = new list<Pair>[size];
    }

    ~HashTable() {
        delete[] table;
    }

    int hash(int isu) {
        return isu % size;
    }

    void insert(int isu, int points) {
        int h = hash(isu);
        for (auto& p : table[h]) {
            if (p.isu == isu) {
                p.points = points;
                return;
            }
        }
        table[h].push_back({isu, points});
    }

    void remove(int isu) {
        int h = hash(isu);
        for (auto it = table[h].begin(); it != table[h].end(); ++it) {
            if (it->isu == isu) {
                table[h].erase(it);
                return;
            }
        }
    }

    pair<int, int> find_max() {
        int max_points = -1;
        int max_isu = -1;
        for (int i = 0; i < size; i++) {
            for (auto& pair : table[i]) {
                if (pair.points > max_points) {
                    max_points = pair.points;
                    max_isu = pair.isu;
                }
            }
        }
        return {max_isu, max_points};
    }

    int find_average() {
        int sum_points = 0;
        int num_students = 0;
        for (int i = 0; i < size; i++) {
            for (auto& pair : table[i]) {
                sum_points += pair.points;
                num_students++;
            }
        }
        return (num_students == 0) ? 0 : (int) sum_points / num_students;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);

    int m, q;
    cin >> m >> q;
    vector<HashTable> groups(m, HashTable(m));

    for (int i = 0; i < m; i++) {
        groups[i] = HashTable(m * 5);
    }

    for (int i = 0; i < q; i++) {
        char command;
        int avg;
        int group, isu, points;
        cin >> command >> group;
        switch (command) {
            case 'a':
                avg = groups[group - 1].find_average();
                cout << avg << '\n';
                break;
            case '-':
                cin >> isu;
                groups[group - 1].remove(isu);
                break;
            case '+':
                cin >> isu >> points;
                groups[group - 1].insert(isu, points);
                break;
            case 'm':
                auto result = groups[group - 1].find_max();
                cout << result.second << '\n';
                break;
        }
    }

    return 0;
}