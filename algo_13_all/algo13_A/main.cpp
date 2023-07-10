#include <iostream>
#include <vector>


using namespace std;

class HASH {
public:
    vector<vector<int>> arr_of_points;
    vector<int> indexes_of_keys;
    int size_of_massive;
    int count;

    HASH(int size) {
        arr_of_points.resize(size);
        indexes_of_keys.resize(size, -1);
        size_of_massive = size;
        count = 0;
    }

    int hash_index(int x, int y) const {
        return (x * 23 + y * 13) % size_of_massive;
    }

    void insert(int x, int y) {
        int hash = hash_index(x, y);

        while (indexes_of_keys[hash] != -1) {
            hash = (hash + 1) % size_of_massive;
        }

        arr_of_points[hash] = {x, y};
        indexes_of_keys[hash] = count;
        count++;
    }

    int find_coord(int x, int y) {
        int hash = hash_index(x, y);

        int count_1 = 0;
        while (indexes_of_keys[hash] != -1 && count_1 < count) {
            if (arr_of_points[hash][0] == x && arr_of_points[hash][1] == y) {
                return indexes_of_keys[hash];
            }
            hash = (hash + 1) % size_of_massive;
            count_1++;
        }

        return -1;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    HASH hash_table(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        hash_table.insert(x, y);
    }

    for (int i = 0; i < n; i++) {
        int x1 = hash_table.arr_of_points[i][0];
        int y1 = hash_table.arr_of_points[i][1];
        int t1 = hash_table.find_coord(x1, y1);
        if (t1 == -1) {
            continue;
        }

        for (int j = i + 1; j < n; j++) {
            int x2 = hash_table.arr_of_points[j][0];
            int y2 = hash_table.arr_of_points[j][1];
            int t2 = hash_table.find_coord(x2, y2);
            if (t2 == -1) {
                continue;
            }

            if (x1 == x2 || y1 == y2) {
                continue;
            }

            int x3 = x1;
            int y3 = y2;
            int t3 = hash_table.find_coord(x3, y3);
            if (t3 != -1 && t3 != t1 && t3 != t2) {
                cout << "YES" << '\n';
                return 0;
            }

            x3 = x2;
            y3 = y1;
            t3 = hash_table.find_coord(x3, y3);
            if (t3 != -1 && t3 != t1 && t3 != t2) {
                cout << "YES" << '\n';
                return 0;
            }
        }
    }

    cout << "NO" << '\n';
    return 0;
}
