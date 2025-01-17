#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/query.h"
#include "Firestore/core/src/types/types.h"

using firebase::firestore::core::Query;
using firebase::firestore::core::QueryComparator;
using firebase::firestore::core::QueryComparator::Bound;
using firebase::firestore::core::QueryComparator::Direction;
using firebase::firestore::core::QueryComparator::Field;
using firebase::firestore::core::QueryComparator::Type;
using firebase::firestore::core::QueryComparator::Value;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKey::ComparisonResult;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::TypeOrder;
using firebase::firestore::type::Type;

#ifdef __cplusplus
extern "C" {
#endif
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  Query query;
  query.SetCollectionGroup("collectionGroup");
  query.SetDirection(Direction::ASCENDING);
  query.AddFieldFilter(FieldPath::FromDotSeparatedString("field1"), Type::STRING,
                       TypeOrder::ASCENDING, FieldValue::FromString("value1"));

  union.anon anon;
  // Set the first field.
  anon.field.field = Field{FieldPath::FromDotSeparatedString("field1"), Type::STRING};
  // Set the second field.
  anon.field.value = Value{FieldValue::FromString("value2")};

  // Test MatchesBounds.
  (void)query.MatchesBounds(&query, &anon);

  // Test MatchesBounds with a different direction.
  query.SetDirection(Direction::DESCENDING);
  (void)query.MatchesBounds(&query, &anon);

  // Test MatchesBounds with a different type.
  query.SetDirection(Direction::ASCENDING);
  anon.field.value = Value{FieldValue::FromInteger(1)};
  (void)query.MatchesBounds(&query, &anon);

  // Test MatchesBounds with a different field.
  anon.field.field = Field{FieldPath::FromDotSeparatedString("field2"), Type::STRING};
  (void)query.MatchesBounds(&query, &anon);

  // Test MatchesBounds with a different field and type.
  anon.field.field = Field{FieldPath::FromDotSeparatedString("field2"), Type::INTEGER};
  (void)query.MatchesBounds(&query, &anon);

  return 0;
}
#ifdef __cplusplus
}  // extern "C"
#endif