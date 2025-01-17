#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/bound.h"
#include "Firestore/core/src/core/document_key.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/field_value_array.h"
#include "Firestore/core/src/model/field_value_map.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_util.h"
#include "Firestore/core/src/nanopb/message_builder.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/status.h"
#include "Firestore/core/src/util/statusor.h"

using firebase::firestore::core::Bound;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::DocumentKeyComparator;
using firebase::firestore::core::FieldPath;
using firebase::firestore::core::FieldValue;
using firebase::firestore::core::FieldValueArray;
using firebase::firestore::core::FieldValueMap;
using firebase::firestore::core::Nanopb;
using firebase::firestore::core::Query;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::ValueUtil;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::FieldValueArray;
using firebase::firestore::model::FieldValueMap;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::ValueUtil;
using firebase::firestore::util::Status;
using firebase::firestore::util::StatusOr;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate a document key.
  const std::string key_str =
      provider.ConsumeRemainingBytesAsString();
  DocumentKey key = DocumentKey::FromPathString(key_str);

  // Generate a document.
  FieldValueMap fields;
  while (provider.remaining_bytes() > 0) {
    const std::string field_name = provider.ConsumeRemainingBytesAsString();
    FieldValue value;
    if (provider.ConsumeBool()) {
      value = FieldValue::IntegerValue(provider.ConsumeIntegral<int32_t>());
    } else {
      value = FieldValue::StringValue(provider.ConsumeBytesAsString());
    }
    fields[field_name] = value;
  }
  Document document(key, fields);

  // Generate a bound.
  Bound bound = Bound::FromDocument(document);

  // Generate a vector of documents.
  std::vector<Document> documents;
  while (provider.remaining_bytes() > 0) {
    const std::string key_str =
        provider.ConsumeRemainingBytesAsString();
    DocumentKey key = DocumentKey::FromPathString(key_str);
    FieldValueMap fields;
    while (provider.remaining_bytes() > 0) {
      const std::string field_name = provider.ConsumeRemainingBytesAsString();
      FieldValue value;
      if (provider.ConsumeBool()) {
        value = FieldValue::IntegerValue(provider.ConsumeIntegral<int32_t>());
      } else {
        value = FieldValue::StringValue(provider.ConsumeBytesAsString());
      }
      fields[field_name] = value;
    }
    documents.push_back(Document(key, fields));
  }

  // Call the function.
  bool result = bound.SortsAfterDocument(&document, &documents, nullptr);

  return 0;
}