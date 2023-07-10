#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool check_name(const string& name) {
    if (name.size() == 0) {
        return false;
    }

    int cnt = 0;

    for (char c : name) {
        if (!isalpha(c)) {
            return false;
        }
        if (cnt == 0 && !isupper(c)) {
            return false;
        }
        if (cnt != 0 && isupper(c)) {
            return false;
        }
        ++cnt;
    }

    return cnt == 3;
}

bool check_age(const string& age) {
    if (age.size() != 2) {
        return false;
    }

    for (char c : age) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

bool check_phone(const string& phone) {
    if (phone.size() != 11 && phone.size() != 12 && phone.size() != 14) {
        return false;
    }

    bool with_plus = false;

    if (phone[0] == '+') {
        with_plus = true;
    }

    int digit_cnt = 0;

    for (char c : phone) {
        if (isdigit(c)) {
            ++digit_cnt;
        } else if (with_plus && c != '(' && c != ')' && c != '-') {
            return false;
        } else if (!with_plus && c != '-') {
            return false;
        }
    }

    return digit_cnt == 11;
}

bool check_address(const string& address) {
    if (address.size() < 9) {
        return false;
    }

    if (address[0] != 'g' || !isupper(address[1]) || !isupper(address[2]) || !isupper(address[3])) {
        return false;
    }

    int i = 4;

    while (i < address.size() && isalpha(address[i])) {
        ++i;
    }

    if (i == 4 || address[i] != 'u' || address.size()-i < 4) {
        return false;
    }

    ++i;

    while (i < address.size() && isalpha(address[i])) {
        ++i;
    }

    if (i == address.size() || address[i] != 'd') {
        return false;
    }

    ++i;

    if (i == address.size() || !isdigit(address[i])) {
        return false;
    }

    ++i;
    while (i < address.size() && isdigit(address[i])) {
        ++i;
    }

    return i == address.size();
}

int main() {
    int m;
    cin >> m;

    string name, age, phone, address;
    for (int i = 0; i < m; ++i) {
        cin >> name >> age >> phone >> address;
        bool flag = true;

        if (!check_name(name) || !check_age(age) || !check_phone(phone) || !check_address(address)) {
            flag = false;
        }

        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}