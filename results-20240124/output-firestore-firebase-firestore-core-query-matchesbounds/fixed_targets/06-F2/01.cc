#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_util.h"

extern "C" {
#include "Firestore/core/src/model/field_value.h"
}

using firebase::firestore::core::Query;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::ValueUtil;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  // Parse the input string as a DocumentKey.
  DocumentKey key;
  try {
    key = DocumentKey::FromPathString(str);
  } catch (...) {
    // Ignore caught errors and assertions.
    return 0;
  }

  // Parse the input string as a FieldValue.
  FieldValue value;
  try {
    value = ValueUtil::ParseFieldValue(str);
  } catch (...) {
    // Ignore caught errors and assertions.
    return 0;
  }

  // Create a Query object with a bound on the given key and value.
  Query query = Query::New(ResourcePath::EmptyPath())
                    .Where(key.path(), Query::Operator::EQUAL, value);

  // Create a Document object with the given key and value.
  Document document = Document::New(key, value, Document::DocumentState::kLocal);

  // Check if the document matches the query bounds.
  bool matches = query.MatchesBounds(&document);

  return 0;
}