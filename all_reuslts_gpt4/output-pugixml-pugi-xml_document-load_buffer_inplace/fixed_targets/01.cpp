#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pugixml.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pugi::xml_document doc;
  pugi::xml_parse_result result;
  pugi::xml_encoding encoding = stream.PickValueInArray({pugi::encoding_auto, pugi::encoding_utf8, pugi::encoding_utf16_le, pugi::encoding_utf16_be, pugi::encoding_utf16, pugi::encoding_utf32_le, pugi::encoding_utf32_be, pugi::encoding_utf32, pugi::encoding_wchar, pugi::encoding_latin1});
  pugi::xml_parse_status status = stream.PickValueInArray({pugi::status_ok, pugi::status_file_not_found, pugi::status_io_error, pugi::status_out_of_memory, pugi::status_internal_error, pugi::status_unrecognized_tag, pugi::status_bad_pi, pugi::status_bad_comment, pugi::status_bad_cdata, pugi::status_bad_doctype, pugi::status_bad_pcdata, pugi::status_bad_start_element, pugi::status_bad_attribute, pugi::status_bad_end_element, pugi::status_end_element_mismatch, pugi::status_append_invalid_root, pugi::status_no_document_element});

  std::string str = stream.ConsumeRemainingBytesAsString();
  char* buffer = const_cast<char*>(str.c_str());

  doc.load_buffer_inplace(buffer, str.size(), pugi::parse_default, encoding);

  return 0;
}