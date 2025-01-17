#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_type.h"
#include "Firestore/core/src/util/status.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str_ptr = reinterpret_cast<const char *>(data);
  std::string str{str_ptr, size};
  firebase::firestore::core::ResourcePath path =
      firebase::firestore::core::ResourcePath::FromString(str);

  firebase::firestore::core::FieldValue field_value =
      firebase::firestore::core::FieldValue::FromInteger(0);

  firebase::firestore::core::Query query;
  firebase::firestore::core::Query::Bound bound;
  bound.type = firebase::firestore::core::Query::BoundType::kEqual;
  bound.value = field_value;
  query.AddFilter(firebase::firestore::core::FieldFilter(
      path, firebase::firestore::core::Operator::kEqual, field_value));

  firebase::firestore::core::Document doc(
      path,
      firebase::firestore::core::DocumentState::kLocalDocument,
      firebase::firestore::core::SnapshotVersion::FromTimestamp(
          firebase::firestore::core::Timestamp::Now()),
      firebase::firestore::core::Value::Array(
          {firebase::firestore::core::FieldValue::FromInteger(0)}));

  bool result = query.MatchesBounds(&doc, &bound);

  return static_cast<int>(result);
}
}