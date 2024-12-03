#include "FileUtil.hpp"
#include "StringUtil.hpp"
#include "Platform.hpp"

#include <algorithm>
#include <fstream>
#include <sys/stat.h>

namespace cam::util {
bool
FileUtil::fileExist(const std::string &path) {
    std::ifstream f(path.c_str());
    return f.good();
}

bool
FileUtil::fileWrite(const std::string &path, const std::string &content) {
    std::ofstream file(path, std::ofstream::out);
    if(!file.is_open()) {
        return false;
    }
    file << content;
    file.close();
    return true;
}

bool
FileUtil::fileWrite(const std::string &path, const std::vector<uint8_t> &content) {
    std::ofstream file(path, std::ofstream::out | std::ofstream::binary);
    if(!file.is_open()) {
        return false;
    }
    file.write(reinterpret_cast<const char *>(content.data()), content.size());
    file.close();
    return true;
}

std::vector<uint8_t>
FileUtil::fileRead(const std::string &file_path) {
    std::ifstream        instream(file_path, std::ifstream::in | std::ifstream::binary);
    std::vector<uint8_t> data;
    if(instream.is_open()) {
        data = std::vector<uint8_t>(std::istreambuf_iterator<char>(instream), std::istreambuf_iterator<char>());
        instream.close();
    }
    return data;
}

size_t
FileUtil::fileSize(const std::string &filePath) {
    size_t        fileSize = 0;
    std::ifstream file(filePath, std::ifstream::ate | std::ifstream::binary);
    if(!file.is_open()) {
        return fileSize;
    }
    fileSize = file.tellg();
    file.close();

    return fileSize;
}

bool
FileUtil::fileRemove(const std::string &path) {
    int error;
    error = std::remove(path.c_str());
    return (error == 0);
}

bool
FileUtil::dirCreate(const std::string &path) {
    int error;
    error = makedir(path.c_str());
    return (error == 0);
}

bool
FileUtil::dirExist(const std::string &path) {
    if(DIR *entry = opendir(path.c_str()); entry != nullptr) {
        closedir(entry);
        return true;
    }
    return false;
}

bool
FileUtil::dirDeleteEmpty(const std::string &path) {
    int error;
    error = removedir(path.c_str());
    return (error == 0);
}

bool
FileUtil::dirDelete(const std::string &path) {
    DIR *dir = opendir(path.c_str());
    if(dir == nullptr) {
        return false;
    }

    bool          error = false;
    const dirent *entry;
    while((entry = readdir(dir)) != nullptr) {
        std::string name(entry->d_name);
        if(name == "." || name == "..") {
            continue;
        }

        std::string file_path = path + "/" + name;
        // This check is needed by unix systems, to keep the entry updated
        if(struct stat info; stat(file_path.c_str(), &info) != 0) {
            continue;
        }

        if(entry->d_type == DT_DIR) {
            error |= !dirDelete(file_path);
        } else {
            error |= !fileRemove(file_path);
        }
    }
    closedir(dir);

    error |= !dirDeleteEmpty(path);

    return !error;
}

std::vector<FileUtil::FileEntry>
FileUtil::dirContent(const std::string &path) {
    std::vector<FileEntry> ret;
    DIR                   *dir = opendir(path.c_str());
    if(dir == nullptr) {
        return ret;
    }

    const dirent *entry;
    while((entry = readdir(dir)) != nullptr) {
        std::string name(entry->d_name);
        if(name == "." || name == "..") {
            continue;
        }

        FileEntry fileEntry;
        fileEntry.name = name;
        fileEntry.type = (entry->d_type == DT_DIR) ? FileEntryType::DIRECTORY : FileEntryType::FILE;
        ret.push_back(fileEntry);
    }
    closedir(dir);
    return ret;
}

std::vector<std::string>
FileUtil::pathComponents(const std::string &path) {
    std::string        url = StringUtil::replace(path, "\\", "/");
    StringUtil::Option opt;
    return StringUtil::split(url, "/");
}

std::string
FileUtil::pathComponents(const std::string &path, int comp) {
    auto   list       = FileUtil::pathComponents(path);
    size_t components = list.size();

    size_t size = std::min(static_cast<size_t>(std::abs(comp)), list.size());
    if(comp > 0) {
        list.erase(list.begin() + size, list.end());
    } else {
        list.erase(list.begin(), list.end() - size);
    }

    std::string base = "";
    if(!path.empty() && path[0] == '/' && (comp >= 0 || (comp < 0 && abs(comp) >= components))) {    // not set it when removing from left
        base = "/";
    }

    return base + StringUtil::join(list, "/");
}

size_t
FileUtil::pathComponentCount(const std::string &path) {
    auto list = FileUtil::pathComponents(path);
    return list.size();
}

std::string
FileUtil::pathComponentAt(const std::string &path, size_t index) {
    auto        list = FileUtil::pathComponents(path);
    std::string ret;
    if(index < list.size()) {
        ret = list[index];
    }
    return ret;
}

std::string
FileUtil::pathRemoveComponents(const std::string &path, int comp) {
    auto   list       = FileUtil::pathComponents(path);
    size_t components = list.size();

    size_t size = std::min(static_cast<size_t>(std::abs(comp)), list.size());
    if(comp < 0) {
        list.erase(list.begin(), list.begin() + size);
    } else {
        list.erase(list.end() - size, list.end());
    }

    std::string base = "";
    if(!path.empty() && path[0] == '/' && (comp >= 0 || (comp < 0 && abs(comp) >= components))) {    // not set it when removing from left
        base = "/";
    }

    return base + StringUtil::join(list, "/");
}

}    // namespace cam::util