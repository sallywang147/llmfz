#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "leveldb/db.h"
#include "db/db_impl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::DB* db;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  if (!status.ok()) {
    return 0;
  }

  leveldb::DBImpl* db_impl = reinterpret_cast<leveldb::DBImpl*>(db);
  leveldb::Iterator* iterator = db_impl->TEST_NewInternalIterator();

  FuzzedDataProvider stream(data, size);
  while (iterator->Valid() && stream.remaining_bytes() > 0) {
    leveldb::Slice key = stream.ConsumeRandomLengthString().c_str();
    iterator->Seek(key);
    if (!iterator->Valid()) {
      iterator->SeekToFirst();
    }
  }

  delete iterator;
  delete db;

  return 0;
}