#include <fuzzer/FuzzedDataProvider.h>
#include <rawspeed/ArwDecoder.h>
#include <rawspeed/RawImage.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 100000));
  void *data_ptr = bytes.data();

  // Extract to user defined object
  rawspeed::RawImage obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Extract to user defined object
  rawspeed::ArwDecoder obj2;
  size_t consumed2 = stream.ConsumeData(&obj2, sizeof(obj2));

  // Call the function
  obj2.decodeSRF(&obj);

  return 0;
}
```

The issue in the original code is that the function `decodeSRF` is a member function of `rawspeed::ArwDecoder`, but it was called as a static function. To fix this, the call to `decodeSRF` has been changed to `obj2.decodeSRF(&obj)`, which correctly calls the member function on the `obj2` object.