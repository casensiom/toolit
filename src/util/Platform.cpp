//-------------------------------------
#include "Platform.hpp"
//-------------------------------------

#if defined(_WIN32)

/*****************************************************************************
 * Open directory stream DIRNAME for read and return a pointer to the
 * internal working area that is used to retrieve individual directory
 * entries.
 */
DIR *
opendir(const char *dirname) {
    DIR *dirp;
    if(dirname == 0x0) {
        return 0x0;
    }
    if(strlen(dirname) >= DIRENT_MAX_PATH) {
        return 0x0;
    }

    // construct new DIR structure
    dirp = (DIR *)malloc(sizeof(struct DIR));
    if(dirp != NULL) {
        char *p;

        // take directory name...
        strncpy(dirp->patt, dirname, DIRENT_MAX_PATH);
        dirp->patt[DIRENT_MAX_PATH] = '\0';

        // ... and append search pattern to it
        p = strchr(dirp->patt, '\0');
        // TODO: Esta condición no es correcta. (*(p-1) != '\\' || *(p-1) != '/') dará siempre true! KARLOZ
        if(dirp->patt < p && *(p - 1) != '\\' && *(p - 1) != '/' && *(p - 1) != ':') {
            *p++ = '\\';
        }
        *p++ = '*';
        *p   = '\0';

        // open stream and retrieve first file
        dirp->search_handle = FindFirstFileA(dirp->patt, &dirp->current.data);
        if(dirp->search_handle == INVALID_HANDLE_VALUE) {
            // invalid search pattern?
            free(dirp);
            return 0x0;
        }

        // there is an un-processed directory entry in memory now
        dirp->cached = 1;
    }

    return dirp;
}

/*****************************************************************************
 * Read a directory entry, and return a pointer to a dirent structure
 * containing the name of the entry in d_name field.  Individual directory
 * entries returned by this very function include regular files,
 * sub-directories, pseudo-directories "." and "..", but also volume labels,
 * hidden files and system files may be returned.
 */
struct dirent *
readdir(DIR *dirp) {
    if(dirp == 0x0) {
        return 0x0;
    }

    if(dirp->search_handle == INVALID_HANDLE_VALUE) {
        // directory stream was opened/rewound incorrectly or ended normally
        return 0x0;
    }

    // get next directory entry
    if(dirp->cached != 0) {
        // a valid directory entry already in memory
        dirp->cached = 0;
    } else {
        // read next directory entry from disk
        if(FindNextFileA(dirp->search_handle, &dirp->current.data) == false) {
            // the very last file has been processed or an error occured
            FindClose(dirp->search_handle);
            dirp->search_handle = INVALID_HANDLE_VALUE;
            return 0x0;
        }
    }

    // copy as a multibyte character string
    strncpy(dirp->current.d_name, dirp->current.data.cFileName, DIRENT_MAX_PATH);
    dirp->current.d_name[DIRENT_MAX_PATH] = '\0';

    /// Default type to a normal file
    dirp->current.d_type = DT_REG;

    /// stat the file to get if it's a subdir
    // stat(dirp->current.data->name, &stat_buf);
    if((dirp->current.data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
        dirp->current.d_type = DT_DIR;
    }

    return &dirp->current;
}

/*****************************************************************************
 * Close directory stream opened by opendir() function.  Close of the
 * directory stream invalidates the DIR structure as well as any previously
 * read directory entry.
 */
int
closedir(DIR *dirp) {
    if(dirp == 0x0) {
        return 0x0;
    }

    // release search handle
    if(dirp->search_handle != INVALID_HANDLE_VALUE) {
        FindClose(dirp->search_handle);
        dirp->search_handle = INVALID_HANDLE_VALUE;
    }

    // release directory handle
    free(dirp);
    return 0;
}

/*****************************************************************************
 * Resets the position of the directory stream to which dirp refers to the
 * beginning of the directory. It also causes the directory stream to refer
 * to the current state of the corresponding directory, as a call to opendir()
 * would have done. If dirp does not refer to a directory stream, the effect
 * is undefined.
 */
void
rewinddir(DIR *dirp) {
    if(dirp == 0x0) {
        return;
    }

    // release search handle
    if(dirp->search_handle != INVALID_HANDLE_VALUE) {
        FindClose(dirp->search_handle);
        dirp->search_handle = INVALID_HANDLE_VALUE;
    }

    // open new search handle and retrieve first file
    dirp->search_handle = FindFirstFileA(dirp->patt, &dirp->current.data);
    if(dirp->search_handle == INVALID_HANDLE_VALUE) {
        // invalid search pattern?
        free(dirp);
        return;
    }

    // there is an un-processed directory entry in memory now
    dirp->cached = 1;
}

#endif