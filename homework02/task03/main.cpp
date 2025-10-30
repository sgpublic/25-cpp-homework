#include <iostream>
#include <string>
using namespace std;

class person {
public:
    person() {
        cout << "Input id:";
        cin >> id;
        cout << "Input name:";
        cin >> name;
    }

    void display() {
        cout << "Id:" << id << endl;
        cout << "Name:" << name << endl;
    }

private:
    string id;
    string name;
};


// ----- input start ----- //
class student : public person {
private:
    string clazz;
    int score;
public:
    student() {
        cout << "Input class:";
        cin >> clazz;
        cout << "Input score:";
        cin >> score;
    }

    void display() {
        cout << "Student's info:" << endl;
        person::display();
        cout << "Class:" << clazz << endl;
        cout << "Score:" << score << endl;
    }
};

class teacher : public person {
private:
    string title;
    string dept;
public:
    teacher() {
        cout << "Input title:";
        cin >> title;
        cout << "Input department:";
        cin >> dept;
    }

    void display() {
        cout << "Teacher's info:" << endl;
        person::display();
        cout << "Title:" << title << endl;
        cout << "Department:" << dept << endl;
    }
};
// ----- input end ----- //


int main() {
    student stu;
    teacher tea;
    stu.display();
    tea.display();
    return 0;
}
