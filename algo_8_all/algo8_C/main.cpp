#include <iostream>
#include <string>

using namespace std;

int length;

int find_mistake(string input[], int k) {
    int mistake = 0;
    for (int i = 0; i < length; i++) {
        if (input[k][i] == '1') {
            mistake ^= i + 1;
        }
        return mistake;
    }
}

int main() {
    int mistake = 0;
    char info[2000];
    int info_position = 0;
    int b = 1;
    int k;
    cin >> k;
    string input[k];
    string output[k];
    for (int i = 0; i < k; i++) {
        cin >> input[i];
    }

    for (int j = 0; j < k; j++) {
        length = sizeof(input[j]);
        mistake = find_mistake(input, k);
        if (mistake) {
            input[j][mistake - 1] ^= '0' xor '1';
            mistake = find_mistake(input, k);
        }
        for (int i = 0; i < length; i++) {
            if (i + 1 == b) {
                b <<= 1;
            } else {
                info[info_position++] = input[j][i];
            }
        }
        for (int i = 0; i < length; i++) {
            output[j][i] = info[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        cout << output[k] << '\n';
    }
    return 0;
}
