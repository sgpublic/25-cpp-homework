#include <cmath>
#include <iostream>

const double PI = 3.14;

class Shape {
private:
    const std::string name;
protected:
    double r;
    Shape(std::string name): name(name) {}
public:
    virtual double surfaceArea() = 0;
    virtual double volume() = 0;

    void print() {
        std::cout << "The area of the " << name << ":" << surfaceArea() << std::endl;
        std::cout << "The volume of the " << name << ":" << volume() << std::endl;
    }
};

class Sphere: public Shape {
public:
    Sphere(): Shape("sphere") {
        std::cout << "Input the radius of the sphere:";
        std::cin >> r;
    }

    double surfaceArea() {
        return 4.0 * PI * r * r;
    }

    double volume() {
        return 4.0 / 3.0 * PI * r * r * r;
    }
};

class Cylinder: public Shape {
private:
    double h;
public:
    Cylinder(): Shape("cylinder") {
        std::cout << "Input the radius and height of the cylinder:";
        std::cin >> r >> h;
    }

    double surfaceArea() {
        return PI * r * 2.0 * (r + h);
    }

    double volume() {
        return PI * r * r * h;
    }
};

class Cone: public Shape {
private:
    double h;
public:
    Cone(): Shape("cone")  {
        std::cout << "Input the radius and height of the cone:";
        std::cin >> r >> h;
    }

    double surfaceArea() {
        return PI * r * (r + std::sqrt(r * r + h * h));
    }

    double volume() {
        return 1.0 / 3.0 * PI * r * r * h;
    }
};

int main() {
    Sphere sphere;
    Cylinder cylinder;
    Cone cone;
    sphere.print();
    cylinder.print();
    cone.print();
}
