#include <iostream>
#include <vector>

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructor called" << std::endl; }
    ~MyClass() { std::cout << "MyClass destructor called" << std::endl; }
};

int main() {
    std::vector<MyClass> myVector;
    myVector.push_back(MyClass());

    return 0;
}