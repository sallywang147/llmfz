#include <msgpack.hpp>
#include <exception>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  try {
    // NOTE(derwolfe): by default the limits are set at 2^32-1 length. I'm
    // setting these at far smaller values to avoid OOMs
    const int test_limit = 1000;
    msgpack::object_handle unpacked = msgpack::unpack(reinterpret_cast<const char *>(data), size, MSGPACK_NULLPTR, MSGPACK_NULLPTR, msgpack::unpack_limit(test_limit, test_limit, test_limit, test_limit, test_limit, test_limit));
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, unpacked.get());
    msgpack::v1::container_size_overflow e(sbuf.size());
    throw e;
  } catch (msgpack::v1::container_size_overflow &e) {
    msgpack::v1::container_size_overflow::~container_size_overflow(&e);
  } catch (std::exception &e) {
  } catch (...) {
  }
  return 0;
}