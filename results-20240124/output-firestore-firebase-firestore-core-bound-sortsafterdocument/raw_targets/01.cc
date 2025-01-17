 #include <cstddef>
#include <cstdint>
#include <vector>

#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/model/value_util.h"
#include "Firestore/core/src/nanopb/message_builder.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/sorts/bound.h"
#include "Firestore/core/src/util/status.h"

using firebase::firestore::core::Bound;
using firebase::firestore::core::Document;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::FieldValue;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::types::Comparator;
using firebase::firestore::core::types::Type;
using firebase::firestore::core::util::Status;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::Type;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  // Test Bound::SortsAfterDocument
  try {
    Bound bound;
    std::vector<FieldValue> field_values;
    union anon anon;
    bound.SortsAfterDocument(&bound, &field_values, &anon);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  return 0;
}