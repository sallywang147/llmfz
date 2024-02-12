#include <iostream>
#include <string>

class RegularCommandService {
public:
    RegularCommandService(int id) : id_(id) {}
    void execute() {
        std::cout << "RegularCommandService::execute() called with id: " << id_ << std::endl;
    }

private:
    int id_;
};

extern "C" {
#include "RegularCommandService.h"
}

int main() {
    RegularCommandService service(1);
    service.execute();
    return 0;
}