 #include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Firestore/core/src/core/bound.h"
#include "Firestore/core/src/core/document_key.h"
#include "Firestore/core/src/core/field_filter.h"
#include "Firestore/core/src/core/field_path.h"
#include "Firestore/core/src/core/filter.h"
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/core/target.h"
#include "Firestore/core/src/core/target_id_generator.h"
#include "Firestore/core/src/core/target_parser.h"
#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/field_path.h"
#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/resource_path.h"
#include "Firestore/core/src/model/value.h"
#include "Firestore/core/src/nanopb/message_codec.h"
#include "Firestore/core/src/nanopb/reader.h"
#include "Firestore/core/src/nanopb/writer.h"
#include "Firestore/core/src/util/status.h"
#include "Firestore/core/src/util/string_format.h"
#include "Firestore/core/src/util/string_util.h"
#include "Firestore/core/src/util/time.h"
#include "Firestore/core/src/util/to_string.h"
#include "Firestore/core/src/util/types.h"

using firebase::firestore::core::Bound;
using firebase::firestore::core::DocumentKey;
using firebase::firestore::core::FieldFilter;
using firebase::firestore::core::FieldPath;
using firebase::firestore::core::Filter;
using firebase::firestore::core::Query;
using firebase::firestore::core::Target;
using firebase::firestore::core::TargetIdGenerator;
using firebase::firestore::core::TargetParser;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::ResourcePath;
using firebase::firestore::model::Value;
using firebase::firestore::nanopb::MessageCodec;
using firebase::firestore::nanopb::Reader;
using firebase::firestore::nanopb::Writer;
using firebase::firestore::util::Status;
using firebase::firestore::util::StringFormat;
using firebase::firestore::util::StringUtil;
using firebase::firestore::util::Time;
using firebase::firestore::util::ToString;
using firebase::firestore::util::Types;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  Reader reader(str);
  Target target;
  auto status = TargetParser::ParseQueryTarget(reader, &target);
  if (!status.ok()) {
    return 0;
  }

  std::vector<DocumentKey> keys;
  Bound::SortsAfterDocument(&target, &keys, nullptr);

  return 0;
}