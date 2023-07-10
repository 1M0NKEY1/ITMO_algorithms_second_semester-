#include <iostream>
#include <vector>

using namespace std;

int hash_func(int coord, int number, int size) {
    return (coord + number) % size;
}

int main() {
    int n;
    cin >> n;

    int threads = 0;
    int table_size = n * 2;
    vector<pair<int, int>> x_coord(table_size, make_pair(-1, 0));
    vector<pair<int, int>> y_coord(table_size, make_pair(-1, 0));

    int x;
    int y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;

        int counter_ex = 0;
        while (x_coord[hash_func(x, counter_ex, table_size)].first != x && x_coord[hash_func(x, counter_ex, table_size)].first != -1) {
            counter_ex++;
        }

        int x_pos = hash_func(x, counter_ex, table_size);
        counter_ex = 0;
        while (y_coord[hash_func(y, counter_ex, table_size)].first != y && y_coord[hash_func(y, counter_ex, table_size)].first != -1) {
            counter_ex++;
        }

        int y_pos = hash_func(y, counter_ex, table_size);
        if (x_coord[x_pos].second == 0 and y_coord[y_pos].second == 0) {
            threads++;
        }

        x_coord[x_pos].first = x;
        x_coord[x_pos].second++;

        y_coord[y_pos].first = y;
        y_coord[y_pos].second++;
    }

    if (threads <= 3) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}