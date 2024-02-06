#include <libexif/exif-data.h>
#include <libexif/exif-loader.h>
#include <stddef.h>
#include <stdlib.h>

/* Extract all MakerNote tags */
static void mnote_dump(ExifData *data) {
  ExifMnoteData *mn = exif_data_get_mnote_data(data);
  if (mn) {
    int num = exif_mnote_data_count(mn);

    /* Loop through all MakerNote tags */
    for (int i = 0; i < num; ++i) {
      char buf[1024];
      exif_mnote_data_get_value(mn, i, buf, sizeof(buf));
    }
  }
}

static void dump_value(ExifEntry *entry, void *user_data) {
  char buf[1024];
  exif_entry_get_value(entry, buf, sizeof(buf));
}

static void data_func(ExifContent *content, void *user_data) { exif_content_foreach_entry(content, dump_value, NULL); }

/* This is like exif_data_dump but without writing to stdout */
static void data_dump(ExifData *data) { exif_data_foreach_content(data, data_func, NULL); }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Parse tags using (ultimately) exif_data_load_data()
  ExifData *image = exif_data_new_from_data(data, size);
  if (image) {
    // Exercise the EXIF tag manipulation code
    exif_data_get_mnote_data(image);
    data_dump(image);
    mnote_dump(image);
    unsigned char *buf;
    unsigned int sz;
    exif_data_save_data(image, &buf, &sz);
    free(buf);
    exif_data_fix(image);
    exif_data_dump(image);
    exif_data_unref(image);
  }

  return 0;
}