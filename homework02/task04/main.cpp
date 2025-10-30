#include <iostream>
using namespace std;

class Employee {
public:
    Employee(string id, string name) : id(id), name(name) {
    }

    void display() {
        cout << "ID:" << id << endl;
        cout << "Name:" << name << endl;
    }

protected:
    string id, name;
};

// ----- input start ----- //
class SampleEmployee: public Employee {
protected:
    float salary;
    SampleEmployee(string id, string name, float salary) :
    Employee(id, name),
    salary(salary) {}
public:
    void display() {
        Employee::display();
        cout << "Salary:" << salary << endl;
    }
};
class Sales: virtual public SampleEmployee {
public:
    Sales(string id, string name, float sale) :
    SampleEmployee(id, name, sale*0.1f) {}
};
class Manager: virtual public SampleEmployee {
public:
    Manager(string id, string name) :
    SampleEmployee(id, name, 8000) {}
};
class SalesManager: public Sales, public Manager {
public:
    SalesManager(string id, string name, float sale) :
    SampleEmployee(id, name, 5000+sale*0.05f),
    Sales(id, name, sale),
    Manager(id, name) {}
};
// ----- input end ----- //

int main() {
    string id, name;
    float sale;
    cout << "Input id name and sale:" << endl;
    cin >> id >> name >> sale;
    if (sale < 0) {
        cout << "Input Error!" << endl;
        return 0;
    }
    SalesManager sm(id, name, sale);
    sm.display();
    return 0;
}
