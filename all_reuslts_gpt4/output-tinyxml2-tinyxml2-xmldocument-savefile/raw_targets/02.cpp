#include <fuzzer/FuzzedDataProvider.h>
#include <tinyxml2.h>
#include <string>
#include <filesystem>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file in the system's temp directory
  std::filesystem::path temp_dir = std::filesystem::temp_directory_path();
  std::filesystem::path temp_file = temp_dir / "fuzz.xml";

  // Create a new XMLDocument
  tinyxml2::XMLDocument doc;

  // Parse some XML data
  std::string xml_data = stream.ConsumeRemainingBytesAsString();
  doc.Parse(xml_data.c_str());

  // Save the XMLDocument to a file
  doc.SaveFile(temp_file.c_str(), stream.ConsumeBool());

  // Clean up the temporary file
  std::filesystem::remove(temp_file);

  return 0;
}