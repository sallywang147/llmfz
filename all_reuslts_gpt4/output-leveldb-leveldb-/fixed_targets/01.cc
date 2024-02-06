#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "leveldb/db.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  leveldb::DB* db = nullptr;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  if (!status.ok()) {
    return 0;
  }

  leveldb::ReadOptions read_options;
  leveldb::Iterator* it = db->NewIterator(read_options);

  FuzzedDataProvider provider(data, size);

  // Call the function to fuzz
  leveldb::(leveldb::(anonymous namespace)::DBIter(it, &provider);

  delete it;
  delete db;

  return 0;
}