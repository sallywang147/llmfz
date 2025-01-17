 #include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/query_filter.h"
#include "Firestore/core/src/core/target.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_util.h"
#include "Firestore/core/src/nanopb/message_builder.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/status.h"
#include "Firestore/core/src/util/string_format.h"
#include "Firestore/core/src/util/string_util.h"
#include "Firestore/core/src/util/statusor.h"

using firebase::firestore::core::ArrayContainsFilter;
using firebase::firestore::core::ArrayContainsInFilter;
using firebase::firestore::core::ArrayFilter;
using firebase::firestore::core::ComparisonFilter;
using firebase::firestore::core::FieldFilter;
using firebase::firestore::core::FieldPath;
using firebase::firestore::core::FieldPathFilter;
using firebase::firestore::core::Filter;
using firebase::firestore::core::InFilter;
using firebase::firestore::core::KeyFieldFilter;
using firebase::firestore::core::KeyFieldInFilter;
using firebase::firestore::core::LimitFilter;
using firebase::firestore::core::Nanopb;
using firebase::firestore::core::NanopbMessageBuilder;
using firebase::firestore::core::NanopbWriter;
using firebase::firestore::core::NullFilter;
using firebase::firestore::core::OrderBy;
using firebase::firestore::core::Query;
using firebase::firestore::core::QueryFilter;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::Status;
using firebase::firestore::core::StatusOr;
using firebase::firestore::core::StringFilter;
using firebase::firestore::core::Target;
using firebase::firestore::core::ValueUtil;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ObjectValue;
using firebase::firestore::model::Type;
using firebase::firestore::model::Value;
using firebase::firestore::util::StatusOr;
using firebase::firestore::util::StringFormat;
using firebase::firestore::util::StringUtil;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  // Parse the input into a QueryFilter.
  QueryFilter filter;
  Status status = QueryFilter::Parse(str, &filter);
  if (!status.ok()) {
    return 0;
  }

  // Create a Query with the given filter.
  Query query;
  query.filter = filter;

  // Create a Document with a random key.
  DocumentKey key = DocumentKey::FromPath(ResourcePath::FromString(str));
  Document document(key, ObjectValue::Empty());

  // Check if the document matches the query.
  bool matches = query.MatchesBounds(&document, nullptr);

  return 0;
}