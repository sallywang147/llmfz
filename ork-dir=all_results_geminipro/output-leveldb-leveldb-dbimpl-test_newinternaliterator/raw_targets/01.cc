#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/status.h"

namespace {

// Deletes the database directory when going out of scope.
class AutoDbDeleter {
public:
  static constexpr char kDbPath[] = "/tmp/testdb";

  AutoDbDeleter() = default;

  AutoDbDeleter(const AutoDbDeleter &) = delete;
  AutoDbDeleter &operator=(const AutoDbDeleter &) = delete;

  ~AutoDbDeleter() { std::__fs::filesystem::remove_all(kDbPath); }
};

// static
constexpr char AutoDbDeleter::kDbPath[];

// Returns nullptr (a falsey unique_ptr) if opening fails.
std::unique_ptr<leveldb::DB> OpenDB() {
  leveldb::Options options;
  options.create_if_missing = true;

  leveldb::DB *db_ptr;
  leveldb::Status status = leveldb::DB::Open(options, AutoDbDeleter::kDbPath, &db_ptr);
  if (!status.ok())
    return nullptr;

  return std::unique_ptr<leveldb::DB>(db_ptr);
}

} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Must occur before `db` so the deletion doesn't happen while the DB is open.
  AutoDbDeleter db_deleter;

  std::unique_ptr<leveldb::DB> db = OpenDB();
  if (!db.get())
    return 0;

  FuzzedDataProvider fuzzed_data(data, size);
  leveldb::DBImpl *db_impl = reinterpret_cast<leveldb::DBImpl *>(db.get());
  leveldb::Iterator *it = db_impl->TEST_NewInternalIterator(db_impl);
  delete it;

  return 0;
}