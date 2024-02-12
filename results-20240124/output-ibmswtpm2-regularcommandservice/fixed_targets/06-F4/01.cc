#include <iostream>
#include <vector>

using namespace std;

class RegularCommandService {
public:
    RegularCommandService(int* n) {
        *n = 10;
    }
};

int main() {
    int n;
    RegularCommandService rcs(&n);
    cout << n << endl;
    return 0;
}