#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/object_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_util.h"

using firebase::firestore::core::Query;
using firebase::firestore::core::QueryComparator;
using firebase::firestore::core::QueryDocumentSnapshot;
using firebase::firestore::core::QueryListener;
using firebase::firestore::core::QuerySnapshot;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::ValueUtil;
using firebase::firestore::model::Document;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ObjectValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::Value;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  ResourcePath path = ResourcePath::FromString(str);

  Query query = Query(path);

  // Test MatchesBounds(Query*, union.anon*) const.
  try {
    QueryDocumentSnapshot snapshot = QueryDocumentSnapshot(Document(path, 0, ObjectValue::FromMap({{"foo", FieldValue::IntegerValue(1)}})),
                                                          QuerySnapshot::New(query, QueryListener::Type::Added));
    QueryComparator comparator(query);
    comparator.MatchesBounds(&query, &snapshot);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  return 0;
}