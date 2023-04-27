#include <iostream>
#include <string.h>

using namespace std;

int mistake_finder(const char input[], int length) {
    int mistake = 0;
    for (int i = 0; i < length; i++) {
        if (input[i] == '1') {
            mistake ^= i + 1;
        }
        return mistake;
    }
}

int main() {

    int mistake;
    int k;
    cin >> k;
    int info_position = 0;
    int shift = 1;
    char info[1000000];
    char input[1000000];

    for (int j = 0; j < k; j++) {
        cin >> input;
        int length = sizeof(input);

        mistake = mistake_finder(input, length);
        if (mistake) {
            input[mistake - 1] ^= '0' ^ '1';
        }

        for (int i = 0; i < length; i++) {
            if (i + 1 == shift) {
                shift <<= 1;
            } else {
                info[info_position++] = input[i];
            }
        }
        cout << info << '\n';
        memset(info, '0', sizeof(info));
        memset(input, '0', sizeof(input));
    }

    return 0;
}
