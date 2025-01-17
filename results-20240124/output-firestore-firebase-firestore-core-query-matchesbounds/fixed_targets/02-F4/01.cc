#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/query.h"
#include "Firestore/core/src/types.h"

using firebase::firestore::core::Query;
using firebase::firestore::core::types::OrderDirection;
using firebase::firestore::core::types::OrderBy;
using firebase::firestore::core::types::QueryComparator;
using firebase::firestore::core::types::TargetId;

extern "C" {
#include "Firestore/core/src/query.h"
#include "Firestore/core/src/types.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  Query::Bound bound;
  (void)bound.Decode(str);

  std::vector<OrderBy> order_bys;
  order_bys.emplace_back(OrderBy::Field("foo"));
  order_bys.emplace_back(OrderBy::Field("bar"));
  Query::Comparator comparator(order_bys);

  Query::QueryComparator query_comparator(comparator);
  query_comparator.MatchesBounds(nullptr, &bound);

  return 0;
}