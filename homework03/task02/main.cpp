#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> a;
    int n, m, x = 0;
    cout << "Input n and m:";
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    // ----- input start ----- //
    int index = 0, mod = 1;
    while (a.size() > 1) {
        if (mod % m == 0) {
            a.erase(a.begin() + index);
            mod = 1;
        } else {
            index += 1;
            mod += 1;
        }
        index %= a.size();
    }
    // ----- input end ----- //
    cout << "Result:" << a[0] << endl;
    return 0;
}
