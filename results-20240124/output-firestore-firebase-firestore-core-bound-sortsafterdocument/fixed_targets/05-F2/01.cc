#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/bound.h"
#include "Firestore/core/src/core/document.h"
#include "Firestore/core/src/core/document_key.h"
#include "Firestore/core/src/core/document_snapshot.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/query_snapshot.h"
#include "Firestore/core/src/core/target_id.h"
#include "Firestore/core/src/core/types.h"
#include "Firestore/core/src/core/view_snapshot.h"
#include "Firestore/core/src/local/leveldb_key.h"
#include "Firestore/core/src/local/leveldb_util.h"
#include "Firestore/core/src/model/document.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/snapshot_version.h"
#include "Firestore/core/src/model/types.h"
#include "Firestore/core/src/nanopb/reader.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/status.h"
#include "Firestore/core/src/util/string_format.h"
#include "Firestore/core/src/util/string_util.h"
#include "Firestore/core/src/util/type_traits.h"
#include "Firestore/core/src/util/vector.h"

extern "C" {
#include "Firestore/core/src/nanopb/message_codec.h"
#include "Firestore/core/src/nanopb/message_definition.h"
#include "Firestore/core/src/nanopb/writer.h"
}

using firebase::firestore::core::Bound;
using firebase::firestore::core::Document;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::DocumentSnapshot;
using firebase::firestore::core::Query;
using firebase::firestore::core::QuerySnapshot;
using firebase::firestore::core::TargetId;
using firebase::firestore::core::ViewSnapshot;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::Type;
using firebase::firestore::nanopb::MessageReader;
using firebase::firestore::nanopb::MessageWriter;
using firebase::firestore::util::Status;
using firebase::firestore::util::StringFormat;
using firebase::firestore::util::StringUtil;
using firebase::firestore::util::TypeTraits;
using firebase::firestore::util::Vector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  leveldb::Slice slice = firebase::firestore::local::MakeSlice(str);

  // Test DescribeKey(std::string) which calls MakeSlice(std::string).
  try {
    firebase::firestore::local::DescribeKey(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbMutationKey methods.
  try {
    LevelDbMutationKey::KeyPrefix(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    BatchId batch_id{static_cast<int>(size)};
    LevelDbMutationKey::Key(str, batch_id);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    LevelDbMutationKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbDocumentMutationKey methods.
  try {
    LevelDbDocumentMutationKey::KeyPrefix(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    LevelDbDocumentMutationKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbMutationQueueKey methods.
  try {
    LevelDbMutationQueueKey::Key(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    LevelDbMutationQueueKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbTargetGlobalKey methods.
  try {
    LevelDbTargetGlobalKey key;
    (void)key.Decode(slice);
  } catch (...) {
    // ignore caught errors and assertions.
  }

  // Test LevelDbTargetKey methods.
  try {
    LevelDbTargetKey key;
    (void)key.Decode(slice);
  } catch (...) {
    // ignore caught errors and assertions.
  }

  // Test LevelDbQueryTargetKey methods.
  try {
    LevelDbQueryTargetKey::KeyPrefix(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    LevelDbQueryTargetKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbTargetDocumentKey methods.
  try {
    LevelDbTargetDocumentKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbDocumentTargetKey methods.
  try {
    ResourcePath rp = ResourcePath::FromString(str);
    LevelDbDocumentTargetKey::KeyPrefix(rp);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    LevelDbDocumentTargetKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test LevelDbRemoteDocumentKey methods.
  try {
    ResourcePath rp = ResourcePath::FromString(str);
    LevelDbRemoteDocumentKey::KeyPrefix(rp);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  try {
    LevelDbRemoteDocumentKey key;
    (void)key.Decode(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test Bound::SortsAfterDocument().
  try {
    Bound bound;
    std::vector<FieldValue> values;
    union {
      Document document;
      DocumentSnapshot document_snapshot;
    } doc_or_snap;
    bound.SortsAfterDocument(&doc_or_snap, &values, nullptr);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  return 0;
}