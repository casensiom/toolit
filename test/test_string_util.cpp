#include <util/StringUtil.hpp>

#include <gtest/gtest.h>

using namespace cam::util;

StringUtil::Option
defaultOption() {
    return StringUtil::Option{};
}

TEST(StringUtilTest, Trim) {
    std::string str = "   Hello World   ";
    EXPECT_EQ(StringUtil::trim(str), "Hello World");
    EXPECT_EQ(StringUtil::ltrim(str), "Hello World   ");
    EXPECT_EQ(StringUtil::rtrim(str), "   Hello World");
}

TEST(StringUtilTest, CaseConversion) {
    std::string str = "Hello World";
    EXPECT_EQ(StringUtil::toUpper(str), "HELLO WORLD");
    EXPECT_EQ(StringUtil::toLower(str), "hello world");
}

TEST(StringUtilTest, Substring) {
    std::string str = "Hello World";
    EXPECT_EQ(StringUtil::substr(str, 6, 5), "World");
    EXPECT_EQ(StringUtil::substr(str, 0, 5), "Hello");
    EXPECT_EQ(StringUtil::substr(str, 11, 5), "");
}

TEST(StringUtilTest, Replace) {
    std::string str = "Hello hello HeLLo world";

    EXPECT_EQ(StringUtil::replace(str, "Hello", "Hi"), "Hi hello HeLLo world");

    StringUtil::Option insensitive;
    insensitive.sensitive = false;
    EXPECT_EQ(StringUtil::replace(str, "hello", "Hi", insensitive), "Hi Hi Hi world");
    EXPECT_EQ(StringUtil::replace(str, "hello", "", insensitive), "   world");
    EXPECT_EQ(StringUtil::replace(str, "NotFound", "Hi", insensitive), "Hello hello HeLLo world");
    EXPECT_EQ(StringUtil::replace(str, "", "Hi", insensitive), "Hello hello HeLLo world");
    EXPECT_EQ(StringUtil::replace(str, "Hello", "Greetings", insensitive), "Greetings Greetings Greetings world");
}

TEST(StringUtilTest, Count) {
    StringUtil::Option opt;
    std::string        str = "abcABCabc";

    EXPECT_EQ(StringUtil::count(str, "abc"), 2);

    opt.sensitive = false;
    EXPECT_EQ(StringUtil::count(str, "abc", opt), 3);
}

TEST(StringUtilTest, Find) {
    std::string        str = "Hello World Hello Universe";
    StringUtil::Option opt;

    EXPECT_EQ(StringUtil::find(str, "Hello"), 0);

    opt.from = 6;
    EXPECT_EQ(StringUtil::find(str, "Hello", opt), 12);

    opt.sensitive = false;
    EXPECT_EQ(StringUtil::find(str, "hello", opt), 12);
}

TEST(StringUtilTest, Split) {
    std::string        str = "apple,orange,banana,,grape";
    StringUtil::Option opt;

    auto result = StringUtil::split(str, ",");
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "apple");
    EXPECT_EQ(result[3], "grape");

    opt.keepEmpty = true;
    result        = StringUtil::split(str, ",", opt);
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[3], "");
}

TEST(StringUtilTest, Starts) {
    std::string        str = "Hello World";
    StringUtil::Option opt;

    EXPECT_TRUE(StringUtil::starts(str, "Hello"));
    EXPECT_FALSE(StringUtil::starts(str, "hello"));

    opt.sensitive = false;
    EXPECT_TRUE(StringUtil::starts(str, "hello", opt));
}

TEST(StringUtilTest, Ends) {
    std::string        str = "Hello World";
    StringUtil::Option opt;

    EXPECT_TRUE(StringUtil::ends(str, "World"));
    EXPECT_FALSE(StringUtil::ends(str, "world"));

    opt.sensitive = false;
    EXPECT_TRUE(StringUtil::ends(str, "world", opt));
}
