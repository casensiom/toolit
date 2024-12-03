#pragma once

#include <string>
#include <vector>

namespace cam::parser {

class Tokenizer {
public:
    Tokenizer(const std::string &content = "") : content(content), currentPos(0), prevPos(0) {
    }

    void          set(const std::string &data);
    bool          eof() const;
    unsigned char peek() const;
    unsigned char peekNext() const;
    unsigned char advance();
    bool          advanceIfEqual(unsigned char val);
    size_t        length() const;
    std::string   consume();
    void          cancel();
    void          reset();

    std::string consume(size_t len);
    std::string consumeString();
    size_t      consumeInteger();
    float       consumeFloat();

    std::vector<std::string> consumeStringList(const std::string &delim = " ");
    std::vector<size_t>      consumeIntegerList(const std::string &delim = " ");
    std::vector<float>       consumeFloatList(const std::string &delim = " ");

    bool isAlpha(unsigned char chr);
    bool isNumeric(unsigned char chr);
    bool isAlphaNum(unsigned char chr);
    bool isSpace(unsigned char chr);
    bool isEndLine(unsigned char chr);

private:
    std::string content;
    size_t      currentPos;
    size_t      prevPos;
};

}    // namespace cam::parser
