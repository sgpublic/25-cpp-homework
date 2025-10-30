#include <iostream>
#include <string>
using namespace std;

class Object {
public:
    Object() {
        cout << "Constructing Object!" << endl;
    }

    ~Object() {
        cout << "Destructing Object!" << endl;
    }

    void getInfo() {
        cout << "Input weight:";
        cin >> weight;
    }

    void showInfo() {
        cout << "Weight:" << weight << endl;
    }

private:
    int weight;
};

// ----- input start ----- //
class Box : public Object {
private:
    int height, width;

public:
    Box() {
        cout << "Constructing Box!" << endl;
    }

    ~Box() {
        cout << "Destructing Box!" << endl;
    }

    void getInfo() {
        Object::getInfo();
        cout << "Input height and width:";
        cin >> height >> width;
    }

    void showInfo() {
        Object::showInfo();
        cout << "Height and width:" << height << "," << width << endl;
    }
};
// ----- input end ----- //
int main() {
    Box box;
    box.getInfo();
    box.showInfo();
    return 0;
}
