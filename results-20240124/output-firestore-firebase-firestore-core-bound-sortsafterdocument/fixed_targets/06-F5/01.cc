#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/bound.h"
#include "Firestore/core/src/core/document_key.h"
#include "Firestore/core/src/core/document_key_comparator.h"
#include "Firestore/core/src/core/order_by.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/target.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"

extern "C" {
#include "Firestore/core/src/core/document_key.h"
}

using firebase::firestore::core::Bound;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::DocumentKeyComparator;
using firebase::firestore::core::OrderBy;
using firebase::firestore::core::Query;
using firebase::firestore::core::Target;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  DocumentKey document_key = DocumentKey::FromPath(ResourcePath::FromString(str));

  // Test Bound::SortsAfterDocument(Bound *, std::vector *, union.anon *) const.
  std::vector<OrderBy> order_bys;
  union.anon anon;
  Bound bound(FieldValue::Null(), false, false, order_bys);
  bound.SortsAfterDocument(&document_key, &order_bys, &anon);

  return 0;
}