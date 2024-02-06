#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "cmark.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the fuzzing data to it.
  FILE *temp_file = tmpfile();
  if (!temp_file) {
    return 0;
  }
  fwrite(data, 1, size, temp_file);
  rewind(temp_file);

  // Parse the file using cmark.
  cmark_node *root_node = cmark_parse_file(temp_file, CMARK_OPT_DEFAULT);

  if (root_node) {
    // Render the parsed document to HTML and free the result.
    char *html = cmark_render_html(root_node, CMARK_OPT_DEFAULT, NULL);
    free(html);

    // Free the parsed document.
    cmark_node_free(root_node);
  }

  // Close the temporary file.
  fclose(temp_file);

  return 0;
}