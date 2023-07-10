#include <iostream>
#include <vector>

using namespace std;

int hash_func(int a, int n) {
    return a % n;
}

int main() {
    int n;
    cin >> n;

    int t = n * 2;

    vector<int> a;
    vector<int> b;
    a.resize(t);
    b.resize(t);

    vector<int> tmp_a(t);
    vector<int> tmp_b(t);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        ++tmp_a[hash_func(a[i], t)];
        ++tmp_b[hash_func(b[i], t)];
    }

    bool equal = true;
    for (int i = 0; i < t; i++) {
        if (tmp_a[i] != tmp_b[i]) {
            equal = false;
            break;
        }
    }

    if (equal) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}