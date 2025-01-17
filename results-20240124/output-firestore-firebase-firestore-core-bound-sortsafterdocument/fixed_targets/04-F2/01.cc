 #include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/bound.h"
#include "Firestore/core/src/core/document_key.h"
#include "Firestore/core/src/core/document_snapshot.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/query_snapshot.h"
#include "Firestore/core/src/core/target.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/snapshot_version.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/model/value_util.h"
#include "Firestore/core/src/nanopb/message_builder.h"
#include "Firestore/core/src/nanopb/reader.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/status.h"
#include "Firestore/core/src/util/statusor.h"
#include "Firestore/core/src/util/string_format.h"
#include "Firestore/core/src/util/string_util.h"
#include "Firestore/core/src/util/to_string.h"
#include "Firestore/core/src/util/type_traits.h"
#include "Firestore/core/src/util/version.h"
#include "Firestore/core/src/util/writer.h"
#include "Firestore/core/src/util/x_ray_string.h"
#include "Firestore/core/src/util/xxhash.h"
#include "Firestore/core/variant.h"
#include "Firestore/core/write_batch.h"
#include "Firestore/core/write_batch_impl.h"
#include "Firestore/core/write_stream.h"
#include "Firestore/core/write_stream_impl.h"
#include "Firestore/core/write_stream_token_manager.h"

extern "C" {
#include "Firestore/core/src/core/document_key.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/target.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/snapshot_version.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/model/value_util.h"
#include "Firestore/core/src/nanopb/message_builder.h"
#include "Firestore/core/src/nanopb/reader.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/status.h"
#include "Firestore/core/src/util/statusor.h"
#include "Firestore/core/src/util/string_format.h"
#include "Firestore/core/src/util/string_util.h"
#include "Firestore/core/src/util/to_string.h"
#include "Firestore/core/src/util/type_traits.h"
#include "Firestore/core/src/util/version.h"
#include "Firestore/core/src/util/writer.h"
#include "Firestore/core/src/util/x_ray_string.h"
#include "Firestore/core/src/util/xxhash.h"
#include "Firestore/core/variant.h"
#include "Firestore/core/write_batch.h"
#include "Firestore/core/write_batch_impl.h"
#include "Firestore/core/write_stream.h"
#include "Firestore/core/write_stream_impl.h"
#include "Firestore/core/write_stream_token_manager.h"
}

using firebase::firestore::core::Bound;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::DocumentSnapshot;
using firebase::firestore::core::Query;
using firebase::firestore::core::QuerySnapshot;
using firebase::firestore::core::Target;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::types::Type;
using firebase::firestore::model::Value;
using firebase::firestore::model::ValueUtil;
using firebase::firestore::nanopb::MessageBuilder;
using firebase::firestore::nanopb::Reader;
using firebase::firestore::nanopb::Writer;
using firebase::firestore::util::Status;
using firebase::firestore::util::StatusOr;
using firebase::firestore::util::StringFormat;
using firebase::firestore::util::StringUtil;
using firebase::firestore::util::ToString;
using firebase::firestore::util::TypeTraits;
using firebase::firestore::util::Version;
using firebase::firestore::util::Writer;
using firebase::firestore::util::XRayString;
using firebase::firestore::util::Xxhash;
using firebase::firestore::variant;
using firebase::firestore::WriteBatch;
using firebase::firestore::WriteBatchImpl;
using firebase::firestore::WriteStream;
using firebase::firestore::WriteStreamImpl;
using firebase::firestore::WriteStreamTokenManager;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<DocumentSnapshot> docs;
  for (int i = 0; i < 10; i++) {
    docs.push_back(RandomDocumentSnapshot(&stream));
  }

  Bound bound = RandomBound(&stream);
  bool result = bound.SortsAfterDocument(nullptr, &docs, nullptr);

  return 0;
}