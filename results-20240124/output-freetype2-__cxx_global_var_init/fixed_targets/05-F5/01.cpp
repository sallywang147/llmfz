#include <iostream>
#include <vector>

extern "C" {
#include <stddef.h>
#include <stdint.h>
}

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructor called" << std::endl; }
    ~MyClass() { std::cout << "MyClass destructor called" << std::endl; }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Call the global variable initializer
    __cxx_global_var_init();

    std::vector<MyClass> myVector;
    myVector.push_back(MyClass());

    return 0;
}

int main() {
    return 0;
}