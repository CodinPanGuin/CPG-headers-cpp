#pragma once
/**
 * @file CPG-dsys.h
 * @brief Cross-platform utilities for working with directories.
 */
#include <stdbool.h>

/**
 * @brief Creates a directory at the specified path.
 * @code
 * if (CPG_dsys_mdir("folder"))
 *     printf("Directory created.\n");
 * else
 *     printf("Failed to create directory.\n");
 * @endcode
 * @param path The path where the directory should be created.
 * @return True if the directory was successfully created; otherwise, false.
 */
bool CPG_dsys_mdir(char path[]);

/**
 * @brief Checks whether a file or directory exists at the given path.
 * @code
 * if (CPG_dsys_exist("some_folder"))
 *     printf("Exists!\n");
 * else
 *     printf("Does not exist.\n");
 * @endcode
 * @param path The path to check.
 * @return True if the file or directory exists; otherwise, false.
 */
bool CPG_dsys_exist(char path[]);

/**
 * @brief Deletes the file at the specified path.
 * @code
 * if (CPG_dsys_rfile("file.txt"))
 *     printf("File deleted.\n");
 * else
 *     printf("Failed to delete file.\n");
 * @endcode
 * @param path The path of the file to delete.
 * @return True if the file was successfully deleted; otherwise, false.
 */
bool CPG_dsys_rfile(char path[]);

/**
 * @brief Deletes the directory at the specified path and all its contents.
 * @code
 * if (CPG_dsys_rdir("path"))
 *     printf("Directory deleted.\n");
 * else
 *     printf("Failed to delete directory.\n");
 * @endcode
 * @param path The path of the directory to delete.
 * @return True if the directory was successfully deleted; otherwise, false.
 */
bool CPG_dsys_rdir(char path[]);
