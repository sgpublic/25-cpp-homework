#include <iostream>
using namespace std;

// ----- input start ----- //
class Cat {
public:
    Cat() {
        numOfCats += 1;
    }

    static int numOfCats;

    static int getNumOfCats() {
        return numOfCats;
    }
};
// ----- input end ----- //

int Cat::numOfCats = 0;
int main()
{
    Cat c;
    cout<<"Num:"<<Cat::getNumOfCats()<<endl;
    Cat carr[4];
    cout<<"Num:"<<Cat::getNumOfCats()<<endl;
    return 0;
}