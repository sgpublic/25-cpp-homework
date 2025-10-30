# 修改下面的4个类，添加析构函数

## 问题描述

修改下面的4个类，添加析构函数，在析构函数中输出各私有数据成员的值。并分析结果。

修改后程序的输出结果为：

```
Constructing B2.2
Constructing B1.1
Constructing B3.3
Constructing A.4
1
2
4
Destructing A.4
Destructing B3.3
Destructing B1.1
Destructing B2.2
```

待修改的程序源代码如下：

```c++
#include <iostream>

using namespace std;

class B1 {
public:
    B1(int i) {
        b1 = i;

        cout << "Constructing B1." << b1 << endl;
    }

    void print() { cout << b1 << endl; }

private:
    int b1;
};


class B2 {
public:
    B2(int i) {
        b2 = i;

        cout << "Constructing B2." << b2 << endl;
    }

    void print() { cout << b2 << endl; }

private:
    int b2;
};


class B3 {
public:
    B3(int i) {
        b3 = i;

        cout << "Constructing B3." << b3 << endl;
    }

    int getb3() { return b3; }

private:
    int b3;
};

class A : public B2, public B1 {
public:
    A(int i, int j, int k, int l) : B1(i), B2(j), bb(k) {
        a = l;

        cout << "Constructing A." << a << endl;
    }

    void print() {
        B1::print();

        B2::print();

        cout << a << endl;
    }

private:
    int a;

    B3 bb;
};


int main() {
    A aa(1, 2, 3, 4);

    aa.print();

    return 0;
}
```