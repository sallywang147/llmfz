#include <cryptofuzz/Botan.h>

namespace cryptofuzz {
namespace module {
namespace Botan {

void OpECGDSA_Sign(std::optional<cryptofuzz::module::BearSSL>* bearssl,
                   cryptofuzz::operation::ECDSA_Sign* op,
                   unsigned char const* msg, unsigned long msg_len) {
  // Implementation goes here.
}

}  // namespace Botan
}  // namespace module
}  // namespace cryptofuzz