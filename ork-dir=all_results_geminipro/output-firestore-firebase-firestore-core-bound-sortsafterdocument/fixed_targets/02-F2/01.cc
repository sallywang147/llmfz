#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/model/bound.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/unknown_document.h"
#include "Firestore/core/src/model/value_util.h"
#include "absl/types/optional.h"

using firebase::firestore::core::Bound;
using firebase::firestore::core::Document;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::FieldValue;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::UnknownDocument;
using firebase::firestore::core::ValueUtil;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Read an array of fields.
  std::vector<FieldValue> fields;
  while (stream.remaining_bytes() > 0) {
    absl::optional<FieldValue> field = ValueUtil::ParseFieldValue(stream);
    if (field) {
      fields.push_back(*field);
    }
  }

  // Read a document key.
  std::string key_string = stream.ConsumeRandomLengthString();
  DocumentKey key = DocumentKey::FromPathString(key_string);

  // Create an UnknownDocument.
  UnknownDocument document(key, std::move(fields));

  // Read a Bound.
  Bound bound = Bound::FromDocument(document);

  // Read a vector of DocumentKeys.
  std::vector<DocumentKey> keys;
  while (stream.remaining_bytes() > 0) {
    std::string key_string = stream.ConsumeRandomLengthString();
    DocumentKey key = DocumentKey::FromPathString(key_string);
    keys.push_back(key);
  }

  // Create an anonymous union.
  union anon {
    bool b;
    int i;
    double d;
  } anon_value;

  // Call the function.
  bool result = bound.SortsAfterDocumentKeys(&document, keys, &anon_value);

  // Ignore the result.
  (void)result;
  return 0;
}