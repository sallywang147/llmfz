#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "Firestore/core/src/model/document_comparator.h"
}
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/snapshot_version.h"
#include "Firestore/core/src/model/types.h"

using firebase::firestore::core::Query;
using firebase::firestore::model::DocumentComparator;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::Type;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  // Test Query::Comparator(DocumentComparator*, Query*) const.
  try {
    Query query;
    DocumentComparator comparator;
    query.Comparator(&comparator, &query);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  return 0;
}