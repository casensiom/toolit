#pragma once

#include <string>
#include <map>
#include <regex>
#include <iostream>

#if defined(__clang__) || defined(__GNUC__)
#    define FUNC_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#    define FUNC_SIGNATURE __FUNCSIG__
#    if __cplusplus < 201703L
#        error "Unsupported c++ version, this code needs C++17 at least. Use the flag /std:c++17";
#    endif
#else
#    error "Unsupported compiler, this code works on GCC, CLANG or MSVC.";
#endif

namespace cam::util {

class CommonUtil {
public:
    /// @brief Gets the name of an enumerator
    ///
    /// When invoked as CommonUtil::getEnumName<Enumerator::VALUE>()
    /// It will return the string containing "Enumerator::VALUE"
    /// @tparam key Value of an enum
    /// @return String with the full namespace of the value.
    template<auto key>
    static std::string
    getEnumName() {
        using T = decltype(key);
        static_assert(std::is_enum<T>::value, "Key must be an enum type.");
        return getKeyName(FUNC_SIGNATURE);
    }

private:
    static std::string
    getKeyName(const std::string &line) noexcept {
        // These are examples of 'line' content on different compilers.
        // gcc:   static std::string cam::util::CommonUtil::enumName() [with auto key = MyEnum::Value1]
        // clang: static std::string cam::util::CommonUtil::enumName() [key = MyEnum::Value1]
        // mscv:  static std::string __thiscall cam::util::CommonUtil::enumName<MyEnum::Value1>()

        std::string result;
        std::smatch captures;
        std::regex  pattern("[\\[<](.+=\\s*)?(([a-zA-Z_][a-zA-Z0-9_()]+::)*([a-zA-Z_][a-zA-Z0-9_]+))[\\]>]");

        if(regex_search(line, captures, pattern) && captures.size() == 5) {
            result = captures[2].str();
        }
        return result;
    }
};

}    // namespace cam::util
