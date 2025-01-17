#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <leveldb/db.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::DB* db;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  if (!status.ok()) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string key = stream.ConsumeRandomLengthString();
  std::string value = stream.ConsumeRandomLengthString();
  db->Put(leveldb::WriteOptions(), key, value);

  leveldb::ReadOptions read_options;
  leveldb::Iterator* it = db->NewIterator(read_options);
  if (!it) {
    delete db;
    return 0;
  }

  it->SeekToFirst();
  while (it->Valid()) {
    leveldb::(leveldb::(anonymous namespace)::DBIter*)(it, &stream);
    it->Next();
  }

  delete it;
  delete db;

  return 0;
}