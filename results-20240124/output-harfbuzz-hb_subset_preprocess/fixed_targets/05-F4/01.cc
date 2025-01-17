#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <hb.h>

#ifdef __cplusplus
}
#endif

int main() {
  hb_document_t *doc = hb_document_create();
  hb_face_t *face = hb_face_create("Roboto-Regular.ttf", 0);
  hb_font_t *font = hb_font_create(face);
  hb_subset_preprocess(font);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_document_destroy(doc);
  return 0;
}