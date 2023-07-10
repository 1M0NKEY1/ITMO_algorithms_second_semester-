#include <iostream>
#include <regex>
#include <vector>

using namespace std;

bool check(const string_view& str, int i) {
    regex regular;
    switch (i) {
        case 0:
        case 1:
        case 2:
            regular = regex("[A-Z][a-z]*");
            break;
        case 3:
            regular = regex("[0-9]{2}");
            break;
        case 4:
            regular = regex(R"(^\+7\(\d{3}\)-\d{3}-\d{2}-\d{2}$|^\+7\d{10}$|^\+7\(\d{3}\)\d{3}-\d{4}$)");
            break;
        case 5:
            regular = regex("g\\.[A-Z]{3},");
            break;
        case 6:
            regular = regex("ul\\.[A-Z][a-z]*,");
            break;
        case 7:
            regular = regex("d\\.[0-9]+");
            break;
    }

    return regex_match(str.begin(), str.end(), regular);
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int g = 0; g < n; g++) {
        char symbol;
        cin >> symbol;
        string input;
        getline(cin, input);
        input = symbol + input;

        vector<string> array(8, "brake");
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
            if (S == "brake") {
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
            if (i == 3 || i == 5 || i == 6 || i == 7) {
                if (!check(str, i)) {
                    flag = false;
                    break;
                }
            } else if (i == 4) {
                if (str[0] == '+' && str[1] != '7') {
                    flag = false;
                    break;
                } else if (str[0] == '+') {
                    str.erase(remove(str.begin(), str.end(), '('), str.end());
                    str.erase(remove(str.begin(), str.end(), ')'), str.end());
                    str.erase(remove(str.begin(), str.end(), '-'), str.end());

                    if (!check(str, i)) {
                        flag = false;
                        break;
                    }
                }
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