#pragma once

#include <string>
#include <vector>

namespace cam::parser {

class Tokenizer {
public:
    Tokenizer(const std::string &content) : content(content), currentPos(0), prevPos(0) {
    }

    bool          eof() const;
    unsigned char peek() const;
    unsigned char peekNext() const;
    unsigned char advance();
    bool          advanceIfEqual(unsigned char val);
    std::string   consume();
    void          reset();

    std::string consume(size_t len);
    std::string consumeString();
    size_t      consumeInteger();
    float       consumeFloat();

    std::vector<std::string> consumeStringList();
    std::vector<size_t>      consumeIntegerList();
    std::vector<float>       consumeFloatList();

private:
    std::string content;
    size_t      currentPos;
    size_t      prevPos;
};

}    // namespace cam::parser
