#include <cstddef>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

using std::string;

#include "uriparser/include/uriparser/Uri.h"
#include "uriparser/include/uriparser/UriIp4.h"

class UriParserW {
public:
  UriParserW() { memset((void *)&uri_, 0, sizeof(uri_)); }
  ~UriParserW() { uriFreeUriMembersW(&uri_); }

  UriUriStructW *get_mutable_uri() { return &uri_; }
  UriUriStructW *get_uri() const { return const_cast<UriUriStructW *>(&uri_); }

private:
  UriUriStructW uri_;
};

void Escapes(const string &uri) {
  const char *first = uri.c_str();
  // A new line char takes 6 char to encode.
  // Use a vector to make a C string.
  std::vector<char> buf1(uri.size() * 6 + 1);
  std::vector<char> buf2(uri.size() * 3 + 1);

  char *result;
  result = uriEscapeW(first, &buf1[0], URI_TRUE, URI_TRUE);
  result = uriEscapeW(first, &buf1[0], URI_FALSE, URI_TRUE);
  if (buf1.data())
    uriUnescapeInPlaceW(&buf1[0]);

  result = uriEscapeW(first, &buf2[0], URI_TRUE, URI_FALSE);
  result = uriEscapeW(first, &buf2[0], URI_FALSE, URI_FALSE);
  if (buf2.data())
    uriUnescapeInPlaceW(&buf2[0]);
}

void FileNames(const string &uri) {
  const size_t size = 8 + 3 * uri.size() + 1;
  std::vector<char> buf(size);

  uriUnixFilenameToUriStringW(uri.c_str(), &buf[0]);
  uriWindowsFilenameToUriStringW(uri.c_str(), &buf[0]);
  uriUriStringToUnixFilenameW(uri.c_str(), &buf[0]);
  uriUriStringToWindowsFilenameW(uri.c_str(), &buf[0]);
}

int uriParseIpFourAddressW(unsigned char *octetOutput, const wchar_t *first, const wchar_t *afterLast);

void Ipv4(const string &s) {
  const wchar_t *cstr = reinterpret_cast<const wchar_t *>(s.c_str());
  unsigned char result[4] = {};
  uriParseIpFourAddressW(result, cstr, &cstr[s.size()]);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider stream(data, size);
  bool domainRelative = stream.ConsumeBool();
  size_t uriSize = stream.remaining_bytes() / 2;

  const string uri1 = stream.ConsumeBytesAsString(uriSize);
  const string uri2 = stream.ConsumeRemainingBytesAsString();

  Escapes(uri1);
  Escapes(uri2);

  FileNames(uri1);
  FileNames(uri2);

  Ipv4(uri1);
  Ipv4(uri2);

  UriParserW parser1;
  UriParserStateW state1;
  state1.uri = parser1.get_mutable_uri();
  if (uriParseUriW(&state1, uri1.c_str()) != URI_SUCCESS)
    return 0;

  char buf[1024 * 8] = {0};
  int written = 0;
  uriToStringW(buf, state1.uri, sizeof(buf), &written);

  UriParserW parser2;
  UriParserStateW state2;
  state2.uri = parser2.get_mutable_uri();
  if (uriParseUriW(&state2, uri2.c_str()) != URI_SUCCESS)
    return 0;

  int baseUriLength = 0;
  int pathSegmentCount = 0;
  int *pathSegmentOffset = nullptr;
  uriParseSingleUriExW(state1.uri, &baseUriLength, &pathSegmentCount, &pathSegmentOffset);

  uriNormalizeSyntaxW(state1.uri);

  UriUriW absUri;
  uriAddBaseUriW(&absUri, state1.uri, state2.uri);
  uriFreeUriMembersW(&absUri);

  UriUriW relUri;
  uriRemoveBaseUriW(&relUri, state1.uri, state2.uri, domainRelative);
  uriFreeUriMembersW(&relUri);

  return 0;
}