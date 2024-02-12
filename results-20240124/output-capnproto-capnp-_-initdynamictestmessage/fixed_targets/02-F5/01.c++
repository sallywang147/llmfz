#include <iostream>
#include <gtest/gtest.h>

extern "C" {
#include "dynamic_test_message.h"
}

TEST(DynamicTestMessage, Test) {
  ::initDynamicTestMessage();
  ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}