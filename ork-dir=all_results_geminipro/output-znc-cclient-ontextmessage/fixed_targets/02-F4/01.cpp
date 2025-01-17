#include <stdint.h>
#include <znc/Client.h>
#include <znc/TopicMessage.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();
  CClient client;
  CTopicMessage topic_message;
  topic_message.SetTopic("topic");
  topic_message.SetMessage(input);
  client.OnTextMessage(&client, &topic_message);
  return 0;
}
```

The fix is to wrap the `#include` directive for the `znc` headers in `extern "C" {}`. This is necessary because the `znc` headers are written in C++, and the fuzzer is written in C. Without the `extern "C" {}` wrapper, the linker would not be able to find the symbols defined in the `znc` headers.