#pragma once
/**
 * @file CPG-dsys.h
 * @brief Cross-platform file and directory system utilities.
 *
 * Provides a set of inline utility functions for performing
 * basic file and directory operations such as creation, deletion, existence 
 * checking, and copying. It supports both Windows and POSIX-compliant systems.
 *
 * Namespace: CPG_dsys
 *
 * Provided functions:
 * - m_dir     : Create a directory
 * - r_dir     : Recursively delete a directory and its contents
 * - e_dir     : Check if a file or directory exists
 * - r_file    : Delete a file
 *
 * Includes:
 * <string>
 * #Windows: <windows.h>, <direct.h>, <io.h>
 * #POSIX: <sys/stat.h>, <unistd.h>, <dirent.h>
 *
 * @author CodinPanGuin
 * @date 2025-04-21
 * @version 1.0
 * @note License: MIT
 */

#include <string>

#if defined(_WIN32)
  #include <windows.h>
  #include <direct.h>
  #include <io.h>
#else
  #include <sys/stat.h>
  #include <unistd.h>
  #include <dirent.h> 
#endif

namespace CPG_dsys {
  /**
  * @brief Creates a directory at the specified path.
  * @code
  * if (CPG_dsys::m_dir("folder"))
  *     printf("Directory created.\n");
  * else
  *     printf("Failed to create directory.\n");
  * @endcode
  * @param path The path where the directory should be created.
  * @return True if the directory was successfully created; otherwise, false.
  */
  inline bool m_dir(const std::string& path) {
    #if defined(_WIN32)
        return _mkdir(path.c_str()) == 0;
    #else
        return mkdir(path.c_str(), 0755) == 0;
    #endif
  }
  /**
  * @brief Recursively deletes a directory and its contents.
  * @code
  * if (CPG_dsys::r_dir("folder"))
  *     printf("Directory deleted.\n");
  * else
  *     printf("Failed to delete directory.\n");
  * @endcode
  * @param path The path of the directory to delete.
  * @return True if the directory and its contents were successfully deleted; otherwise, false.
  */
  inline bool r_dir(const std::string& path) {
    #if defined(_WIN32)
        std::string search_path = path + "\\*";
        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(search_path.c_str(), &fd);
        if (hFind == INVALID_HANDLE_VALUE) return false;

        do {
          std::string name = fd.cFileName;
          if (name == "." || name == "..") continue;

          std::string full_path = path + "\\" + name;
          if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!r_dir(full_path)) {
              FindClose(hFind);
              return false;
            }
          }
          else {
            if (!DeleteFileA(full_path.c_str())) {
              FindClose(hFind);
              return false;
            }
          }
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
        return RemoveDirectoryA(path.c_str()) != 0;
    #else
        DIR* dir = opendir(path.c_str());
        if (!dir) return false;

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
          std::string name = entry->d_name;
          if (name == "." || name == "..") continue;

          std::string full_path = path + "/" + name;
          if (entry->d_type == DT_DIR) {
            if (!r_dir(full_path)) {
              closedir(dir);
              return false;
            }
          }
          else {
            if (unlink(full_path.c_str()) != 0) {
              closedir(dir);
              return false;
            }
          }
        }
        closedir(dir);
        return rmdir(path.c_str()) == 0;
    #endif
  }
  /**
  * @brief Checks whether a file or directory exists at the given path.
  * @code
  * if (CPG_dsys::e_dir("some_folder"))
  *     printf("Exists!\n");
  * else
  *     printf("Does not exist.\n");
  * @endcode
  * @param path The path to check.
  * @return True if the file or directory exists; otherwise, false.
  */
  inline bool e_dir(const std::string& path) {
    #if defined(_WIN32)
        return _access(path.c_str(), 0) == 0;
    #else
        return access(path.c_str(), F_OK) == 0;
    #endif
  }
  /**
  * @brief Deletes the file at the specified path.
  * @code
  * if (CPG_dsys::r_file("file.txt"))
  *     printf("File deleted.\n");
  * else
  *     printf("Failed to delete file.\n");
  * @endcode
  * @param path The path of the file to delete.
  * @return True if the file was successfully deleted; otherwise, false.
  */
  inline bool r_file(const std::string& path) {
    #if defined(_WIN32)
        return DeleteFileA(path.c_str()) != 0;
    #else
        return unlink(path.c_str()) == 0;
    #endif
  }
}