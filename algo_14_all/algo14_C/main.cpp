#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    int ans = 0;
    for (int i = 0; i < m; i++) {
        string first_str, second_str;
        int start1, start2, len;
        cin >> start1 >> start2 >> len;

        first_str = s.substr(start1 - 1, len);
        second_str = s.substr(start2 - 1, len);

        if (first_str == second_str) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}