#include <msgpack.hpp>

extern "C" {
#include <stdint.h>
}

// The function's signature must NOT be changed since other projects rely on it:
// - libFuzzer
// - AFL++
// - Google's oss-fuzz (uses the previous two ones)
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  try {
    // NOTE(derwolfe): by default the limits are set at 2^32-1 length. I'm
    // setting these at far smaller values to avoid OOMs
    const int test_limit = 1000;
    msgpack::object_handle unpacked = msgpack::unpack(reinterpret_cast<const char *>(data), size, MSGPACK_NULLPTR, MSGPACK_NULLPTR, msgpack::unpack_limit(test_limit, test_limit, test_limit, test_limit, test_limit, test_limit));
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, unpacked.get());
    msgpack::zone zone;
    msgpack::object obj;
    msgpack::unpack(sbuf.data(), sbuf.size(), &zone, &obj);
  } catch (const msgpack::unpack_error &) {
  } catch (const msgpack::pack_error &) {
  }
  return 0;
}