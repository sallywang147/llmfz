#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "proj/crs.hpp"
#include "proj/crs_wkt.hpp"

extern "C" {
#include "proj/crs_geojson.hpp"
#include "proj/crs_transform.hpp"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string wkt = stream.ConsumeRemainingBytesAsString();
  osgeo::proj::crs::CRS source_crs;
  if (!osgeo::proj::crs::wkt::from_wkt(wkt, source_crs)) {
    return 0;
  }

  std::shared_ptr<osgeo::proj::crs::CRS> target_crs = std::make_shared<osgeo::proj::crs::CRS>();
  osgeo::proj::crs::CRSTransform transform;
  if (!osgeo::proj::crs::getCRSProj4(source_crs, transform.src_pj)) {
    return 0;
  }
  if (!osgeo::proj::crs::getCRSProj4(*target_crs, transform.tgt_pj)) {
    return 0;
  }
  transform.skip_factor = 1;
  transform.accuracy = 0;
  transform.order = 0;
  transform.geod = nullptr;
  transform.ellps = nullptr;
  transform.datum_params = nullptr;
  transform.inverse = 0;
  transform.axis_order[0] = 0;
  transform.axis_order[1] = 1;
  transform.axis_order[2] = 2;
  transform.axis_order[3] = 3;
  transform.axis_order[4] = 4;
  transform.axis_order[5] = 5;
  transform.axis_order[6] = 6;
  transform.axis_order[7] = 7;
  transform.axis_order[8] = 8;
  transform.axis_order[9] = 9;
  transform.axis_order[10] = 10;
  transform.axis_order[11] = 11;
  transform.axis_order[12] = 12;
  transform.axis_order[13] = 13;
  transform.axis_order[14] = 14;
  transform.axis_order[15] = 15;
  transform.axis_order[16] = 16;
  transform.axis_order[17] = 17;
  transform.axis_order[18] = 18;
  transform.axis_order[19] = 19;
  transform.axis_order[20] = 20;
  transform.axis_order[21] = 21;
  transform.axis_order[22] = 22;
  transform.axis_order[23] = 23;
  transform.axis_order[24] = 24;
  transform.axis_order[25] = 25;
  transform.axis_order[26] = 26;
  transform.axis_order[27] = 27;
  transform.axis_order[28] = 28;
  transform.axis_order[29] = 29;
  transform.axis_order[30] = 30;
  transform.axis_order[31] = 31;
  transform.axis_order[32] = 32;
  transform.axis_order[33] = 33;
  transform.axis_order[34] = 34;
  transform.axis_order[35] = 35;
  transform.axis_order[36] = 36;
  transform.axis_order[37] = 37;
  transform.axis_order[38] = 38;
  transform.axis_order[39] = 39;
  transform.axis_order[40] = 40;
  transform.axis_order[41] = 41;
  transform.axis_order[42] = 42;
  transform.axis_order[43] = 43;
  transform.axis_order[44] = 44;
  transform.axis_order[45] = 45;
  transform.axis_order[46] = 46;
  transform.axis_order[47] = 47;
  transform.axis_order[48] = 48;
  transform.axis_order[49] = 49;
  transform.axis_order[50] = 50;
  transform.axis_order[51] = 51;
  transform.axis_order[52] = 52;
  transform.axis_order[53] = 53;
  transform.axis_order[54] = 54;
  transform.axis_order[55] = 55;
  transform.axis_order[56] = 56;
  transform.axis_order[57] = 57;
  transform.axis_order[58] = 58;
  transform.axis_order[59] = 59;
  transform.axis_order[60] = 60;
  transform.axis_order[61] = 61;
  transform.axis_order[62] = 62;
  transform.axis_order[63] = 63;
  transform.axis_order[64] = 64;
  transform.axis_order[65] = 65;
  transform.axis_order[66] = 66;
  transform.axis_order[67] = 67;
  transform.axis_order[68] = 68;
  transform.axis_order[69] = 69;
  transform.axis_order[70] = 70;
  transform.axis_order[71] = 71;
  transform.axis_order[72] = 72;
  transform.axis_order[73] = 73;
  transform.axis_order[74] = 74;
  transform.axis_order[75] = 75;
  transform.axis_order[76] = 76;
  transform.axis_order[77] = 77;
  transform.axis_order[78] = 78;
  transform.axis_order[79] = 79;
  transform.axis_order[80] = 80;
  transform.axis_order[81] = 81;
  transform.axis_order[82] = 82;
  transform.axis_order[83] = 83;
  transform.axis_order[84] = 84;
  transform.axis_order[85] = 85;
  transform.axis_order[86] = 86;
  transform.axis_order[87] = 87;
  transform.axis_order[88] = 88;
  transform.axis_order[89] = 89;
  transform.axis_order[90] = 90;
  transform.axis_order[91] = 91;
  transform.axis_order[92] = 92;
  transform.axis_order[93] = 93;
  transform.axis_order[94] = 94;
  transform.axis_order[95] = 95;
  transform.axis_order[96] = 96;
  transform.axis_order[97] = 97;
  transform.axis_order[98] = 98;
  transform.axis_order[99] = 99;
  transform.axis_order[100] = 100;
  transform.axis_order[101] = 101;
  transform.axis_order[102] = 102;
  transform.axis_order[103] = 103;
  transform.