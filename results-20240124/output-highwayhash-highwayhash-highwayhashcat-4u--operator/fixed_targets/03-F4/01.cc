#include <highwayhash/highwayhash_hh_sip_128.h>
#include <highwayhash/highwayhash_hh_sip_256.h>

extern "C" {
#include <highwayhash/highwayhash_hh_sip_128.h>
#include <highwayhash/highwayhash_hh_sip_256.h>
}

int main() {
  highwayhash::HHKey key128;
  highwayhash::HHKey key256;
  highwayhash::StringView str;
  highwayhash::HHResult64 result128;
  highwayhash::HHResult64 result256;
  highwayhash::HighwayHashCat<4u>()(key128, key256, &str, 10, &result128);
  highwayhash::HighwayHashCat<8u>()(key128, key256, &str, 10, &result256);
  return 0;
}