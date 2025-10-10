#include <iostream>

class Dog {
private:
    int age;
    int weight;

public:
    Dog(int age, int weight) {
        this->age = age;
        this->weight = weight;
    }

    int getWeight() {
        return weight;
    }
    int getAge() {
        return age;
    }
};

int main() {
    std::cout << "Input Age and Weight:";
    int age, weight;
    std::cin >> age >> weight;
    Dog* dog = new Dog(age, weight);
    std::cout << "Dog Age:" << dog->getAge() << " years" << std::endl;
    std::cout << "Dog Weight:" << dog->getWeight() << "kg" << std::endl;
    delete dog;
    return 0;
}