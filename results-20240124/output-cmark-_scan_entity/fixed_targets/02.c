#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scan_entity.h"
}

int main() {
  int n;
  printf("Enter the number of entities: ");
  scanf("%d", &n);

  Entity *entities = (Entity *)malloc(sizeof(Entity) * n);

  for (int i = 0; i < n; i++) {
    scan_entity(&entities[i]);
  }

  for (int i = 0; i < n; i++) {
    printf("Entity %d: %s\n", i + 1, entities[i].name);
  }

  free(entities);

  return 0;
}