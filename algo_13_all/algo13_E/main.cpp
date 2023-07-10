#include <iostream>
#include <vector>

using namespace std;

int hash_func(int x, int n) {
    return ((x % n) + n) % n;
}

int main() {
    int n;
    cin >> n;

    int t = n * 14;

    vector<int> S(n);
    vector<int> tmp(t);

    for (int i = 0; i < n; i++) {
        cin >> S[i];
        ++tmp[hash_func(S[i] - i, t)];
    }

    int answer = 0;
    for (int i = 0; i < n; i++) {
        --tmp[hash_func(S[i] - i, t)];
        answer += tmp[hash_func(S[i] - i, t)];
    }

    cout << answer << '\n';

    return 0;
}