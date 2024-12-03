
#include <util/FileUtil.hpp>

#include <gtest/gtest.h>

using namespace cam::util;

#ifdef _WIN32
#    define BASE_PATH "c:"
#else
#    define BASE_PATH
#endif

TEST(FileUtil, file_api) {
    const char          *path    = BASE_PATH "/tmp/temp.txt";
    std::string          content = "Hello, World!";
    std::vector<uint8_t> content_vector(content.begin(), content.end());

    ASSERT_FALSE(FileUtil::fileExist(path));

    ASSERT_FALSE(FileUtil::fileWrite("", content));
    ASSERT_TRUE(FileUtil::fileWrite(path, content));
    ASSERT_TRUE(FileUtil::fileExist(path));
    ASSERT_EQ(FileUtil::fileSize(path), content.length());

    ASSERT_FALSE(FileUtil::fileWrite("", content_vector));
    ASSERT_TRUE(FileUtil::fileWrite(path, content_vector));
    ASSERT_TRUE(FileUtil::fileExist(path));
    ASSERT_EQ(FileUtil::fileSize(path), content_vector.size());

    ASSERT_FALSE(FileUtil::fileRead(path).empty());

    ASSERT_TRUE(FileUtil::fileRemove(path));
    ASSERT_FALSE(FileUtil::fileExist(path));

    ASSERT_EQ(FileUtil::fileSize(path), 0);
}

TEST(FileUtil, dir_api) {
    const char *path = BASE_PATH "/tmp/custom";

    ASSERT_FALSE(FileUtil::dirExist(path));
    ASSERT_TRUE(FileUtil::dirCreate(path));
    ASSERT_TRUE(FileUtil::dirExist(path));

    ASSERT_TRUE(FileUtil::dirContent(path).empty());

    const char *path2   = BASE_PATH "/tmp/custom/temp.txt";
    std::string content = "Hello, World!\n";
    ASSERT_TRUE(FileUtil::fileWrite(path2, content));

    ASSERT_TRUE(FileUtil::dirCreate(BASE_PATH "/tmp/custom/second"));

    ASSERT_FALSE(FileUtil::dirContent(path).empty());
    ASSERT_TRUE(FileUtil::dirDelete(path));
    ASSERT_FALSE(FileUtil::dirExist(path));
    ASSERT_TRUE(FileUtil::dirContent(path).empty());
}

TEST(FileUtil, path_api) {
    std::string              path       = "/root/folder1\\folder2/name.ext";
    std::vector<std::string> components = FileUtil::pathComponents(path);
    EXPECT_EQ(components[0], "root");
    EXPECT_EQ(components[1], "folder1");
    EXPECT_EQ(components[2], "folder2");
    EXPECT_EQ(components[3], "name.ext");
    EXPECT_EQ(components.size(), 4);

    EXPECT_EQ((FileUtil::pathComponentCount(path)), 4);

    EXPECT_EQ((FileUtil::pathComponentAt(path, 0)), "root");
    EXPECT_EQ((FileUtil::pathComponentAt(path, 1)), "folder1");
    EXPECT_EQ((FileUtil::pathComponentAt(path, 2)), "folder2");
    EXPECT_EQ((FileUtil::pathComponentAt(path, 3)), "name.ext");

    EXPECT_EQ((FileUtil::pathComponents(path, 0)), "/");
    EXPECT_EQ((FileUtil::pathComponents(path, 1)), "/root");
    EXPECT_EQ((FileUtil::pathComponents(path, 2)), "/root/folder1");
    EXPECT_EQ((FileUtil::pathComponents(path, 3)), "/root/folder1/folder2");
    EXPECT_EQ((FileUtil::pathComponents(path, 4)), "/root/folder1/folder2/name.ext");
    EXPECT_EQ((FileUtil::pathComponents(path, 5)), "/root/folder1/folder2/name.ext");
    EXPECT_EQ((FileUtil::pathComponents(path, -5)), "/root/folder1/folder2/name.ext");
    EXPECT_EQ((FileUtil::pathComponents(path, -4)), "/root/folder1/folder2/name.ext");
    EXPECT_EQ((FileUtil::pathComponents(path, -3)), "folder1/folder2/name.ext");
    EXPECT_EQ((FileUtil::pathComponents(path, -2)), "folder2/name.ext");
    EXPECT_EQ((FileUtil::pathComponents(path, -1)), "name.ext");

    EXPECT_EQ((FileUtil::pathRemoveComponents(path, 0)), "/root/folder1/folder2/name.ext");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, 1)), "/root/folder1/folder2");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, 2)), "/root/folder1");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, 3)), "/root");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, 4)), "/");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, 5)), "/");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, -5)), "/");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, -4)), "/");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, -3)), "name.ext");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, -2)), "folder2/name.ext");
    EXPECT_EQ((FileUtil::pathRemoveComponents(path, -1)), "folder1/folder2/name.ext");
}
