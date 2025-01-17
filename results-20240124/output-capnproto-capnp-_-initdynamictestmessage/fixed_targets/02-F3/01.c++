#include "capnp/test.capnp.h"
#include <capnp/message.h>
#include <kj/string-tree.h>
#include <kj/debug.h>
#include <kj/array.h>
#include <kj/vector.h>
#include <kj/main.h>
#include <kj/io.h>
#include <kj/test.h>
#include <kj/units.h>
#include <capnp/serialize-packed.h>
#include <kj/debug.h>
#include <kj/vector.h>
#include <kj/array.h>
#include <kj/string.h>
#include <kj/string-tree.h>
#include <kj/units.h>
#include <capnp/dynamic.h>
#include <unistd.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  capnp::DynamicStruct::Builder builder;
  capnp::_::initDynamicTestMessage(&builder);
  for (int i = 0; i < 100; i++) {
    capnp::DynamicStruct::Builder dynamicBuilder = builder.init("dynamicNestedStruct", i);
    capnp::_::initDynamicTestMessage(&dynamicBuilder);
  }
  return 0;
}