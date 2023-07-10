#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparison(vector<int>& arr, int k) {
    for (int i = 0; i < k; i++) {
        if ((k + 1 > arr.size()) || (k - 1 - i < 0)) {
            continue;
        }
        if (arr[k + i] != arr[k - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;

    vector<int> array_of_cards;
    for (int i = 0; i < n; i++) {
        cin >> m;
        array_of_cards.push_back(m);
    }

    vector<int> positions;
    for (int i = 0; i < n; i++) {
        if (comparison(array_of_cards, i)) {
            positions.push_back(n - i);
        }
    }

    reverse(positions.begin(), positions.end());

    for (auto i : positions) {
        cout << i << ' ';
    }

    return 0;
}