#include "Tokenizer.hpp"

#include <util/StringUtil.hpp>

using namespace cam::util;

namespace cam::parser {

bool
Tokenizer::eof() const {
    return currentPos >= (content.size() - 1);
}

unsigned char
Tokenizer::peek() const {
    if(eof()) {
        return '\0';
    }
    return content[currentPos];
}

unsigned char
Tokenizer::peekNext() const {
    if((currentPos + 1) >= (content.size() - 1)) {
        return '\0';
    }
    return content[currentPos + 1];
}

unsigned char
Tokenizer::advance() {
    if(eof()) {
        return '\0';
    }
    currentPos++;
    return content[currentPos];
}

bool
Tokenizer::advanceIfEqual(unsigned char val) {
    unsigned char next = advance();
    if(next != val) {
        currentPos--;
        return false;
    }
    return true;
}

std::string
Tokenizer::consume() {
    size_t len = (currentPos - prevPos);
    return StringUtil::substr(content, currentPos, len);
}

void
Tokenizer::reset() {
    currentPos = prevPos;
}

std::string
Tokenizer::consume(size_t len) {
    printf("[ERROR] 'consume' Not implemented yet\n");
    return "";
}

std::string
Tokenizer::consumeString() {
    printf("[ERROR] 'consumeString' Not implemented yet\n");
    return "";
}

size_t
Tokenizer::consumeInteger() {
    printf("[ERROR] 'consumeInteger' Not implemented yet\n");
    return 0;
}

float
Tokenizer::consumeFloat() {
    printf("[ERROR] 'consumeFloat' Not implemented yet\n");
    return 0;
}

std::vector<std::string>
Tokenizer::consumeStringList() {
    printf("[ERROR] 'consumeStringList' Not implemented yet\n");
    return {};
}
std::vector<size_t>
Tokenizer::consumeIntegerList() {
    printf("[ERROR] 'consumeIntegerList' Not implemented yet\n");
    return {};
}
std::vector<float>
Tokenizer::consumeFloatList() {
    printf("[ERROR] 'consumeFloatList' Not implemented yet\n");
    return {};
}

}    // namespace cam::parser
