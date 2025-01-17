#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "leveldb/db.h"
#include "db/db_impl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  if (!status.ok()) {
    return 0;
  }

  leveldb::DBImpl* db_impl = reinterpret_cast<leveldb::DBImpl*>(db);

  leveldb::Iterator* it = db_impl->TEST_NewInternalIterator();
  if (it == nullptr) {
    delete db;
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  while (provider.remaining_bytes() > 0) {
    switch (provider.ConsumeIntegralInRange<int>(0, 3)) {
      case 0:
        it->SeekToFirst();
        break;
      case 1:
        it->SeekToLast();
        break;
      case 2:
        it->Next();
        break;
      case 3:
        it->Prev();
        break;
    }
  }

  delete it;
  delete db;

  return 0;
}