#include <stdio.h>
#include <stdlib.h>
#include "roaring/roaring.h"

extern "C" {
#include "roaring/roaring_bitmap.h"
}

int main(int argc, char **argv) {
  roaring_bitmap_t *bitmap = roaring_bitmap_create();
  roaring_bitmap_add(bitmap, 1);
  roaring_bitmap_add(bitmap, 2);
  roaring_bitmap_add(bitmap, 3);

  roaring_bitmap_t *bitmap2 = roaring_bitmap_create();
  roaring_bitmap_add(bitmap2, 3);
  roaring_bitmap_add(bitmap2, 4);
  roaring_bitmap_add(bitmap2, 5);

  roaring_bitmap_or_many(bitmap, 2, bitmap2, NULL);

  for (uint32_t i = 0; i < roaring_bitmap_get_cardinality(bitmap); i++) {
    printf("%d ", roaring_bitmap_inspect(bitmap, i));
  }
  printf("\n");

  roaring_bitmap_free(bitmap);
  roaring_bitmap_free(bitmap2);

  return 0;
}