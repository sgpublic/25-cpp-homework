#include <iostream>
#include <string>
using namespace std;
#include <set>

int main() {
    multiset<string> arr;
    string s;
    cin >> s;
    while (s != "#") {
        int times = 0;
        // ----- input start ----- //
        times = arr.count(s);
        // ----- input end ----- //
        cout << "times:" << times << endl;
        arr.insert(s);
        cin >> s;
    }
}
