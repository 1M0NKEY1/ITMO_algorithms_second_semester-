#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

class Solution {
public:
    vector<int> grey_code(int n) {
        if (n == 1) {
            vector<int> arr = {0, 1};
            return arr;
        }
        vector<int> ans(grey_code(n - 1));
        for (int i = ans.size() - 1; i >= 0; i--) {
            ans.push_back((ans[i] | 1 << (n - 1)));
        }
        return ans;
    }
};

//void bin(int n, int k) {
//    char s[] = "\0";
//    string t = "";
//    int e = k - sizeof(itoa(n, s, 2));
//    t.append(e, '0').append(itoa(n, s, 2));
//    cout << t << '\n';
//}

//void bin(int n, int k) {
//    bitset<32> b(n ^ (n >> 1));
//    string t = b.to_string().substr(32 - k);
//    cout << t << '\n';
//}

//void bin(int n, int k) {
//    std::string binary = std::bitset<k>(n).to_string;
//    cout << binary << '\n';
//}

void bin (int n) {
    if (n / 2 != 0) {
        bin(n / 2);
    }
    cout << n % 2 << '\n';
}

int main() {
    Solution object;
    int n;
    vector<int> output;\

    cin >> n;
    output = object.grey_code(n);

    for (int i = 0; i < output.size(); i++) {
//        cout << bitset<n>(output[i]).to_string <<'\n';
        bin(output[i]);
    }
    return 0;
}


