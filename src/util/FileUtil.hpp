#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace cam::util {

class FileUtil {
public:
    enum class FileEntryType { FILE, DIRECTORY };

    using FileEntry = struct file_entry_struct {
        std::string             name;
        FileUtil::FileEntryType type;
    };

    static bool                 fileExist(const std::string &path);
    static bool                 fileWrite(const std::string &path, const std::string &content);
    static bool                 fileWrite(const std::string &path, const std::vector<uint8_t> &content);
    static std::vector<uint8_t> fileRead(const std::string &path);
    static bool                 fileRemove(const std::string &path);
    static size_t               fileSize(const std::string &filePath);

    static bool dirCreate(const std::string &path);
    static bool dirExist(const std::string &path);
    static bool dirDelete(const std::string &path);
    static bool dirDeleteEmpty(const std::string &path);

    static std::vector<FileEntry> dirContent(const std::string &path);

    static std::vector<std::string> pathComponents(const std::string &path);
    static std::string              pathComponents(const std::string &path, int comp);
    static size_t                   pathComponentCount(const std::string &path);
    static std::string              pathComponentAt(const std::string &path, size_t index);
    static std::string              pathRemoveComponents(const std::string &path, int comp);

    static std::string getPath(const std::string &path);
    static std::string getFilename(const std::string &path);
    static std::string getExtension(const std::string &path);
};

}    // namespace cam::util