#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string t;
    string x;
    getline(cin, t);
    getline(cin, x);

    int counter = 0;
    vector<int> indexes;

    size_t position = t.find(x);
    while (position != string::npos) {
        counter++;
        indexes.push_back(position);
        position = t.find(x, ++position);
    }

    cout << counter << '\n';

    for (int i = 0; i < indexes.size(); i++) {
        cout << indexes[i] << ' ';
    }


    return 0;
}