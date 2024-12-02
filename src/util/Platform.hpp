#ifndef DIRENT_H
#define DIRENT_H

#if !defined(_WIN32)

#    include <dirent.h>
#    include <sys/stat.h>
#    include <unistd.h>

#    define makedir(str) mkdir((str), 0700)
#    define removedir    remove

#else

#    include <direct.h>

#    define NOMINMAX
#    include <wtypes.h>

constexpr auto DT_UNKNOWN = 0;
constexpr auto DT_FIFO    = 1;
constexpr auto DT_CHR     = 2;
constexpr auto DT_DIR     = 4;
constexpr auto DT_BLK     = 6;
constexpr auto DT_REG     = 8;
constexpr auto DT_LNK     = 10;
constexpr auto DT_SOCK    = 12;
constexpr auto DT_WHT     = 14;

constexpr auto DIRENT_MAX_PATH = 1024;

typedef struct dirent {
    unsigned int     d_type;                      /* file type, see above */
    char             d_name[DIRENT_MAX_PATH + 1]; /* current dir entry (multi-byte char string) */
    WIN32_FIND_DATAA data;                        /* file attributes */
} dirent;

typedef struct DIR {
    dirent current;                   /* Current directory entry */
    int    cached;                    /* Indicates un-processed entry in memory */
    HANDLE search_handle;             /* File search handle */
    char   patt[DIRENT_MAX_PATH + 3]; /* search pattern (3 = pattern + "\\*\0") */
} DIR;

// Forward declarations
DIR           *opendir(const char *dirname);
struct dirent *readdir(DIR *dirp);
int            closedir(DIR *dirp);
void           rewinddir(DIR *dirp);

#    define makedir   _mkdir
#    define removedir _rmdir

#endif

#endif
