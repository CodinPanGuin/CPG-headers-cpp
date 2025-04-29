#include "CPG-dsys.h"

#if defined(_WIN32)
    #include <windows.h>
    #include <direct.h>
    #include <io.h>
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <limits.h>
#endif

bool CPG_dsys_mdir(char path[]) {
    #if defined(_WIN32)
        return _mkdir(path) == 0;
    #else
        return mkdir(path, 0755) == 0;
    #endif
}

bool CPG_dsys_exist(char path[]) {
    #if defined(_WIN32)
        return _access(path, 0) == 0;
    #else
        return access(path, F_OK) == 0;
    #endif
}

bool CPG_dsys_rfile(char path[]) {
    #if defined(_WIN32)
        return DeleteFileA(path) != 0;
    #else
        return unlink(path) == 0;
    #endif
}

bool CPG_dsys_rdir(char path[]) {
    #if defined(_WIN32)
        WIN32_FIND_DATAA find_data;
        char search_path[MAX_PATH];
        int i = 0;

        while (path[i] != '\0' && i < MAX_PATH - 2) {
            search_path[i] = path[i];
            i++;
        }
        if (i < MAX_PATH - 2) {
            search_path[i++] = '\\';
            search_path[i++] = '*';
        }
        search_path[i] = '\0';

        HANDLE hFind = FindFirstFileA(search_path, &find_data);
        if (hFind == INVALID_HANDLE_VALUE) return false;

        do {
            if (find_data.cFileName[0] == '.' && 
                (find_data.cFileName[1] == '\0' || 
                (find_data.cFileName[1] == '.' && find_data.cFileName[2] == '\0'))) {
                continue;
            }

            char full_path[MAX_PATH];
            int j = 0, k = 0;
            i = 0;
            while (path[j] != '\0' && i < MAX_PATH - 1) full_path[i++] = path[j++];
            if (i > 0 && full_path[i-1] != '\\' && full_path[i-1] != '/') full_path[i++] = '\\';
            while (find_data.cFileName[k] != '\0' && i < MAX_PATH - 1) full_path[i++] = find_data.cFileName[k++];
            full_path[i] = '\0';

            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (!CPG_dsys_rdir(full_path)) {
                    FindClose(hFind);
                    return false;
                }
            } else {
                if (!DeleteFileA(full_path)) {
                    FindClose(hFind);
                    return false;
                }
            }
        } while (FindNextFileA(hFind, &find_data));

        FindClose(hFind);
        return RemoveDirectoryA(path) != 0;
    #else
        DIR *dir = opendir(path);
        if (!dir) return false;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] == '.' && 
               (entry->d_name[1] == '\0' || 
               (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
                continue;
            }

            char full_path[PATH_MAX];
            int j = 0, k = 0;
            int i = 0;
            while (path[j] != '\0' && i < PATH_MAX - 1) full_path[i++] = path[j++];
            if (i > 0 && full_path[i-1] != '/') full_path[i++] = '/';
            while (entry->d_name[k] != '\0' && i < PATH_MAX - 1) full_path[i++] = entry->d_name[k++];
            full_path[i] = '\0';

            struct stat st;
            if (stat(full_path, &st) == -1) {
                closedir(dir);
                return false;
            }

            if (S_ISDIR(st.st_mode)) {
                if (!CPG_dsys_rdir(full_path)) {
                    closedir(dir);
                    return false;
                }
            } else {
                if (unlink(full_path) != 0) {
                    closedir(dir);
                    return false;
                }
            }
        }

        closedir(dir);
        return rmdir(path) == 0;
    #endif
}
