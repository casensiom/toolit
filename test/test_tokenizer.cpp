#include <gtest/gtest.h>

#include <parser/Tokenizer.hpp>

using namespace cam::parser;

TEST(TokenizerTest, EofTest) {
    Tokenizer tokenizer("");
    EXPECT_TRUE(tokenizer.eof());

    Tokenizer tokenizer2("Hello");
    EXPECT_FALSE(tokenizer2.eof());
}

TEST(TokenizerTest, PeekTest) {
    Tokenizer tokenizer("Hello");
    EXPECT_EQ(tokenizer.peek(), 'H');
    tokenizer.advance();
    EXPECT_EQ(tokenizer.peek(), 'e');
}

TEST(TokenizerTest, PeekNextTest) {
    Tokenizer tokenizer("Hello");
    EXPECT_EQ(tokenizer.peekNext(), 'e');
    tokenizer.advance();
    EXPECT_EQ(tokenizer.peekNext(), 'l');
    tokenizer.advance();
    tokenizer.advance();
    EXPECT_EQ(tokenizer.peekNext(), 'o');
}

TEST(TokenizerTest, AdvanceTest) {
    Tokenizer tokenizer("Hello");
    EXPECT_EQ(tokenizer.advance(), 'H');
    EXPECT_EQ(tokenizer.advance(), 'e');
    EXPECT_EQ(tokenizer.advance(), 'l');
    EXPECT_EQ(tokenizer.advance(), 'l');
    EXPECT_EQ(tokenizer.advance(), 'o');
    EXPECT_EQ(tokenizer.advance(), '\0');    // EOF
}

TEST(TokenizerTest, AdvanceIfEqualTest) {
    Tokenizer tokenizer("Hello");
    EXPECT_TRUE(tokenizer.advanceIfEqual('H'));
    EXPECT_FALSE(tokenizer.advanceIfEqual('x'));    // Doesn't match 'e'
    EXPECT_EQ(tokenizer.peek(), 'e');
}

TEST(TokenizerTest, ConsumeTest) {
    Tokenizer tokenizer("Hello World!");
    tokenizer.advance();                       // Move to 'e'
    tokenizer.advance();                       // Move to 'l'
    tokenizer.advance();                       // Move to second 'l'
    tokenizer.advance();                       // Move to second 'o'
    EXPECT_EQ(tokenizer.consume(), "Hell");    // Consumes "Hell" (prevPos to currentPos) excludes 'o'
    EXPECT_EQ(tokenizer.peek(), 'o');
}

TEST(TokenizerTest, ResetTest) {
    Tokenizer tokenizer("Hello");
    tokenizer.advance();    // Move to 'e'
    tokenizer.advance();    // Move to 'l'
    tokenizer.reset();      // Reset to previous position
    EXPECT_EQ(tokenizer.peek(), 'H');
    EXPECT_EQ(tokenizer.consume(), "");    // Consume the reset part
}
