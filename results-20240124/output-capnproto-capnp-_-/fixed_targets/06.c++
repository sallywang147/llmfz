#include <capnp/dynamic.capnp.h>

#include "serialize.h"
#include "test-util.h"

extern "C" {
#include <capnp/serialize.h>
}

int main(int argc, char** argv) {
  return capnp::test::main(argc, argv);
}