#include <iostream>
#include <string>

extern "C" {
#include "scan_entity.h"
}

extern "int _scan_entity(char * )";

int main() {
  std::string entity_name;
  std::cout << "Enter the entity name: ";
  std::cin >> entity_name;

  int entity_id = _scan_entity(entity_name.c_str());
  if (entity_id == -1) {
    std::cout << "Entity not found." << std::endl;
  } else {
    std::cout << "Entity ID: " << entity_id << std::endl;
  }

  return 0;
}