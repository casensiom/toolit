#include <util/CommonUtil.hpp>

#include <gtest/gtest.h>

using namespace cam::util;

enum test { VALUE1 };
namespace EnumTest {
enum test { VALUE1 };
}

TEST(CommonUtil, enumName) {
    std::string name;
    name = CommonUtil::getEnumName<VALUE1>();
    EXPECT_EQ(name, "VALUE1");
    name = CommonUtil::getEnumName<EnumTest::VALUE1>();
    EXPECT_EQ(name, "EnumTest::VALUE1");
}
