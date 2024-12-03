#include <parser/Tokenizer.hpp>

#include <gtest/gtest.h>

using namespace cam::parser;

TEST(TokenizerTest, SetInitializesContentAndResetsPositions) {
    Tokenizer tokenizer("hello");
    tokenizer.set("world");

    EXPECT_EQ(tokenizer.eof(), false);    // Verifies that tokenizer is not at the end
    EXPECT_EQ(tokenizer.peek(), 'w');     // The first character is 'w'
    EXPECT_EQ(tokenizer.length(), 0);     // No token consumed yet
}

TEST(TokenizerTest, EofReturnsTrueAtEndOfContent) {
    Tokenizer tokenizer("hello");
    EXPECT_FALSE(tokenizer.eof());    // Not a the end
    tokenizer.advance();              // Advances to 'h'
    tokenizer.advance();              // Advances to 'e'
    tokenizer.advance();              // Advances to 'l'
    tokenizer.advance();              // Advances to 'l'
    tokenizer.advance();              // Advances to 'o'
    EXPECT_TRUE(tokenizer.eof());     // After advancing all characters, we should be at the end
}

TEST(TokenizerTest, PeekReturnsCurrentCharacter) {
    Tokenizer tokenizer("hello");
    tokenizer.advance();                 // Advances to 'h'
    EXPECT_EQ(tokenizer.peek(), 'e');    // Peeks at the current character, which should be 'e'
}

TEST(TokenizerTest, PeekNextReturnsNextCharacter) {
    Tokenizer tokenizer("hello");
    tokenizer.advance();                     // Advances to 'h'
    EXPECT_EQ(tokenizer.peekNext(), 'l');    // Peeks at the next character, which should be 'l'
}

TEST(TokenizerTest, PeekNextAtEnd) {
    Tokenizer tokenizer("hello");
    tokenizer.advance();                      // 'h'
    tokenizer.advance();                      // 'e'
    tokenizer.advance();                      // 'l'
    tokenizer.advance();                      // 'l'
    tokenizer.advance();                      // 'o'
    EXPECT_EQ(tokenizer.peekNext(), '\0');    // At the end of the content, peekNext should return '\0'
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

TEST(TokenizerTest, AdvanceIfEqualAdvancesIfMatchAndReturnsTrue) {
    Tokenizer tokenizer("hello");
    EXPECT_TRUE(tokenizer.advanceIfEqual('h'));     // Advances because 'h' matches
    EXPECT_EQ(tokenizer.peek(), 'e');               // Current character is now 'e'
    EXPECT_FALSE(tokenizer.advanceIfEqual('z'));    // No advance since 'z' does not match
    EXPECT_EQ(tokenizer.peek(), 'e');               // Current character is still 'e'
}

TEST(TokenizerTest, AdvanceIfEqualAtEnd) {
    Tokenizer tokenizer("hello");
    tokenizer.advance();                            // 'h'
    tokenizer.advance();                            // 'e'
    tokenizer.advance();                            // 'l'
    tokenizer.advance();                            // 'l'
    tokenizer.advance();                            // 'o'
    EXPECT_FALSE(tokenizer.advanceIfEqual('o'));    // At the end of the text, it should not advance
    EXPECT_TRUE(tokenizer.eof());                   // Verifies we are at the end
}

TEST(TokenizerTest, LengthReturnsCorrectTokenLength) {
    Tokenizer tokenizer("hello");
    tokenizer.advance();                 // 'h'
    tokenizer.advance();                 // 'e'
    EXPECT_EQ(tokenizer.length(), 2);    // Length should be 2 ('he')
    tokenizer.advance();                 // 'l'
    EXPECT_EQ(tokenizer.length(), 3);    // Length should be 3 ('hel')
}

TEST(TokenizerTest, ConsumeUpdatesPrevPosAndReturnsToken) {
    Tokenizer tokenizer("hello world");
    tokenizer.advance();                       // Stores 'h'
    tokenizer.advance();                       // Stores 'e'
    tokenizer.advance();                       // Stores 'l'
    tokenizer.advance();                       // Stores 'l'
    EXPECT_EQ(tokenizer.consume(), "hell");    // Consumes from prevPos (0) until currentPos (4)
    EXPECT_EQ(tokenizer.consume(), "");        // Consumes nothing (no advance methods invoked)
    EXPECT_EQ(tokenizer.peek(), 'o');          // CurrentPos points to 'o'
}

TEST(TokenizerTest, CancelRestoresPrevPos) {
    Tokenizer tokenizer("hello");
    tokenizer.advance();                 // 'h'
    tokenizer.advance();                 // 'e'
    EXPECT_EQ(tokenizer.length(), 2);    // Length of "he"

    tokenizer.cancel();    // Cancels, prevPos and currentPos should be equal

    EXPECT_EQ(tokenizer.peek(), 'h');    // prevPos should be equal to currentPos
    EXPECT_EQ(tokenizer.length(), 0);    // Length should be 0 since no token was consumed
}

TEST(TokenizerTest, ConsumeSizeLen) {
    Tokenizer tokenizer("hello world");
    EXPECT_EQ(tokenizer.consume(5), "hello");    // Consumes the first 5 characters
    EXPECT_EQ(tokenizer.peek(), ' ');            // After consuming, there should be a space
    EXPECT_EQ(tokenizer.consume(5), " worl");    // Consumes the next 5 characters
    EXPECT_EQ(tokenizer.consume(1), "d");        // Consumes the last character
}

TEST(TokenizerTest, ConsumeStringReturnsParsedString) {
    Tokenizer tokenizer("hello123 456world ");
    EXPECT_EQ(tokenizer.consumeString(), "hello123");    // Should consume "hello123" and return it
    EXPECT_EQ(tokenizer.peek(), ' ');                    // After consuming, there should be a space
    EXPECT_EQ(tokenizer.consumeString(), "456world");    // Should consume "456world" and return it
    EXPECT_EQ(tokenizer.peek(), ' ');                    // After consuming, there should be a space
    EXPECT_EQ(tokenizer.consumeString(), "");            // Should consume nothing
}

TEST(TokenizerTest, ConsumeIntegerReturnsParsedInteger) {
    Tokenizer tokenizer("1234 -5678");
    EXPECT_EQ(tokenizer.consumeInteger(), 1234);    // Should consume "1234" and return the integer 1234
    tokenizer.advanceIfEqual(' ');
    EXPECT_EQ(tokenizer.consumeInteger(), -5678);    // Should handle negative integers
}

TEST(TokenizerTest, ConsumeFloatReturnsParsedFloat) {
    Tokenizer tokenizer("12.34 -56.78");
    EXPECT_FLOAT_EQ(tokenizer.consumeFloat(), 12.34f);    // Should consume "12.34" and return the float 12.34
    tokenizer.advanceIfEqual(' ');
    EXPECT_FLOAT_EQ(tokenizer.consumeFloat(), -56.78f);    // Should handle negative float values
}

TEST(TokenizerTest, ConsumeStringListReturnsListOfStrings) {
    Tokenizer tokenizer("a,b,c");
    auto      result = tokenizer.consumeStringList(",");
    EXPECT_EQ(result.size(), 3);    // Three elements: "a", "b", "c"
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
}

TEST(TokenizerTest, ConsumeIntegerListReturnsListOfIntegers) {
    Tokenizer tokenizer("1,2,3");
    auto      result = tokenizer.consumeIntegerList(",");
    EXPECT_EQ(result.size(), 3);    // Three elements: 1, 2, 3
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST(TokenizerTest, ConsumeFloatListReturnsListOfFloats) {
    Tokenizer tokenizer("1.1,2.2,3.3");
    auto      result = tokenizer.consumeFloatList(",");
    EXPECT_EQ(result.size(), 3);    // Three elements: 1.1, 2.2, 3.3
    EXPECT_FLOAT_EQ(result[0], 1.1);
    EXPECT_FLOAT_EQ(result[1], 2.2);
    EXPECT_FLOAT_EQ(result[2], 3.3);
}

TEST(TokenizerTest, IsAlphaReturnsTrueForAlphabets) {
    Tokenizer tokenizer("hello");
    EXPECT_TRUE(tokenizer.isAlpha('h'));     // 'h' is an alphabet
    EXPECT_FALSE(tokenizer.isAlpha('1'));    // '1' is not an alphabet
}

TEST(TokenizerTest, IsNumericReturnsTrueForDigits) {
    Tokenizer tokenizer("1234");
    EXPECT_TRUE(tokenizer.isNumeric('1'));     // '1' is a numeric character
    EXPECT_FALSE(tokenizer.isNumeric('a'));    // 'a' is not numeric
}

TEST(TokenizerTest, IsAlphaNumReturnsTrueForAlphanumeric) {
    Tokenizer tokenizer("hello123");
    EXPECT_TRUE(tokenizer.isAlphaNum('h'));     // 'h' is alphanumeric
    EXPECT_TRUE(tokenizer.isAlphaNum('1'));     // '1' is alphanumeric
    EXPECT_FALSE(tokenizer.isAlphaNum('#'));    // '#' is not alphanumeric
}

TEST(TokenizerTest, IsSpaceReturnsTrueForWhitespace) {
    Tokenizer tokenizer(" \t\r");
    EXPECT_TRUE(tokenizer.isSpace(' '));     // ' ' is a space
    EXPECT_TRUE(tokenizer.isSpace('\t'));    // '\t' is a space
    EXPECT_FALSE(tokenizer.isSpace('a'));    // 'a' is not a space
}

TEST(TokenizerTest, IsEndLineReturnsTrueForNewline) {
    Tokenizer tokenizer("\n");
    EXPECT_TRUE(tokenizer.isEndLine('\n'));    // Newline character should return true
    EXPECT_FALSE(tokenizer.isEndLine(' '));    // Space character should return false
}
