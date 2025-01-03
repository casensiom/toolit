#include "Tokenizer.hpp"

#include <util/StringUtil.hpp>

using namespace cam::util;

namespace cam::parser {

void
Tokenizer::set(const std::string &data) {
    content = data;
    reset();
}

bool
Tokenizer::eof() const {
    return currentPos >= content.size();
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
    if(currentPos + 1 >= content.size()) {
        return '\0';
    }
    return content[currentPos + 1];
}

unsigned char
Tokenizer::advance() {
    if(eof()) {
        return '\0';
    }
    return content[currentPos++];
}

bool
Tokenizer::advanceIfEqual(unsigned char val) {
    if(eof()) {
        return false;
    }
    unsigned char next = advance();
    if(next != val) {
        currentPos--;
        return false;
    }
    return true;
}

size_t
Tokenizer::length() const {
    return (currentPos - prevPos);
}

std::string
Tokenizer::consume() {
    size_t      len   = currentPos - prevPos;
    std::string token = StringUtil::substr(content, prevPos, len);
    prevPos           = currentPos;
    return token;
}

void
Tokenizer::cancel() {
    currentPos = prevPos;
}

void
Tokenizer::reset() {
    currentPos = prevPos = 0;
}

std::string
Tokenizer::consume(size_t len) {
    std::string token = StringUtil::substr(content, prevPos, len);
    prevPos += token.size();
    currentPos = prevPos;
    return token;
}


std::string
Tokenizer::consumeAll() {
    std::string token = StringUtil::substr(content, currentPos, content.size() - currentPos);
    prevPos += content.size();
    currentPos = prevPos;
    return token;
}

std::string
Tokenizer::consumeString() {
    // ignore all previous spaces
    while(!eof() && isSpace(peek())) {
        advance();
    }
    consume();

    // capture until space or eof
    while(!eof() && !isSpace(peek())) {
        advance();
    }
    return consume();
}

int64_t
Tokenizer::consumeInteger() {
    int64_t ret = 0;
    if(peek() == '-') {
        advance();
    }
    while(isNumeric(peek())) {
        advance();
    }
    if(length() > 0) {
        ret = std::stoll(consume());
    }
    return ret;
}

float
Tokenizer::consumeFloat() {
    float ret = 0;
    if(peek() == '-') {
        advance();
    }
    while(isNumeric(peek())) {
        advance();
    }
    if(peek() == '.' && isNumeric(peekNext())) {
        advance();
        while(isNumeric(peek())) {
            advance();
        }
    }
    if(length() > 0) {
        ret = std::stof(consume());
    }
    return ret;
}

std::vector<std::string>
Tokenizer::consumeStringList(const std::string &delim) {
    return StringUtil::split(consumeAll(), delim);
}

std::vector<int64_t>
Tokenizer::consumeIntegerList(const std::string &delim) {
    std::vector<int64_t> ret;
    auto                 items = StringUtil::split(consumeAll(), delim);
    for(const auto &it : items) {
        ret.push_back(std::stoll(it));
    }
    return ret;
}

std::vector<float>
Tokenizer::consumeFloatList(const std::string &delim) {
    std::vector<float> ret;
    auto               items = StringUtil::split(consumeAll(), delim);
    for(const auto &it : items) {
        ret.push_back(std::stof(it));
    }
    return ret;
}

bool
Tokenizer::isAlpha(unsigned char chr) {
    return ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'));
}

bool
Tokenizer::isNumeric(unsigned char chr) {
    return (chr >= '0' && chr <= '9');
}

bool
Tokenizer::isAlphaNum(unsigned char chr) {
    return isAlpha(chr) || isNumeric(chr);
}

bool
Tokenizer::isSpace(unsigned char chr) {
    return (chr == ' ' || chr == '\t' || chr == '\r');
}

bool
Tokenizer::isEndLine(unsigned char chr) {
    return (chr == '\n');
}

}    // namespace cam::parser
