#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char test_file[] = "libfuzzer.xml";

  FILE *fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  char *open_entity = "<!ENTITY foo \"";
  char *close_entity = "\">";
  XML_ExternalEntityParserCreate(parser, open_entity, close_entity);

  fp = fopen(test_file, "r");
  if (!fp)
    return 0;
  while (!feof(fp)) {
    char buf[4096];
    size_t len = fread(buf, 1, sizeof(buf), fp);
    if (len < 0)
      break;
    XML_Parse(parser, buf, len, feof(fp));
  }
  fclose(fp);
  XML_ParserFree(parser);

  remove(test_file);
  return 0;
}