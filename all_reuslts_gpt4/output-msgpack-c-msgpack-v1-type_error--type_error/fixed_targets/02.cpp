#include <msgpack.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  try {
    msgpack::object_handle unpacked = msgpack::unpack(reinterpret_cast<const char *>(data), size);
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, unpacked.get());
  } catch (msgpack::type_error &e) {
    e.~type_error(); // Explicitly call the destructor
  } catch (...) {
  }
  return 0;
}