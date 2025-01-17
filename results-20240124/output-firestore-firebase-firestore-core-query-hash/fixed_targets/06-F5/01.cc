#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "Firestore/core/src/query.h"
#include "Firestore/core/src/types.h"
}

using firebase::firestore::core::Query;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  Query::CollectionGroup collection_group =
      Query::CollectionGroup::FromPath(str);
  Query::Order order = Query::Order::FromPath(str);
  Query::Filter filter = Query::Filter::FromPath(str);

  Query query = Query::FromPath(str);
  Query query2 = Query::FromPath(str);
  query.Hash(&query2);

  return 0;
}