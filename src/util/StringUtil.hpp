#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace cam::util {

class StringUtil {
public:
    struct Option {
        Option(bool sensitive = true, bool keepEmpty = false, size_t from = 0) : sensitive(sensitive), keepEmpty(keepEmpty), from(from) {
        }

        bool   sensitive;
        bool   keepEmpty;
        size_t from;
    };

    static std::string toUpper(const std::string &str);
    static std::string toLower(const std::string &str);
    static std::string trim(const std::string &str);
    static std::string ltrim(const std::string &str);
    static std::string rtrim(const std::string &str);
    static std::string substr(const std::string &str, size_t pos, size_t len);
    static std::string replace(const std::string &str, const std::string &what, const std::string &with, const Option &option = {});

    static size_t count(const std::string &str, const std::string &piece, const Option &option = {});
    static size_t find(const std::string &str, const std::string &piece, const Option &option = {});

    static std::vector<std::string> split(const std::string &str, const std::string &delim, const Option &option = {});
    static std::string              join(const std::vector<std::string> &items, const std::string &glue);

    static bool starts(const std::string &str, const std::string &separator, const Option &option = {});
    static bool ends(const std::string &str, const std::string &separator, const Option &option = {});
};

}    // namespace cam::util
