#include <cstddef>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

using std::string;
#include "uriparser/include/uriparser/Uri.h"
#include "uriparser/include/uriparser/UriIp4.h"

class UriParserA {
public:
  UriParserA() { memset((void *)&uri_, 0, sizeof(uri_)); }
  ~UriParserA() { uriFreeUriMembersA(&uri_); }

  UriUriA *get_mutable_uri() { return &uri_; }
  UriUriA *get_uri() const { return const_cast<UriUriA *>(&uri_); }

private:
  UriUriA uri_;
};

void Escapes(const string &uri) {
  const char *first = uri.c_str();
  // A new line char takes 6 char to encode.
  // Use a vector to make a C string.
  std::vector<char> buf1(uri.size() * 6 + 1);
  std::vector<char> buf2(uri.size() * 3 + 1);

  char *result;
  result = uriEscapeA(first, &buf1[0], URI_TRUE, URI_TRUE);
  result = uriEscapeA(first, &buf1[0], URI_FALSE, URI_TRUE);
  if (buf1.data())
    uriUnescapeInPlaceA(&buf1[0]);

  result = uriEscapeA(first, &buf2[0], URI_TRUE, URI_FALSE);
  result = uriEscapeA(first, &buf2[0], URI_FALSE, URI_FALSE);
  if (buf2.data())
    uriUnescapeInPlaceA(&buf2[0]);
}

void FileNames(const string &uri) {
  const size_t size = 8 + 3 * uri.size() + 1;
  std::vector<char> buf(size);

  uriUnixFilenameToUriStringA(uri.c_str(), &buf[0]);
  uriWindowsFilenameToUriStringA(uri.c_str(), &buf[0]);
  uriUriStringToUnixFilenameA(uri.c_str(), &buf[0]);
  uriUriStringToWindowsFilenameA(uri.c_str(), &buf[0]);
}

void Ipv4(const string &s) {
  const char *cstr = s.c_str();
  unsigned char result[4] = {};
  uriParseIpFourAddressA(result, cstr, &cstr[s.size()]);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider stream(data, size);
  size_t uriSize = stream.remaining_bytes();

  const string uri = stream.ConsumeRemainingBytesAsString();

  Escapes(uri);

  FileNames(uri);

  Ipv4(uri);

  UriParserA parser;
  UriParserStateA state;
  state.uri = parser.get_mutable_uri();
  uriParseSingleUriA(state.uri, uri.c_str(), nullptr);

  uriNormalizeSyntaxA(state.uri);

  return 0;
}