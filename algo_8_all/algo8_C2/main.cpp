#include <iostream>

using namespace std;

int mistake_finder(string input, const int length) {
    int mistake = 0;
    for (int i = 0; i < length; i++) {
        if (input[i] == '1') {
            mistake ^= i + 1;
        }
        return mistake;
    }
}

int main() {

    int k;
    cin >> k;

    for (int j = 0; j < k; j++) {
        int length;
        int mistake;
        string input;
        string info;
        int shift = 1;
        cin >> input;
        length = input.size();

        mistake = mistake_finder(input, length);
        if (mistake) {
            input[mistake - 1] ^= '0' ^ '1';
        }

        for (int i = 0; i < length; i++) {
            if (i + 1 == shift) {
                shift <<= 1;
            } else {
                info += input[i];
            }
        }
        cout << info << '\n';
    }
    return 0;
}
