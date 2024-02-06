#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_type.h"
#include "Firestore/core/src/query/query.h"
#include "Firestore/core/src/query/query_builder.h"
#include "Firestore/core/src/query/query_comparators.h"
#include "Firestore/core/src/util/statusor.h"

using firebase::firestore::core::Document;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::FieldPath;
using firebase::firestore::core::FieldValue;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::ValueType;
using firebase::firestore::core::query::Query;
using firebase::firestore::core::query::QueryBuilder;
using firebase::firestore::core::query::QueryComparators;
using firebase::firestore::core::util::StatusOr;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str_ptr = reinterpret_cast<const char *>(data);
  std::string str{str_ptr, size};
  leveldb::Slice slice = firebase::firestore::local::MakeSlice(str);

  // Test Query::MatchesBounds(Query*, anon) which calls MakeSlice(std::string).
  try {
    firebase::firestore::core::query::Query query;
    firebase::firestore::core::query::Query::MatchesBounds(&query, &slice);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test QueryBuilder methods.
  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryBuilder::NewQuery(ResourcePath::FromString(str), slice,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending,
                           QueryComparators::Direction::kAscending);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {