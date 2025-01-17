#include <iostream>
#include <string>

extern "C" {
#include "RegularCommandService.h"
}

using namespace std;

class RegularCommandServiceImpl : public RegularCommandService {
public:
    void execute() override {
        cout << "Regular command executed!" << endl;
    }
};

int main() {
    RegularCommandServiceImpl service;
    service.execute();
    return 0;
}