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
  // Create a DB object.
  leveldb::DB *db = leveldb::DB::Open(leveldb::Options(), "/tmp/leveldb_fuzzer");

  // Create a FuzzedDataProvider object.
  FuzzedDataProvider stream(data, size);

  // Call the TEST_NewInternalIterator method.
  leveldb::Iterator *iterator = db->TEST_NewInternalIterator(
      nullptr /* db */, stream.ConsumeRandomLengthString(1024));

  // Delete the iterator object.
  delete iterator;

  // Delete the DB object.
  delete db;

  return 0;
}