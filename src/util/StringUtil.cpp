#include "StringUtil.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace cam::util {

static std::string
toCase(const std::string &str, bool toUpper) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), toUpper ? ::toupper : ::tolower);
    return result;
}

std::string
StringUtil::toUpper(const std::string &str) {
    return toCase(str, true);
}

std::string
StringUtil::toLower(const std::string &str) {
    return toCase(str, false);
}

std::string
StringUtil::trim(const std::string &str) {
    return ltrim(rtrim(str));
}

std::string
StringUtil::ltrim(const std::string &str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string
StringUtil::rtrim(const std::string &str) {
    size_t end = str.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string
StringUtil::substr(const std::string &str, size_t pos, size_t len) {
    if(pos >= str.size())
        return "";
    return str.substr(pos, len);
}

std::string
StringUtil::replace(const std::string &str, const std::string &what, const std::string &with, const Option &option) {
    if(what.empty()) {
        return str;
    }

    std::string result = str;
    size_t      pos    = option.from;
    std::string source = option.sensitive ? str : toLower(str);
    std::string target = option.sensitive ? what : toLower(what);

    while((pos = source.find(target, pos)) != std::string::npos) {
        std::string spaces(pos, ' ');
        source.replace(pos, target.length(), with);
        result.replace(pos, target.length(), with);
        pos += with.length();
    }

    return result;
}

size_t
StringUtil::count(const std::string &str, const std::string &piece, const Option &option) {
    std::string source = option.sensitive ? str : toLower(str);
    std::string target = option.sensitive ? piece : toLower(piece);

    size_t count = 0;
    size_t pos   = source.find(target, option.from);
    while(pos != std::string::npos) {
        ++count;
        pos = source.find(target, pos + target.length());
    }
    return count;
}

size_t
StringUtil::find(const std::string &str, const std::string &piece, const Option &option) {
    std::string source = option.sensitive ? str : toLower(str);
    std::string target = option.sensitive ? piece : toLower(piece);

    return source.find(target, option.from);
}

std::vector<std::string>
StringUtil::split(const std::string &str, const std::string &delim, const Option &option) {
    std::vector<std::string> result;
    size_t                   start = option.from;
    size_t                   end;

    while((end = str.find(delim, start)) != std::string::npos) {
        std::string token = str.substr(start, end - start);
        if(option.keepEmpty || !token.empty()) {
            result.push_back(option.sensitive ? token : toLower(token));
        }
        start = end + delim.length();
    }

    if(option.keepEmpty || start < str.size()) {
        std::string token = str.substr(start);
        result.push_back(option.sensitive ? token : toLower(token));
    }
    return result;
}

bool
StringUtil::starts(const std::string &str, const std::string &separator, const Option &option) {
    if(separator.size() > str.size())
        return false;

    std::string prefix = str.substr(0, separator.size());
    if(!option.sensitive) {
        prefix = toLower(prefix);
    }
    return prefix == (option.sensitive ? separator : toLower(separator));
}

bool
StringUtil::ends(const std::string &str, const std::string &separator, const Option &option) {
    if(separator.size() > str.size())
        return false;

    std::string suffix = str.substr(str.size() - separator.size());
    if(!option.sensitive) {
        suffix = toLower(suffix);
    }
    return suffix == (option.sensitive ? separator : toLower(separator));
}

}    // namespace cam::util