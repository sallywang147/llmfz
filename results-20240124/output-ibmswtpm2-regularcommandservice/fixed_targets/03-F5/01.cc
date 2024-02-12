#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class CommandService {
public:
    virtual void execute() = 0;
};

class RegularCommandService : public CommandService {
public:
    void execute() override {
        cout << "Regular command service executed." << endl;
    }
};

class SpecialCommandService : public CommandService {
public:
    void execute() override {
        cout << "Special command service executed." << endl;
    }
};

class CommandFactory {
public:
    static CommandService* createCommandService(string type) {
        if (type == "regular") {
            return new RegularCommandService();
        } else if (type == "special") {
            return new SpecialCommandService();
        } else {
            return nullptr;
        }
    }
};

int main() {
    string type = "regular";
    CommandService* commandService = CommandFactory::createCommandService(type);
    commandService->execute();

    return 0;
}