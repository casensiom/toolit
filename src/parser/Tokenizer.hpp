#pragma once

#include <string>
#include <vector>

namespace cam::parser {

class Tokenizer {
public:
    Tokenizer(const std::string &content = "") : content(content), currentPos(0), prevPos(0) {
    }

    void set(const std::string &data);    // sets the data and initializes the tokenizer

    bool          eof() const;                          // Checks if there is more data to parse
    unsigned char peek() const;                         // Peeks the current char on the tokenizer
    unsigned char peekNext() const;                     // Peeks the next char on the tokenizer
    unsigned char advance();                            // Advances one char
    bool          advanceIfEqual(unsigned char val);    // Advances one char only if it coincides
    size_t        length() const;                       // gives the current length of the current token
    std::string   consume();                            // gives the token and set up to read the next token
    void          cancel();                             // cancel the current token
    void          reset();                              // reset the tokenizer

    std::string consumeAll();           // consumes everything else
    std::string consume(size_t len);    // consumes a fixed size token
    std::string consumeString();        // consumes an string token
    int64_t     consumeInteger();       // consumes an integer token
    float       consumeFloat();         // consumes a float token

    std::vector<std::string> consumeStringList(const std::string &delim = " ");
    std::vector<int64_t>     consumeIntegerList(const std::string &delim = " ");
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
