#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/query_filter.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value.h"

using firebase::firestore::core::FieldFilter;
using firebase::firestore::core::InequalityFilter;
using firebase::firestore::core::Query;
using firebase::firestore::core::QueryFilter;
using firebase::firestore::core::Value;
using firebase::firestore::model::Document;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;

extern "C" {
#include "Firestore/core/src/core/query_filter.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  ResourcePath path = ResourcePath::FromString(str);
  Document doc = Document(path, {{"foo", Value::String("bar")}});

  Query query;
  query.AddFilter(FieldFilter::Create(
      InequalityFilter::Operator::kGreaterThan, "foo", FieldValue::Integer(1)));

  query.MatchesBounds(&doc, nullptr);
  return 0;
}