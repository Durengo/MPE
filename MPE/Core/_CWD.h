#pragma once

#include "MPE/Core/_CORE.h"

/**
 * @file _CWD.h
 * @brief Set the current working directory to the executable path.
 * @details This file is used to set the current working directory to the
 * executable path.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

/**
 * @def SET_EXECUTABLE_PATH_AS_CWD()
 * @brief Set the current working directory to the executable path.
 * @details This macro is used to set the current working directory to the
 * executable path.
 * @date 2024-05-05
 * @note This macro is only available on Windows and UNIX systems.
 */

// TODO: Add support for MacOS
#ifdef MPE_PLATFORM_WINDOWS

#    include <Shlwapi.h>
#    include <windows.h>
#    include <string>
#    pragma comment(lib, "Shlwapi.lib")

#    define SET_EXECUTABLE_PATH_AS_CWD()                              \
        {                                                             \
            char path[MAX_PATH];                                      \
            if (GetModuleFileNameA(NULL, path, MAX_PATH))             \
            {                                                         \
                PathRemoveFileSpecA(path);                            \
                SetCurrentDirectoryA(path);                           \
                MPE_CORE_WARN("Working directory set to: {0}", path); \
            }                                                         \
            else                                                      \
            {                                                         \
                MPE_CORE_ERROR("Cannot set the working directory");   \
            }                                                         \
        }

#elif MPE_PLATFORM_LINUX

#    include <libgen.h>
#    include <limits.h>
#    include <unistd.h>
#    include <string>

#    define SET_EXECUTABLE_PATH_AS_CWD()                                  \
        {                                                                 \
            char path[PATH_MAX];                                          \
            ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);   \
            if (count != -1)                                              \
            {                                                             \
                path[count] = '\0';                                       \
                dirname(path);                                            \
                if (chdir(path) == 0)                                     \
                {                                                         \
                    MPE_CORE_WARN("Working directory set to: {0}", path); \
                }                                                         \
                else                                                      \
                {                                                         \
                    MPE_CORE_ERROR("Cannot set the working directory");   \
                }                                                         \
            }                                                             \
            else                                                          \
            {                                                             \
                MPE_CORE_ERROR("Failed to retrieve executable path");     \
            }                                                             \
        }

#elif MPE_PLATFORM_OSX

#    include <libgen.h>
#    include <libproc.h>
#    include <limits.h>
#    include <unistd.h>
#    include <string>

#    define SET_EXECUTABLE_PATH_AS_CWD()                                                            \
        {                                                                                           \
            char path[PROC_PIDPATHINFO_MAXSIZE];                                                    \
            if (proc_pidpath(getpid(), path, sizeof(path)) > 0)                                     \
            {                                                                                       \
                char *dir_path = dirname(path);                                                     \
                if (chdir(dir_path) == 0)                                                           \
                {                                                                                   \
                    MPE_CORE_WARN("Working directory set to: {0}", dir_path);                       \
                }                                                                                   \
                else                                                                                \
                {                                                                                   \
                    MPE_CORE_ERROR("Cannot set the working directory. Error: {}", strerror(errno)); \
                }                                                                                   \
            }                                                                                       \
            else                                                                                    \
            {                                                                                       \
                MPE_CORE_ERROR("Failed to retrieve executable path. Error: {}", strerror(errno));   \
            }                                                                                       \
        }

#else
#    error CWD does not support this system.
#endif
