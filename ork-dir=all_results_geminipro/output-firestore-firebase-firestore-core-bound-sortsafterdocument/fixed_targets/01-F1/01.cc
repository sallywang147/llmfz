#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/bound.h"
#include "Firestore/core/src/core/document_view.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/target.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value_util.h"
#include "absl/memory/memory.h"

using firebase::firestore::core::Bound;
using firebase::firestore::core::DocumentView;
using firebase::firestore::core::Query;
using firebase::firestore::core::Target;
using firebase::firestore::model::Document;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::ValueUtil;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<FieldValue> values;
  while (stream.remaining_bytes() > 0) {
    values.push_back(ValueUtil::RandomFieldValue(&stream));
  }
  const ResourcePath path = ResourcePath::FromString(stream.ConsumeRandomLengthString());
  const Document doc = Document(path, values);
  const DocumentView doc_view = DocumentView::Create(doc, /*snapshot_version=*/0);
  const Target target = Target::FromQuery(Query::FromPath(path));
  const Bound bound = Bound::FromDocument(doc_view, target);
  std::vector<FieldValue> field_values;
  bound.SortsAfterDocument(&doc_view, &field_values, nullptr);
  return 0;
}