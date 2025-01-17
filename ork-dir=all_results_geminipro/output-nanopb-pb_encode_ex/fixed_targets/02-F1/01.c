#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "pb_decode.h"
#include "pb_encode.h"

extern "C" {
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string message_type = stream.ConsumeRemainingBytesAsString();

  const google::protobuf::Descriptor* fields =
      google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(
          message_type);
  if (fields == nullptr) {
    return 0;
  }

  google::protobuf::Message* src_struct = fields->New();
  if (src_struct == nullptr) {
    return 0;
  }

  // Initialize the fields in the message.
  for (int i = 0; i < fields->field_count(); i++) {
    const google::protobuf::FieldDescriptor* field = fields->field(i);
    switch (field->type()) {
      case google::protobuf::FieldDescriptor::TYPE_UINT32:
        src_struct->GetReflection()->SetUInt32(src_struct, field,
                                               stream.ConsumeIntegral<uint32_t>());
        break;
      case google::protobuf::FieldDescriptor::TYPE_INT32:
        src_struct->GetReflection()->SetInt32(src_struct, field,
                                              stream.ConsumeIntegral<int32_t>());
        break;
      case google::protobuf::FieldDescriptor::TYPE_UINT64:
        src_struct->GetReflection()->SetUInt64(src_struct, field,
                                               stream.ConsumeIntegral<uint64_t>());
        break;
      case google::protobuf::FieldDescriptor::TYPE_INT64:
        src_struct->GetReflection()->SetInt64(src_struct, field,
                                              stream.ConsumeIntegral<int64_t>());
        break;
      case google::protobuf::FieldDescriptor::TYPE_BOOL:
        src_struct->GetReflection()->SetBool(src_struct, field,
                                             stream.ConsumeBool());
        break;
      case google::protobuf::FieldDescriptor::TYPE_FLOAT:
        src_struct->GetReflection()->SetFloat(src_struct, field,
                                             stream.ConsumeFloat());
        break;
      case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
        src_struct->GetReflection()->SetDouble(src_struct, field,
                                              stream.ConsumeDouble());
        break;
      case google::protobuf::FieldDescriptor::TYPE_STRING:
        src_struct->GetReflection()->SetString(
            src_struct, field, stream.ConsumeRemainingBytesAsString());
        break;
      case google::protobuf::FieldDescriptor::TYPE_BYTES:
        src_struct->GetReflection()->SetBytes(
            src_struct, field, stream.ConsumeRemainingBytesAsString());
        break;
      default:
        // TODO(user): Handle other data types.
        break;
    }
  }

  // Encode the message.
  std::string output;
  src_struct->SerializeToString(&output);

  delete src_struct;

  return 0;
}