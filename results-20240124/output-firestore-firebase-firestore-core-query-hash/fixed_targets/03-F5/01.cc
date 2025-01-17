#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/query_snapshot.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/document_set.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/snapshot_version.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/nanopb/message_builder.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/string_format.h"
#include "Firestore/core/src/util/string_util.h"

extern "C" {
#include "Firestore/core/src/core/query_snapshot.h"
}

using firebase::firestore::core::Query;
using firebase::firestore::core::QuerySnapshot;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentSet;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::Type;
using firebase::firestore::nanopb::MessageBuilder;
using firebase::firestore::nanopb::Writer;
using firebase::firestore::util::StringFormat;
using firebase::firestore::util::StringUtil;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  // Test Query::Hash()
  try {
    Query query = Query::FromString(str);
    (void)query.Hash(&query);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test QuerySnapshot::Hash()
  try {
    QuerySnapshot snapshot = QuerySnapshot::FromDocumentSet(
        DocumentSet{}, SnapshotVersion::None(), {});
    (void)snapshot.Hash(&snapshot);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Document::Hash()
  try {
    Document doc = Document::FromMap(ResourcePath::FromString(str),
                                    DocumentKey::Empty(),
                                    FieldValue::MapFieldValue{});
    (void)doc.Hash(&doc);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test DocumentKey::Hash()
  try {
    DocumentKey key = DocumentKey::FromPath(ResourcePath::FromString(str));
    (void)key.Hash(&key);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test FieldPath::Hash()
  try {
    FieldPath field_path = FieldPath::FromString(str);
    (void)field_path.Hash(&field_path);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test FieldValue::Hash()
  try {
    FieldValue value = FieldValue::FromString(str);
    (void)value.Hash(&value);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test ResourcePath::Hash()
  try {
    ResourcePath path = ResourcePath::FromString(str);
    (void)path.Hash(&path);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test SnapshotVersion::Hash()
  try {
    SnapshotVersion version = SnapshotVersion::FromString(str);
    (void)version.Hash(&version);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  return 0;
}