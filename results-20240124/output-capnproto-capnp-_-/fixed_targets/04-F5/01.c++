#include <capnp/message.h>
#include <capnp/serialize.h>

namespace capnp {
namespace _ {

extern "C" {

void checkTestMessage(TestAllTypes::Reader reader) {
  // Check the value of each field.
  EXPECT_EQ(reader.getBoolField(), true);
  EXPECT_EQ(reader.getInt32Field(), 1234);
  EXPECT_EQ(reader.getInt64Field(), 5678);
  EXPECT_EQ(reader.getFloat32Field(), 3.14);
  EXPECT_EQ(reader.getFloat64Field(), 2.71);
  EXPECT_EQ(reader.getStringField(), "Hello, world!");
  EXPECT_EQ(reader.getDataField().size(), 10);
  EXPECT_EQ(reader.getDataField()[0], 0x01);
  EXPECT_EQ(reader.getDataField()[1], 0x02);
  EXPECT_EQ(reader.getDataField()[2], 0x03);
  EXPECT_EQ(reader.getDataField()[3], 0x04);
  EXPECT_EQ(reader.getDataField()[4], 0x05);
  EXPECT_EQ(reader.getDataField()[5], 0x06);
  EXPECT_EQ(reader.getDataField()[6], 0x07);
  EXPECT_EQ(reader.getDataField()[7], 0x08);
  EXPECT_EQ(reader.getDataField()[8], 0x09);
  EXPECT_EQ(reader.getDataField()[9], 0x0A);

  // Check the presence of each field.
  EXPECT_TRUE(reader.hasBoolField());
  EXPECT_TRUE(reader.hasInt32Field());
  EXPECT_TRUE(reader.hasInt64Field());
  EXPECT_TRUE(reader.hasFloat32Field());
  EXPECT_TRUE(reader.hasFloat64Field());
  EXPECT_TRUE(reader.hasStringField());
  EXPECT_TRUE(reader.hasDataField());

  // Check the type of each field.
  EXPECT_EQ(reader.getBoolField().type(), Type::BOOL);
  EXPECT_EQ(reader.getInt32Field().type(), Type::INT32);
  EXPECT_EQ(reader.getInt64Field().type(), Type::INT64);
  EXPECT_EQ(reader.getFloat32Field().type(), Type::FLOAT32);
  EXPECT_EQ(reader.getFloat64Field().type(), Type::FLOAT64);
  EXPECT_EQ(reader.getStringField().type(), Type::STRING);
  EXPECT_EQ(reader.getDataField().type(), Type::DATA);

  // Check the size of each field.
  EXPECT_EQ(reader.getBoolField().size(), 1);
  EXPECT_EQ(reader.getInt32Field().size(), 1);
  EXPECT_EQ(reader.getInt64Field().size(), 1);
  EXPECT_EQ(reader.getFloat32Field().size(), 1);
  EXPECT_EQ(reader.getFloat64Field().size(), 1);
  EXPECT_EQ(reader.getStringField().size(), 13);
  EXPECT_EQ(reader.getDataField().size(), 10);
}

}  // extern "C"

}  // namespace _
}  // namespace capnp