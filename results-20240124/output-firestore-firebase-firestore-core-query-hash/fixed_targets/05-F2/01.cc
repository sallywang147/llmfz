#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/query/query.h"
#include "Firestore/core/src/query/query_builder.h"

using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::FieldPath;
using firebase::firestore::core::FieldValue;
using firebase::firestore::core::Query;
using firebase::firestore::core::QueryBuilder;
using firebase::firestore::core::ResourcePath;
using firebase::firestore::core::TargetId;

extern "C" {
#include "Firestore/core/src/model/field_value.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<std::string> path_segments;
  while (stream.remaining_bytes() > 0) {
    path_segments.push_back(stream.ConsumeRemainingBytesAsString());
  }
  ResourcePath path = ResourcePath::FromSegments(path_segments);

  // Generate a random document key.
  DocumentKey key = DocumentKey(path, stream.ConsumeIntegral<int64_t>());

  // Generate a random field path.
  std::vector<std::string> field_path_segments;
  while (stream.remaining_bytes() > 0) {
    field_path_segments.push_back(stream.ConsumeRemainingBytesAsString());
  }
  FieldPath field_path = FieldPath::FromSegments(field_path_segments);

  // Generate a random field value.
  FieldValue field_value = FieldValue::FromDouble(stream.ConsumeFloatingPoint<double>());

  // Generate a random target ID.
  TargetId target_id = TargetId(stream.ConsumeIntegral<int64_t>());

  // Generate a random query.
  Query query = QueryBuilder::NewQuery(std::move(path))
                    .WhereEqualTo(std::move(field_path), std::move(field_value))
                    .Build();

  // Hash the query.
  size_t hash = query.Hash(&query);

  // Return the hash.
  return hash;
}
}  // extern "C"