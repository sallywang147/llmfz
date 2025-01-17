#include <fuzzer/FuzzedDataProvider.h>
#include <pistache/http_headers.h>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize FullDate object
  Pistache::Http::FullDate fullDate;
  
  // Initialize ostream object
  std::ostringstream oss;
  
  // Initialize __bucket_list_deallocator object
  std::__bucket_list_deallocator* bucketListDeallocator = nullptr;
  
  // Consume data for the int parameter
  int param = stream.ConsumeIntegral<int>();
  
  // Call the function to fuzz
  fullDate.write(bucketListDeallocator, &oss, param);
  
  return 0;
}