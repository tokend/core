/*
 _____ _____ _____ _ _ _
|     | __  |     | | | |  Crow - a Sentry client for C++
|   --|    -|  |  | | | |  version 0.0.6
|_____|__|__|_____|_____|  https://github.com/nlohmann/crow

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2018 Niels Lohmann <http://nlohmann.me>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef NLOHMANN_CROW_CONFIG_HPP
#define NLOHMANN_CROW_CONFIG_HPP

/*!
 * @file crow_config.hpp
 * @brief constants written by CMake
 */

#ifndef CMAKE_SIZEOF_VOID_P
#define NLOHMANN_CROW_CMAKE_BUILD_TYPE "win_build"
#define NLOHMANN_CROW_BITS (0)
// context: device
#define NLOHMANN_CROW_CMAKE_SYSTEM_PROCESSOR "unknown"
#define NLOHMANN_CROW_HOSTNAME "unknown"
#define NLOHMANN_CROW_SYSCTL_HW_MODEL "unknown"
#define NLOHMANN_CROW_TOTAL_PHYSICAL_MEMORY "unknown"

// context: os
#define NLOHMANN_CROW_CMAKE_SYSTEM_NAME "unknown"
#define NLOHMANN_CROW_OS_RELEASE "unknown"
#define NLOHMANN_CROW_OS_VERSION "unknown"
#define NLOHMANN_CROW_CMAKE_SYSTEM_VERSION "unknown"
#define NLOHMANN_CROW_UNAME "unknown"
#define NLOHMANN_CROW_SYSTEMINFO "unknown"

// context: runtime
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_ID "unknown"
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_VERSION "unknown"
#define NLOHMANN_CROW_CXX "unknown"

// crow version
#define NLOHMANN_CROW_VERSION_MAJOR "unknown"
#define NLOHMANN_CROW_VERSION_MINOR "unknown"
#define NLOHMANN_CROW_VERSION_PATCH "unknown"
#define NLOHMANN_CROW_VERSION "unknown"

// context: device
#define NLOHMANN_CROW_CMAKE_SYSTEM_PROCESSOR "unknown"
#define NLOHMANN_CROW_HOSTNAME "unknown"
#define NLOHMANN_CROW_SYSCTL_HW_MODEL "unknown"
#define NLOHMANN_CROW_TOTAL_PHYSICAL_MEMORY "unknown"

// context: os
#define NLOHMANN_CROW_CMAKE_SYSTEM_NAME "unknown"
#define NLOHMANN_CROW_OS_RELEASE "unknown"
#define NLOHMANN_CROW_OS_VERSION "unknown"
#define NLOHMANN_CROW_CMAKE_SYSTEM_VERSION "unknown"
#define NLOHMANN_CROW_UNAME "unknown"
#define NLOHMANN_CROW_SYSTEMINFO "unknown"

// context: runtime
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_ID "unknown"
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_VERSION "unknown"
#define NLOHMANN_CROW_CXX "unknown"

// crow version
#define NLOHMANN_CROW_VERSION_MAJOR "unknown"
#define NLOHMANN_CROW_VERSION_MINOR "unknown"
#define NLOHMANN_CROW_VERSION_PATCH "unknown"
#define NLOHMANN_CROW_VERSION "unknown"

#else

// macros do decide which headers are present
#cmakedefine NLOHMANN_CROW_HAVE_CXXABI_H
#cmakedefine NLOHMANN_CROW_HAVE_EXECINFO_H
#cmakedefine NLOHMANN_CROW_HAVE_DLFCN_H

// macros to choose certain functions
#cmakedefine NLOHMANN_CROW_MINGW

// context: app
#define NLOHMANN_CROW_CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}"
#define NLOHMANN_CROW_BITS (${CMAKE_SIZEOF_VOID_P} * 8)

// context: device
#define NLOHMANN_CROW_CMAKE_SYSTEM_PROCESSOR "${CMAKE_SYSTEM_PROCESSOR}"
#define NLOHMANN_CROW_HOSTNAME "${NLOHMANN_CROW_HOSTNAME}"
#define NLOHMANN_CROW_SYSCTL_HW_MODEL "${NLOHMANN_CROW_SYSCTL_HW_MODEL}"
#define NLOHMANN_CROW_TOTAL_PHYSICAL_MEMORY (${NLOHMANN_CROW_TOTAL_PHYSICAL_MEMORY} * 1048576ul)

// context: os
#define NLOHMANN_CROW_CMAKE_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}"
#define NLOHMANN_CROW_OS_RELEASE "${NLOHMANN_CROW_OS_RELEASE}"
#define NLOHMANN_CROW_OS_VERSION "${NLOHMANN_CROW_OS_VERSION}"
#define NLOHMANN_CROW_CMAKE_SYSTEM_VERSION "${CMAKE_SYSTEM_VERSION}"
#define NLOHMANN_CROW_UNAME "${NLOHMANN_CROW_UNAME}"
#define NLOHMANN_CROW_SYSTEMINFO "${NLOHMANN_CROW_SYSTEMINFO}"

// context: runtime
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_ID "${CMAKE_CXX_COMPILER_ID}"
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}"
#define NLOHMANN_CROW_CXX "${NLOHMANN_CROW_CXX}"

// crow version
#define NLOHMANN_CROW_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
#define NLOHMANN_CROW_VERSION_MINOR ${PROJECT_VERSION_MINOR}
#define NLOHMANN_CROW_VERSION_PATCH ${PROJECT_VERSION_PATCH}
#define NLOHMANN_CROW_VERSION "${PROJECT_VERSION}"

// context: device
#define NLOHMANN_CROW_CMAKE_SYSTEM_PROCESSOR "${CMAKE_SYSTEM_PROCESSOR}"
#define NLOHMANN_CROW_HOSTNAME "${NLOHMANN_CROW_HOSTNAME}"
#define NLOHMANN_CROW_SYSCTL_HW_MODEL "${NLOHMANN_CROW_SYSCTL_HW_MODEL}"
#define NLOHMANN_CROW_TOTAL_PHYSICAL_MEMORY (${NLOHMANN_CROW_TOTAL_PHYSICAL_MEMORY} * 1048576ul)

// context: os
#define NLOHMANN_CROW_CMAKE_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}"
#define NLOHMANN_CROW_OS_RELEASE "${NLOHMANN_CROW_OS_RELEASE}"
#define NLOHMANN_CROW_OS_VERSION "${NLOHMANN_CROW_OS_VERSION}"
#define NLOHMANN_CROW_CMAKE_SYSTEM_VERSION "${CMAKE_SYSTEM_VERSION}"
#define NLOHMANN_CROW_UNAME "${NLOHMANN_CROW_UNAME}"
#define NLOHMANN_CROW_SYSTEMINFO "${NLOHMANN_CROW_SYSTEMINFO}"

// context: runtime
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_ID "${CMAKE_CXX_COMPILER_ID}"
#define NLOHMANN_CROW_CMAKE_CXX_COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}"
#define NLOHMANN_CROW_CXX "${NLOHMANN_CROW_CXX}"

// crow version
#define NLOHMANN_CROW_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
#define NLOHMANN_CROW_VERSION_MINOR ${PROJECT_VERSION_MINOR}
#define NLOHMANN_CROW_VERSION_PATCH ${PROJECT_VERSION_PATCH}
#define NLOHMANN_CROW_VERSION "${PROJECT_VERSION}"

#endif
#endif
