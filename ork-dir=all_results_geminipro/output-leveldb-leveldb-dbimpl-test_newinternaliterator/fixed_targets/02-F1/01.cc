#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/status.h"

extern "C" {
#include "leveldb/c.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a DBImpl object.
  leveldb::DBImpl *db_impl = new leveldb::DBImpl();

  // Create a FuzzedDataProvider object.
  FuzzedDataProvider stream(data, size);

  // Call the TEST_NewInternalIterator method.
  leveldb::Iterator *iterator =
      db_impl->TEST_NewInternalIterator(nullptr /* db */);

  // Delete the DBImpl object.
  delete db_impl;

  // Delete the iterator object.
  delete iterator;

  return 0;
}