#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

int hashX(int x, int table_size) {
    return x * 7 % table_size;
}

int hashY(int y, int table_size) {
    return y * 7 % table_size;
}

bool find_nail(vector<Point>& nails, vector<int>& tableX, vector<int>& tableY, int table_size) {
    for (int i = 0; i < nails.size(); i++) {
        int x_index = hashX(nails[i].x, table_size);

        for (int j = 0; j < tableX.size(); j++) {
            if (tableX[x_index] != -1 && nails[i].x == nails[tableX[x_index]].x && i != tableX[x_index]) {
                int y_index = hashY(nails[i].y, table_size);

                for (int k = 0; k < tableY.size(); k++) {
                    if (tableY[y_index] != -1 && nails[i].y == nails[tableY[y_index]].y && i != tableY[y_index]) {
                        return true;
                    }

                    y_index = (y_index + 1) % table_size;
                }
            }

            x_index = (x_index + 1) % table_size;
        }
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    int table_size = n * n;

    vector<int> tableX(table_size, -1);
    vector<int> tableY(table_size, -1);


    vector<Point> nails(n);
    for (int i = 0; i < n; i++) {
        Point nail;
        cin >> nail.x >> nail.y;
        int index = hashX(nail.x, table_size);

        while (tableX[index] != -1) {
            index = (index + 1) % table_size;
        }

        tableX[index] = i;
        index = hashY(nail.y, table_size);

        while (tableY[index] != -1) {
            index = (index + 1) % table_size;
        }

        tableY[index] = i;
        nails[i] = nail;
    }


    if (find_nail(nails, tableX, tableY, table_size)) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}