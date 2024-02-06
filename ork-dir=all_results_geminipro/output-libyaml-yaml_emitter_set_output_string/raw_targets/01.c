#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);

  const size_t output_buffer_size = stream.ConsumeIntegralInRange<size_t>(
      1, std::numeric_limits<size_t>::max());
  std::vector<char> output_buffer(output_buffer_size);

  size_t size_written = 0;
  yaml_emitter_set_output_string(&emitter, output_buffer.data(),
                                 output_buffer.size(), &size_written);

  yaml_event_t event;
  yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
  yaml_emitter_emit(&emitter, &event);

  yaml_document_start_event_initialize(&event, nullptr, nullptr, nullptr, 0);
  yaml_emitter_emit(&emitter, &event);

  yaml_sequence_start_event_initialize(&event, nullptr, nullptr, 0);
  yaml_emitter_emit(&emitter, &event);

  for (size_t i = 0; i < 10; ++i) {
    yaml_scalar_event_initialize(&event, nullptr, nullptr,
                                 reinterpret_cast<const uint8_t*>(
                                     stream.ConsumeRemainingBytesAsString().c_str()),
                                 stream.ConsumeRemainingBytesAsString().size(),
                                 1, 1, YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(&emitter, &event);
  }

  yaml_sequence_end_event_initialize(&event);
  yaml_emitter_emit(&emitter, &event);

  yaml_document_end_event_initialize(&event, 0);
  yaml_emitter_emit(&emitter, &event);

  yaml_stream_end_event_initialize(&event);
  yaml_emitter_emit(&emitter, &event);

  yaml_emitter_delete(&emitter);

  return 0;
}