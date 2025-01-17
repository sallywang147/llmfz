#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>

#include "cil.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  cil_db_t* db = cil_db_new();
  if (!db) {
    return 0;
  }

  // Generate random CIL AST.
  cil_tree_t* tree = nullptr;
  cil_parse_tree(provider.ConsumeBytesAsString(size).c_str(), &tree, db);

  // Generate random output file.
  char* filename = provider.ConsumeRandomLengthString().c_str();
  FILE* out = fopen(filename, "w");
  if (!out) {
    cil_db_free(db);
    return 0;
  }

  // Write CIL AST to the output file.
  cil_write_resolve_ast(out, db);

  // Clean up.
  fclose(out);
  cil_db_free(db);
  cil_tree_free(tree);

  return 0;
}