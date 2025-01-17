 #include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_type.h"

using firebase::firestore::core::Query;
using firebase::firestore::core::QueryComparator;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::ValueType;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  Query query;
  // Construct a query with random parameters.
  try {
    ResourcePath path = ResourcePath::FromString(str);
    query = Query(path);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    DocumentKey key = DocumentKey::FromPath(ResourcePath::FromString(str));
    query = Query(key);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    FieldPath field_path = FieldPath::FromString(str);
    query = Query(field_path);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    FieldValue field_value = FieldValue::FromString(str);
    query = Query(field_value);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    QueryComparator comparator = QueryComparator::FromString(str);
    query = Query(comparator);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    ValueType value_type = ValueType::FromString(str);
    query = Query(value_type);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Call the function to fuzz.
  size_t hash = query.Hash(&query);

  return 0;
}