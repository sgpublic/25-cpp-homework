#include <iostream>
using namespace std;
// ----- input start ----- //
class X;
// ----- input end ----- //
class Y
{
public:
    void g(X &x);
};

class Z
{
public:
    void f(X &x);
};

class X
{
public:
    X(int i):i(i){}
    friend void Y::g(X &x);
    friend class Z;
    friend void h(X &x);
    void print()
    {
        cout<<i;
    }
private:
    int i;
};

// ----- input start ----- //
void Y::g(X &x) {
    x.i += 1;
}

void Z::f(X &x) {
    x.i += 5;
}

void h(X &x) {
    x.i += 10;
}
// ----- input end ----- //

int main()
{
    int a;
    cin>>a;
    X x(a);
    Y y;
    Z z;
    y.g(x);
    z.f(x);
    h(x);
    x.print();
}
