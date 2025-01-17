#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/query_spec.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_type.h"

extern "C" {
#include "Firestore/core/src/core/query_spec.h"
}

using firebase::firestore::core::Query;
using firebase::firestore::core::QuerySpec;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::ValueType;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  QuerySpec query_spec;
  try {
    query_spec = QuerySpec::FromPath(ResourcePath::FromString(str));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  Query query(query_spec);

  // Test Query::Hash(Query *) const.
  (void)query.Hash(&query);

  // Test Query::Hash() const.
  (void)query.Hash();

  // Test Query::operator==(Query const&) const.
  (void)(query == query);

  // Test Query::operator!=(Query const&) const.
  (void)(query != query);

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22), FieldValue::FromInteger(23));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22), FieldValue::FromInteger(23),
                 FieldValue::FromInteger(24));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22), FieldValue::FromInteger(23),
                 FieldValue::FromInteger(24), FieldValue::FromInteger(25));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22), FieldValue::FromInteger(23),
                 FieldValue::FromInteger(24), FieldValue::FromInteger(25),
                 FieldValue::FromInteger(26));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22), FieldValue::FromInteger(23),
                 FieldValue::FromInteger(24), FieldValue::FromInteger(25),
                 FieldValue::FromInteger(26), FieldValue::FromInteger(27));
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Query::Filter(FieldPath const&, ValueType, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&, FieldValue const&, FieldValue const&,
  //                   FieldValue const&) const.
  try {
    query.Filter(FieldPath::FromString(str), ValueType::kInteger,
                 FieldValue::FromInteger(0), FieldValue::FromInteger(1),
                 FieldValue::FromInteger(2), FieldValue::FromInteger(3),
                 FieldValue::FromInteger(4), FieldValue::FromInteger(5),
                 FieldValue::FromInteger(6), FieldValue::FromInteger(7),
                 FieldValue::FromInteger(8), FieldValue::FromInteger(9),
                 FieldValue::FromInteger(10), FieldValue::FromInteger(11),
                 FieldValue::FromInteger(12), FieldValue::FromInteger(13),
                 FieldValue::FromInteger(14), FieldValue::FromInteger(15),
                 FieldValue::FromInteger(16), FieldValue::FromInteger(17),
                 FieldValue::FromInteger(18), FieldValue::FromInteger(19),
                 FieldValue::FromInteger(20), FieldValue::FromInteger(21),
                 FieldValue::FromInteger(22), FieldValue::FromInteger(23),
                 FieldValue::FromInteger(24), FieldValue::FromInteger(25),
                 FieldValue::FromInteger(26), FieldValue::FromInteger(27),
                 FieldValue::FromInteger(28));
  } catch (...) {
    // Ignore caught errors and assertions.
  }
}