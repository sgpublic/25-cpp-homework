#include <iostream>
using namespace std;

class Date {
public:
    Date() {
        cout << "Input Date:";
        cin >> y >> m >> d;
    }

    int beLeapYear() {
        return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
    }

    void addOneDay() {
        // ----- input start ----- //
        int dayOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dayOfMonth[m-1] > d || (m == 2 && beLeapYear() != 0)) {
            d += 1;
            return;
        }
        d = 1;
        if (m < 12) {
            m += 1;
            return;
        }
        m = 1;
        y += 1;
        // ----- input end ----- //
    }

    void showDate() {
        cout << y << "-" << m << "-" << d << endl;
    }

private:
    int y, m, d;
};

int main() {
    Date d;
    d.showDate();
    d.addOneDay();
    d.showDate();
}

