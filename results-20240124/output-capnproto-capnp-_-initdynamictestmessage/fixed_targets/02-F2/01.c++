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
  capnp::DynamicStruct::Builder dynamicBuilder = builder.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder);
  capnp::DynamicStruct::Builder dynamicBuilder2 = dynamicBuilder.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder2);
  capnp::DynamicStruct::Builder dynamicBuilder3 = dynamicBuilder2.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder3);
  capnp::DynamicStruct::Builder dynamicBuilder4 = dynamicBuilder3.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder4);
  capnp::DynamicStruct::Builder dynamicBuilder5 = dynamicBuilder4.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder5);
  capnp::DynamicStruct::Builder dynamicBuilder6 = dynamicBuilder5.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder6);
  capnp::DynamicStruct::Builder dynamicBuilder7 = dynamicBuilder6.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder7);
  capnp::DynamicStruct::Builder dynamicBuilder8 = dynamicBuilder7.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder8);
  capnp::DynamicStruct::Builder dynamicBuilder9 = dynamicBuilder8.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder9);
  capnp::DynamicStruct::Builder dynamicBuilder10 = dynamicBuilder9.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder10);
  capnp::DynamicStruct::Builder dynamicBuilder11 = dynamicBuilder10.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder11);
  capnp::DynamicStruct::Builder dynamicBuilder12 = dynamicBuilder11.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder12);
  capnp::DynamicStruct::Builder dynamicBuilder13 = dynamicBuilder12.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder13);
  capnp::DynamicStruct::Builder dynamicBuilder14 = dynamicBuilder13.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder14);
  capnp::DynamicStruct::Builder dynamicBuilder15 = dynamicBuilder14.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder15);
  capnp::DynamicStruct::Builder dynamicBuilder16 = dynamicBuilder15.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder16);
  capnp::DynamicStruct::Builder dynamicBuilder17 = dynamicBuilder16.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder17);
  capnp::DynamicStruct::Builder dynamicBuilder18 = dynamicBuilder17.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder18);
  capnp::DynamicStruct::Builder dynamicBuilder19 = dynamicBuilder18.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder19);
  capnp::DynamicStruct::Builder dynamicBuilder20 = dynamicBuilder19.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder20);
  capnp::DynamicStruct::Builder dynamicBuilder21 = dynamicBuilder20.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder21);
  capnp::DynamicStruct::Builder dynamicBuilder22 = dynamicBuilder21.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder22);
  capnp::DynamicStruct::Builder dynamicBuilder23 = dynamicBuilder22.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder23);
  capnp::DynamicStruct::Builder dynamicBuilder24 = dynamicBuilder23.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder24);
  capnp::DynamicStruct::Builder dynamicBuilder25 = dynamicBuilder24.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder25);
  capnp::DynamicStruct::Builder dynamicBuilder26 = dynamicBuilder25.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder26);
  capnp::DynamicStruct::Builder dynamicBuilder27 = dynamicBuilder26.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder27);
  capnp::DynamicStruct::Builder dynamicBuilder28 = dynamicBuilder27.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder28);
  capnp::DynamicStruct::Builder dynamicBuilder29 = dynamicBuilder28.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder29);
  capnp::DynamicStruct::Builder dynamicBuilder30 = dynamicBuilder29.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder30);
  capnp::DynamicStruct::Builder dynamicBuilder31 = dynamicBuilder30.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder31);
  capnp::DynamicStruct::Builder dynamicBuilder32 = dynamicBuilder31.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder32);
  capnp::DynamicStruct::Builder dynamicBuilder33 = dynamicBuilder32.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder33);
  capnp::DynamicStruct::Builder dynamicBuilder34 = dynamicBuilder33.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder34);
  capnp::DynamicStruct::Builder dynamicBuilder35 = dynamicBuilder34.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder35);
  capnp::DynamicStruct::Builder dynamicBuilder36 = dynamicBuilder35.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder36);
  capnp::DynamicStruct::Builder dynamicBuilder37 = dynamicBuilder36.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder37);
  capnp::DynamicStruct::Builder dynamicBuilder38 = dynamicBuilder37.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder38);
  capnp::DynamicStruct::Builder dynamicBuilder39 = dynamicBuilder38.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder39);
  capnp::DynamicStruct::Builder dynamicBuilder40 = dynamicBuilder39.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder40);
  capnp::DynamicStruct::Builder dynamicBuilder41 = dynamicBuilder40.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder41);
  capnp::DynamicStruct::Builder dynamicBuilder42 = dynamicBuilder41.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder42);
  capnp::DynamicStruct::Builder dynamicBuilder43 = dynamicBuilder42.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder43);
  capnp::DynamicStruct::Builder dynamicBuilder44 = dynamicBuilder43.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder44);
  capnp::DynamicStruct::Builder dynamicBuilder45 = dynamicBuilder44.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder45);
  capnp::DynamicStruct::Builder dynamicBuilder46 = dynamicBuilder45.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder46);
  capnp::DynamicStruct::Builder dynamicBuilder47 = dynamicBuilder46.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder47);
  capnp::DynamicStruct::Builder dynamicBuilder48 = dynamicBuilder47.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder48);
  capnp::DynamicStruct::Builder dynamicBuilder49 = dynamicBuilder48.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder49);
  capnp::DynamicStruct::Builder dynamicBuilder50 = dynamicBuilder49.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder50);
  capnp::DynamicStruct::Builder dynamicBuilder51 = dynamicBuilder50.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder51);
  capnp::DynamicStruct::Builder dynamicBuilder52 = dynamicBuilder51.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder52);
  capnp::DynamicStruct::Builder dynamicBuilder53 = dynamicBuilder52.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder53);
  capnp::DynamicStruct::Builder dynamicBuilder54 = dynamicBuilder53.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder54);
  capnp::DynamicStruct::Builder dynamicBuilder55 = dynamicBuilder54.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder55);
  capnp::DynamicStruct::Builder dynamicBuilder56 = dynamicBuilder55.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder56);
  capnp::DynamicStruct::Builder dynamicBuilder57 = dynamicBuilder56.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder57);
  capnp::DynamicStruct::Builder dynamicBuilder58 = dynamicBuilder57.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder58);
  capnp::DynamicStruct::Builder dynamicBuilder59 = dynamicBuilder58.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder59);
  capnp::DynamicStruct::Builder dynamicBuilder60 = dynamicBuilder59.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder60);
  capnp::DynamicStruct::Builder dynamicBuilder61 = dynamicBuilder60.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder61);
  capnp::DynamicStruct::Builder dynamicBuilder62 = dynamicBuilder61.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder62);
  capnp::DynamicStruct::Builder dynamicBuilder63 = dynamicBuilder62.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder63);
  capnp::DynamicStruct::Builder dynamicBuilder64 = dynamicBuilder63.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder64);
  capnp::DynamicStruct::Builder dynamicBuilder65 = dynamicBuilder64.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder65);
  capnp::DynamicStruct::Builder dynamicBuilder66 = dynamicBuilder65.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder66);
  capnp::DynamicStruct::Builder dynamicBuilder67 = dynamicBuilder66.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder67);
  capnp::DynamicStruct::Builder dynamicBuilder68 = dynamicBuilder67.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder68);
  capnp::DynamicStruct::Builder dynamicBuilder69 = dynamicBuilder68.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder69);
  capnp::DynamicStruct::Builder dynamicBuilder70 = dynamicBuilder69.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder70);
  capnp::DynamicStruct::Builder dynamicBuilder71 = dynamicBuilder70.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder71);
  capnp::DynamicStruct::Builder dynamicBuilder72 = dynamicBuilder71.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder72);
  capnp::DynamicStruct::Builder dynamicBuilder73 = dynamicBuilder72.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder73);
  capnp::DynamicStruct::Builder dynamicBuilder74 = dynamicBuilder73.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder74);
  capnp::DynamicStruct::Builder dynamicBuilder75 = dynamicBuilder74.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder75);
  capnp::DynamicStruct::Builder dynamicBuilder76 = dynamicBuilder75.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder76);
  capnp::DynamicStruct::Builder dynamicBuilder77 = dynamicBuilder76.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder77);
  capnp::DynamicStruct::Builder dynamicBuilder78 = dynamicBuilder77.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder78);
  capnp::DynamicStruct::Builder dynamicBuilder79 = dynamicBuilder78.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder79);
  capnp::DynamicStruct::Builder dynamicBuilder80 = dynamicBuilder79.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder80);
  capnp::DynamicStruct::Builder dynamicBuilder81 = dynamicBuilder80.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder81);
  capnp::DynamicStruct::Builder dynamicBuilder82 = dynamicBuilder81.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder82);
  capnp::DynamicStruct::Builder dynamicBuilder83 = dynamicBuilder82.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder83);
  capnp::DynamicStruct::Builder dynamicBuilder84 = dynamicBuilder83.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder84);
  capnp::DynamicStruct::Builder dynamicBuilder85 = dynamicBuilder84.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder85);
  capnp::DynamicStruct::Builder dynamicBuilder86 = dynamicBuilder85.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder86);
  capnp::DynamicStruct::Builder dynamicBuilder87 = dynamicBuilder86.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder87);
  capnp::DynamicStruct::Builder dynamicBuilder88 = dynamicBuilder87.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder88);
  capnp::DynamicStruct::Builder dynamicBuilder89 = dynamicBuilder88.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder89);
  capnp::DynamicStruct::Builder dynamicBuilder90 = dynamicBuilder89.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder90);
  capnp::DynamicStruct::Builder dynamicBuilder91 = dynamicBuilder90.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder91);
  capnp::DynamicStruct::Builder dynamicBuilder92 = dynamicBuilder91.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder92);
  capnp::DynamicStruct::Builder dynamicBuilder93 = dynamicBuilder92.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder93);
  capnp::DynamicStruct::Builder dynamicBuilder94 = dynamicBuilder93.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder94);
  capnp::DynamicStruct::Builder dynamicBuilder95 = dynamicBuilder94.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder95);
  capnp::DynamicStruct::Builder dynamicBuilder96 = dynamicBuilder95.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder96);
  capnp::DynamicStruct::Builder dynamicBuilder97 = dynamicBuilder96.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder97);
  capnp::DynamicStruct::Builder dynamicBuilder98 = dynamicBuilder97.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder98);
  capnp::DynamicStruct::Builder dynamicBuilder99 = dynamicBuilder98.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder99);
  capnp::DynamicStruct::Builder dynamicBuilder100 = dynamicBuilder99.init("dynamicNestedStruct");
  capnp::_::initDynamicTestMessage(&dynamicBuilder100);
  return 0;
}