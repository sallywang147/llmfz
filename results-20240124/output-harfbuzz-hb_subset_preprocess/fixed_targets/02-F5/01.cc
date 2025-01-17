#include <hb.h>
#include <hb-ot.h>

int main() {
  hb_face_t *face = hb_face_create("Roboto-Regular.ttf", NULL);
  hb_subset_preprocess(face, hb_subset_input_t());
  hb_face_destroy(face);
  return 0;
}