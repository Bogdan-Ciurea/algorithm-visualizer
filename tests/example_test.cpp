#include <gtest/gtest.h>
#include "interface.h"

TEST(ExampleTests, FirstExample) {
    EXPECT_TRUE(true);
    Interface inter = Interface();
    inter.~Interface();
}