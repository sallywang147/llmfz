#include <iostream>
#include <string>

using namespace std;

class RegularCommandService {
public:
    void execute() {
        cout << "Regular command executed." << endl;
    }
};

int main() {
    RegularCommandService service;
    service.execute();
    return 0;
}