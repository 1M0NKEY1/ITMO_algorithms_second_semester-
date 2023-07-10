#include <iostream>
#include <vector>

using namespace std;

bool check(const string_view& str, int i) {
    switch (i) {
        case 0: {
            if (!isupper(str[0])) {
                return false;
            }
            for (int j = 1; j < str.size(); j++) {
                if (!islower(str[j]) && !isdigit(str[j])) {
                    return false;
                }
            }
            return true;
        }

        case 1: {
            if (!isupper(str[0])) {
                return false;
            }
            for (int j = 1; j < str.size(); j++) {
                if (!islower(str[j]) && !isdigit(str[j])) {
                    return false;
                }
            }
            return true;
        }

        case 2: {
            if (!isupper(str[0])) {
                return false;
            }
            for (int j = 1; j < str.size(); j++) {
                if (!islower(str[j]) && !isdigit(str[j])) {
                    return false;
                }
            }
            return true;
        }

        case 3: {
            if (str.size() != 2) {
                return false;
            }

            for (int j = 0; j < 2; j++) {
                if (!isdigit(str[j])) {
                    return false;
                }
            }

            return true;
        }

        case 4: {
            if (str.size() == 17 && str[0] == '+' && str[1] == '7' && str[2] == '(' &&
                isdigit(str[3]) && isdigit(str[4]) && isdigit(str[5]) && str[6] == ')' && str[7] == '-' &&
                isdigit(str[8]) && isdigit(str[9]) && isdigit(str[10]) && str[11] == '-' &&
                isdigit(str[12]) && isdigit(str[13]) && str[14] == '-' && isdigit(str[15]) &&
                isdigit(str[16])) {
                return true;

            } else if (str.size() == 15 &&  str[0] == '+' && str[1] == '7' && str[2] == '(' &&
                       isdigit(str[3]) && isdigit(str[4]) && isdigit(str[5]) && str[6] == ')' &&
                       isdigit(str[7]) && isdigit(str[8]) && isdigit(str[9]) && str[10] == '-' &&
                       isdigit(str[11]) && isdigit(str[12]) && isdigit(str[13]) &&
                       isdigit(str[14])) {
                return true;

            } else if (str.size() == 12 && str[0] == '+' && str[1] == '7') {
                for (int j = 2; j < 12; j++) {
                    if (!isdigit(str[j])) {
                        return false;
                    }
                }
                return true;

            } else if (str.size() == 11 && (str[0] == '7' || str[0] == '8') && isdigit(str[1]) && isdigit(str[2]) &&
                       isdigit(str[3]) && isdigit(str[4]) && isdigit(str[5]) && isdigit(str[6]) &&
                       isdigit(str[7]) && isdigit(str[8]) && isdigit(str[9]) && isdigit(str[10])){
                return true;

            } else {
                return false;
            }
        }

        case 5: {
            if (str.size() > 6 || str.size() < 6 || str[0] != 'g' || str[1] != '.' ||
                !isupper(str[2]) || !isupper(str[3]) || !isupper(str[4]) || str[5] != ',') {
                return false;
            }
            return true;
        }

        case 6: {
            if (str.size() < 5 || str[0] != 'u' || str[1] != 'l' || str[2] != '.' || !isupper(str[3])) {
                return false;
            }

            for (int j = 4; j < str.size() - 1; j++) {
                if (!islower(str[j])) {
                    return false;
                }
            }

            if (str.back() != ',') {
                return false;

            }
            return true;
        }

        case 7: {
            if (str.size() <= 2 || str[0] != 'd' || str[1] != '.') {
                return false;
            }
            for (int j = 2; j < str.size(); j++) {
                if (!isdigit(str[j])) {
                    return false;
                }
            }
            return true;
        }

        default: {
            return false;
        }
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int g = 0; g < n; g++) {
        string input;
        getline(cin, input);


        vector<string> array(8, "error");
        string tmp;
        int step = 0;

        for (char ch : input) {
            if (!isspace(ch)) {
                tmp += ch;
            } else {
                array[step++] = tmp;
                tmp.clear();
            }
        }
        array[step] = tmp;

        bool flag = true;
        for (const string& S : array) {
            if (S == "error") {
                flag = false;
                break;
            }
        }

        if (!flag) {
            cout << "NO" << '\n';
            continue;
        }

        for (int i = 0; i < 8; i++) {
            string str = array[i];
            if (!check(str, i)) {
                flag = false;
                break;
            }
        }

        if (flag) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}