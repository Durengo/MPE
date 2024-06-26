cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CXX_VERSION_NAME "cxx_std_${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TOGGLE TESTING
set(MAIN_TEST OFF)

# TOGGLE EXAMPLES
set(EXAMPLES OFF)

# TOGGLE .DLL IN INSTALLS
set(INSTALL_DLLS OFF)

# SWITCHES FOR PROJECTS
set(MPE_PROJECTS OFF)

# TEMPORARY
# DUMMY EXECUTABLE
set(DUMMY_EXECUTABLE ON)

# SHARED OR STATIC LIBRARY
# ONLY 'STATIC' OR 'SHARED'
set(MPE_LIBRARY_TYPE SHARED)

# SETTING PROJECT VERSION
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 1)
set(PROJECT_VERSION_SUFFIX "a")
set(PROJECT_VERSION
  ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}
)
set(PROJECT_FULL_VERSION
  ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}.${PROJECT_VERSION_SUFFIX}
)

# CREATING PROJECT
if(WIN32)
  project(MERELY_PRIMITIVE_ENGINE VERSION ${PROJECT_VERSION} LANGUAGES C CXX)
elseif(APPLE)
  project(MERELY_PRIMITIVE_ENGINE VERSION ${PROJECT_VERSION} LANGUAGES C CXX OBJC OBJCXX)
else()
  project(MERELY_PRIMITIVE_ENGINE VERSION ${PROJECT_VERSION} LANGUAGES C CXX)
endif()

# RUN CMP TO ASSIGN BUILD TYPE
if(WIN32)
  execute_process(
    COMMAND cmd /c "${PROJECT_SOURCE_DIR}\\cpm.bat" "cache" "-r" "-p"
    "cmake_build_type"
    OUTPUT_VARIABLE BUILD_TYPE_SETUP_OUTPUT
    RESULT_VARIABLE BUILD_TYPE_SETUP_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_BUILD_TYPE ${BUILD_TYPE_SETUP_OUTPUT})
elseif(UNIX)
  execute_process(
    COMMAND bash "${PROJECT_SOURCE_DIR}/cpm.sh" "cache" "-r" "-p"
    "cmake_build_type"
    OUTPUT_VARIABLE BUILD_TYPE_SETUP_OUTPUT
    RESULT_VARIABLE BUILD_TYPE_SETUP_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_BUILD_TYPE ${BUILD_TYPE_SETUP_OUTPUT})
endif()

# SET INSTALLATION PATH CoreD ON BUILD TYPE SETTING BUILD TYPE TOGGLING CUSTOM
# VERBOSITY
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(INSTALL_PATH_SUFFIX "Debug")
  set(CMAKE_BUILD_TYPE Debug)
  set(VERBOSE
    ON
    CACHE INTERNAL "Verbosity on")
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(INSTALL_PATH_SUFFIX "Release")
  set(CMAKE_BUILD_TYPE Release)
  set(VERBOSE
    OFF
    CACHE INTERNAL "Verbosity off")
  set(CMAKE_EXPORT_COMPILE_COMMANDS FALSE)
else()
  set(INSTALL_PATH_SUFFIX "Unknown")
  set(VERBOSE
    ON
    CACHE INTERNAL "Verbosity on")
  message(FATAL_ERROR "UNKNOWN BUILD TYPE: \"${CMAKE_BUILD_TYPE}\".")
endif()

# PATH TO INSTALLATION DIRECTORY
set(CMAKE_INSTALL_PREFIX
  "${CMAKE_CURRENT_SOURCE_DIR}/Install/${CMAKE_BUILD_TYPE}"
  CACHE PATH "Installation Directory" FORCE)

if(${VERBOSE})
  message(STATUS "INSTALLATION SETUP PROCESS STARTING...")
  message(STATUS "DEFAULT INSTALLATION DIRECTORY: \"${CMAKE_INSTALL_PREFIX}\".")
endif()

# CHECKING PLATFORM
set(CURRENT_PLATFORM "${CMAKE_SYSTEM_NAME}")

if(${VERBOSE})
  message(STATUS "CURRENT PLATFORM: ${CMAKE_SYSTEM_NAME}")
endif()

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON X64 SYSTEM THIS ALSO FAILS IF THE
# COMPILER IS NOT 64-BIT COMPATIBLE
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "OMNI-GRID-FRAMEWORK SUPPORTS X64 SYSTEMS ONLY.")
  return()
endif()

# SETTING UP COMPILER
if(${VERBOSE})
  message(STATUS "SETTING UP COMPILER...")
endif()

string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" LOWER_COMPILER_ID)

if(LOWER_COMPILER_ID STREQUAL "msvc")
  set(CURRENT_COMPILER "MSVC")
  set(COMPILATION_PLATFORM "WIN32")
elseif(LOWER_COMPILER_ID STREQUAL "gnu")
  set(CURRENT_COMPILER "GNU")
  set(COMPILATION_PLATFORM "UNIX")
elseif(LOWER_COMPILER_ID STREQUAL "clang")
  set(CURRENT_COMPILER "CLANG")
  set(COMPILATION_PLATFORM "UNIX")
elseif(LOWER_COMPILER_ID STREQUAL "appleclang")
  set(CURRENT_COMPILER "APPLECLANG")
  set(COMPILATION_PLATFORM "OSX")
else()
  message(FATAL_ERROR "COMPILER: {${CMAKE_CXX_COMPILER_ID}} NOT SUPPORTED.")
endif()

if(${VERBOSE})
  message(STATUS "CURRENT COMPILER PATH: ${CMAKE_CXX_COMPILER}")
  message(STATUS "CURRENT COMPILER: ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "CURRENT COMPILER VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
  message(STATUS "CURRENT COMPILER: ${CURRENT_COMPILER}")
  message(STATUS "CURRENT PLATFORM: ${COMPILATION_PLATFORM}")
  message(STATUS "COMPILER SETUP COMPLETE.")
endif()

# DEPENDENCY MANAGEMENT
if(WIN32)
  set(USE_VCPKG ON)

  if(${VERBOSE})
    message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
  endif()

  # RUN CPM TO GET VCPKG PATH
  execute_process(
    COMMAND cmd /c "${PROJECT_SOURCE_DIR}\\cpm.bat" "cache" "-r" "-p"
    "vcpkg_path"
    OUTPUT_VARIABLE VCPKG_SETUP_OUTPUT
    RESULT_VARIABLE VCPKG_SETUP_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  set(VCPKG_FILEPATH "${VCPKG_SETUP_OUTPUT}")
  file(TO_CMAKE_PATH "${VCPKG_FILEPATH}/installed/x64-windows" VCPKG_CORE)

  if(NOT EXISTS "${VCPKG_FILEPATH}")
    message(
      FATAL_ERROR
      "VCPKG NOT FOUND - MAKE SURE \"${VCPKG_FILEPATH}\" IS SET CORRECTLY.\nCURRENT PATH IS SET TO: \"${VCPKG_FILEPATH}\"."
    )
  endif()

  # RUN CPM TO GET VCPKG ROOT PATH
  execute_process(
    COMMAND cmd /c "${PROJECT_SOURCE_DIR}\\cpm.bat" "cache" "-r" "-p"
    "toolchain_path"
    OUTPUT_VARIABLE VCPKG_ROOT_PATH_SETUP_OUTPUT
    RESULT_VARIABLE VCPKG_ROOT_PATH_SETUP_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  set(VCPKG_ROOT_PATH "${VCPKG_ROOT_PATH_SETUP_OUTPUT}")

  if(USE_VCPKG)
    if(${VERBOSE})
      message(
        STATUS
        "LOOKING FOR VCPKG IN \"${VCPKG_FILEPATH}\" TO MANAGE DEPENDENCIES.")
    endif()

    # set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
    set(CMAKE_TOOLCHAIN_FILE
      "${VCPKG_FILEPATH}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "Vcpkg toolchain file")
    set(CMAKE_PREFIX_PATH "${VCPKG_FILEPATH}/installed/x64-windows")

    if(${VERBOSE})
      message(STATUS "VCPKG FOUND IN \"${VCPKG_FILEPATH}\".")
    endif()
  endif()

  # USE SPECIFIC PATHS FOR VCPKG LIBRARIES
  set(VCPKG_CUSTOM_PATHS ON)

  if(${VERBOSE})
    message(STATUS "VCPKG CUSTOM PATHS STATUS: ${VCPKG_CUSTOM_PATHS}")
  endif()

  if(${VCPKG_CUSTOM_PATHS})
    if(${VERBOSE})
      message(STATUS "VCPKG SETTING CUSTOM PATHS...")
    endif()

    set(fmt_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\fmt")
    set(spdlog_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\spdlog")

    # GLAD
    set(glad_DIR "${PROJECT_SOURCE_DIR}/Vendor/Glad")

    file(GLOB_RECURSE GLAD_S
      "${glad_DIR}/src/glad.c")

    add_library(glad STATIC ${GLAD_S})
    target_include_directories(glad PUBLIC "${glad_DIR}/include")

    set(glfw3_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\glfw3")

    # IMGUI
    # set(imgui_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\imgui")
    set(imgui_DIR ${PROJECT_SOURCE_DIR}/Vendor/imgui)

    file(GLOB_RECURSE IMGUI_S
      "${imgui_DIR}/imgui.cpp"
      "${imgui_DIR}/imgui_draw.cpp"
      "${imgui_DIR}/imgui_tables.cpp"
      "${imgui_DIR}/imgui_widgets.cpp"
      "${imgui_DIR}/imgui_demo.cpp"
    )

    list(APPEND IMGUI_S
      "${imgui_DIR}/backends/imgui_impl_glfw.cpp"
      "${imgui_DIR}/backends/imgui_impl_opengl3.cpp"
    )

    add_library(imgui STATIC
      ${IMGUI_S}
    )
    target_include_directories(imgui PUBLIC
      "${imgui_DIR}"
      ${glfw3_INCLUDE_DIRS}
    )
    target_link_libraries(imgui PRIVATE glfw)

    set(glm_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\glm")
    set(GTest_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\gtest")

    # STB
    set(Stb_DIR ${PROJECT_SOURCE_DIR}/Vendor/stb)
    add_library(Stb INTERFACE
      "${Stb_DIR}"
    )
    target_include_directories(Stb INTERFACE
      "${Stb_DIR}"
    )

    if(${VERBOSE})
      message(STATUS "fmt_DIR: ${fmt_DIR}")
      message(STATUS "spdlog_DIR: ${spdlog_DIR}")

      message(STATUS "glad_DIR: ${glad_DIR}")
      message(STATUS "glad_DIR_S: ${GLAD_S}")

      message(STATUS "glfw3_DIR: ${glfw3_DIR}")

      message(STATUS "imgui_DIR: ${imgui_DIR}")
      message(STATUS "imgui_DIR_S: ${IMGUI_S}")

      message(STATUS "glm_DIR: ${glm_DIR}")
      message(STATUS "GTest_DIR: ${GTest_DIR}")
      message(STATUS "Stb_DIR: ${Stb_DIR}")

      message(STATUS "VCPKG CUSTOM PATHS SET.")
    endif()
  endif()

  if(${VERBOSE})
    message(STATUS "VCPKG SETUP COMPLETE.")
  endif()

elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
  set(USE_VCPKG OFF)

  if(${VERBOSE})
    message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
  endif()

  # message(STATUS "VCPKG NOT SUPPORTED ON UNIX SYSTEMS.")
  if(${VERBOSE})
    message(STATUS "ADDING CUSTOM PATHS FOR SPECIFIC LIBRARIES...")
  endif()

  # GLAD
  set(glad_DIR "${PROJECT_SOURCE_DIR}/Vendor/Glad")
  add_library(glad STATIC "${glad_DIR}/src/glad.c")
  target_include_directories(glad PUBLIC "${glad_DIR}/include")

  # Ensure that glad is compiled with -fPIC
  set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

  # IMGUI
  set(imgui_DIR ${PROJECT_SOURCE_DIR}/Vendor/imgui)

  file(GLOB_RECURSE IMGUI_S
    "${imgui_DIR}/imgui.cpp"
    "${imgui_DIR}/imgui_draw.cpp"
    "${imgui_DIR}/imgui_tables.cpp"
    "${imgui_DIR}/imgui_widgets.cpp"
    "${imgui_DIR}/imgui_demo.cpp"
  )

  list(APPEND IMGUI_S
    "${imgui_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_DIR}/backends/imgui_impl_opengl3.cpp"
  )

  add_library(imgui STATIC
    ${IMGUI_S}
  )
  target_include_directories(imgui PUBLIC
    "${imgui_DIR}"
    ${glfw3_INCLUDE_DIRS}
  )
  target_link_libraries(imgui PRIVATE glfw)

  # GTK#
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

  # STB
  set(Stb_DIR ${PROJECT_SOURCE_DIR}/Vendor/stb)
  add_library(Stb INTERFACE
    "${Stb_DIR}"
  )
  target_include_directories(Stb INTERFACE
    "${Stb_DIR}"
  )

  if(${VERBOSE})
    message(STATUS "glad_DIR: ${glad_DIR}")
    message(STATUS "imgui_DIR: ${imgui_DIR}")
    message(STATUS "GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")

    # message(STATUS "glfw3_DIR: ${glfw3_DIR}")
    # message(STATUS "glm_DIR: ${glm_DIR}")
    # message(STATUS "GTest_DIR: ${GTest_DIR}")
    message(STATUS "CUSTOM LIBRARY PATHS SET.")
  endif()

elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  set(USE_VCPKG OFF)

  if(${VERBOSE})
    message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
  endif()

  # message(STATUS "VCPKG NOT SUPPORTED ON UNIX SYSTEMS.")
  if(${VERBOSE})
    message(STATUS "ADDING CUSTOM PATHS FOR SPECIFIC LIBRARIES...")
  endif()

  # GLAD
  set(glad_DIR "${PROJECT_SOURCE_DIR}/Vendor/Glad")
  add_library(glad STATIC "${glad_DIR}/src/glad.c")
  target_include_directories(glad PUBLIC "${glad_DIR}/include")

  # IMGUI
  set(imgui_DIR ${PROJECT_SOURCE_DIR}/Vendor/imgui)

  file(GLOB_RECURSE IMGUI_S
    "${imgui_DIR}/imgui.cpp"
    "${imgui_DIR}/imgui_draw.cpp"
    "${imgui_DIR}/imgui_tables.cpp"
    "${imgui_DIR}/imgui_widgets.cpp"
    "${imgui_DIR}/imgui_demo.cpp"
  )

  list(APPEND IMGUI_S
    "${imgui_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_DIR}/backends/imgui_impl_opengl3.cpp"
  )

  add_library(imgui STATIC
    ${IMGUI_S}
  )
  target_include_directories(imgui PUBLIC
    "${imgui_DIR}"
    ${glfw3_INCLUDE_DIRS}
  )
  target_link_libraries(imgui PRIVATE glfw)

  # STB
  set(Stb_DIR ${PROJECT_SOURCE_DIR}/Vendor/stb)
  add_library(Stb INTERFACE
    "${Stb_DIR}"
  )
  target_include_directories(Stb INTERFACE
    "${Stb_DIR}"
  )

  if(${VERBOSE})
    message(STATUS "glad_DIR: ${glad_DIR}")
    message(STATUS "imgui_DIR: ${imgui_DIR}")
    message(STATUS "Stb_DIR: ${Stb_DIR}")

    # message(STATUS "glfw3_DIR: ${glfw3_DIR}")
    # message(STATUS "glm_DIR: ${glm_DIR}")
    # message(STATUS "GTest_DIR: ${GTest_DIR}")
    message(STATUS "CUSTOM LIBRARY PATHS SET.")
  endif()

else()
  message(FATAL_ERROR "PLATFORM NOT SUPPORTED.")
endif()

# ADDING DEPENDENCIES
if(${VERBOSE})
  message(STATUS "LOOKING FOR DEPENDENCIES...")
endif()

# FIND DEPENDCIES PROVIDED BY DEPENDENCY MANAGER
# EXPLICITLY SET PACKAGE_DIR
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

if(COMPILATION_PLATFORM STREQUAL "OSX")
  find_library(COCOA_LIBRARY Cocoa)
endif()

# find_package(imguizmo CONFIG REQUIRED) find_package(yaml-cpp CONFIG REQUIRED)
# find_package(Stb REQUIRED)
if(${VERBOSE})
  message(STATUS "ALL DEPENDENCIES FOUND.")
endif()

# ADDING TESTING ENVIRONMENT
if(${VERBOSE})
  message(STATUS "ADDING TESTING ENVIRONMENT...")
endif()

include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_FULL_VERSION})
include(CPack)

if(${VERBOSE})
  message(STATUS "TESTING ENVIRONMENT ADDED.")
endif()

# ADDITIONAL INFORMATION
if(${VERBOSE})
  message(STATUS "CURRENT BUILD TYPE: ${CMAKE_BUILD_TYPE}")
  message(STATUS "PROJECT VERSION: \"${PROJECT_FULL_VERSION}\".")
  message(STATUS "TOOLCHAIN STATUS: \"${CMAKE_TOOLCHAIN_FILE}\".")
  message(
    STATUS "CMAKE INCLUDE CURRENT DIRECTORY: \"${CMAKE_INCLUDE_CURRENT_DIR}\".")
  message(
    STATUS
    "CTEST STATUS: \"${CPACK_PROJECT_NAME}\" VERSION \"${CPACK_PROJECT_VERSION}\"."
  )
endif()

# ADD SOURCE FILES MPE LIBRARY .CPP FILES
file(
  GLOB_RECURSE
  MPE_CPP

  # TEST
  "${PROJECT_SOURCE_DIR}/MPE/Test/*.cpp"

  # /Core
  # "${PROJECT_SOURCE_DIR}/MPE/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Core/*.cpp"

  # /Log
  "${PROJECT_SOURCE_DIR}/MPE/Log/*.cpp"

  # /Errors
  "${PROJECT_SOURCE_DIR}/MPE/Errors/*.cpp"

  # /App
  "${PROJECT_SOURCE_DIR}/MPE/App/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/App/Layers/*.cpp"

  # /Profiling
  "${PROJECT_SOURCE_DIR}/MPE/Profiling/*.cpp"

  # /Physics
  "${PROJECT_SOURCE_DIR}/MPE/Time/*.cpp"

  # /Input
  "${PROJECT_SOURCE_DIR}/MPE/Input/*.cpp"

  # /Events
  "${PROJECT_SOURCE_DIR}/MPE/Events/*.cpp"

  # /OpenGL
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/*.cpp"

  # /Renderer
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/*.cpp"

  # /Platform/OpenGL
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Shaders/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/*.cpp"

  # /Vendor
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/ImGui/*.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB/*.cpp"
)

# PRINT MPE SOURCE FILES
if(${VERBOSE})
  message(STATUS "MPE SOURCE:\n{${MPE_CPP}}")
endif()

# MPE LIBRARY .H FILES
file(
  GLOB_RECURSE
  MPE_H

  # TEST
  "${PROJECT_SOURCE_DIR}/MPE/Test/*.h"

  # /Core
  "${PROJECT_SOURCE_DIR}/MPE/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Core/*.h"

  # /Log
  "${PROJECT_SOURCE_DIR}/MPE/Log/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Log/CustomSinks/*.h"

  # /Errors
  "${PROJECT_SOURCE_DIR}/MPE/Errors/*.h"

  # /App
  "${PROJECT_SOURCE_DIR}/MPE/App/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/App/Layers/*.h"

  # /Profiling
  "${PROJECT_SOURCE_DIR}/MPE/Profiling/*.h"

  # /Physics
  "${PROJECT_SOURCE_DIR}/MPE/Time/*.h"

  # /Input
  "${PROJECT_SOURCE_DIR}/MPE/Input/*.h"

  # /Events
  "${PROJECT_SOURCE_DIR}/MPE/Events/*.h"

  # /OpenGL
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/*.h"

  # /Renderer
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/*.h"

  # /Platform/OpenGL
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Shaders/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/*.h"

  # /Vendor
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/ImGui/*.h"
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB/*.h"
)

# PRINT MPE SOURCE FILES
if(${VERBOSE})
  message(STATUS "MPE HEADERS:\n{${MPE_H}}")
endif()

# ADD PLATFORM BASED MPE SOURCE FILES
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  file(
    GLOB_RECURSE
    MPE_WIN32_CPP

    # /Platform/Windows/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/App/*.cpp"

    # /Platform/Windows/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Errors/*.cpp"

    # /Platform/Windows/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Input/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_WIN32_H

    # /Platform/Windows/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/App/*.h"

    # /Platform/Windows/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Input/*.h"
  )

  # ADD MPE WIN32 SOURCE FILES
  list(APPEND MPE_CPP ${MPE_WIN32_CPP})

  list(APPEND MPE_H ${MPE_WIN32_H})

  # PRINT MPE WIN32 SOURCE FILES
  if(${VERBOSE})
    message(STATUS "MPE WIN32 SOURCE:\n{${MPE_WIN32_CPP}}")
    message(STATUS "MPE WIN32 HEADERS:\n{${MPE_WIN32_H}}")
  endif()
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
  file(
    GLOB_RECURSE
    MPE_Linux_CPP

    # /Platform/Linux/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/App/*.cpp"

    # /Platform/Linux/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Errors/*.cpp"

    # /Platform/Linux/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Input/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_Linux_H

    # /Platform/Linux/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/App/*.h"

    # /Platform/Linux/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Input/*.h"
  )

  # ADD MPE Linux SOURCE FILES
  list(APPEND MPE_CPP ${MPE_Linux_CPP})

  list(APPEND MPE_H ${MPE_Linux_H})

  # PRINT MPE Linux SOURCE FILES
  if(${VERBOSE})
    message(STATUS "MPE Linux SOURCE:\n{${MPE_Linux_CPP}}")
    message(STATUS "MPE Linux HEADERS:\n{${MPE_Linux_H}}")
  endif()
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  file(
    GLOB_RECURSE
    MPE_macOS_CPP

    # /Platform/macOS/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/App/*.cpp"

    # /Platform/macOS/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Errors/*.mm"

    # /Platform/macOS/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Input/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_macOS_H

    # /Platform/macOS/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/App/*.h"

    # /Platform/macOS/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Input/*.h"
  )

  # ADD MPE macOS SOURCE FILES
  list(APPEND MPE_CPP ${MPE_macOS_CPP})

  list(APPEND MPE_H ${MPE_macOS_H})

  # set_source_files_properties(${MPE_OSX_CPP} PROPERTIES COMPILE_FLAGS "-include MPE/MPEPCH.h")

  # PRINT MPE macOS SOURCE FILES
  if(${VERBOSE})
    message(STATUS "MPE macOS SOURCE:\n{${MPE_macOS_CPP}}")
    message(STATUS "MPE macOS HEADERS:\n{${MPE_macOS_H}}")
  endif()
endif()

if(${VERBOSE})
  message(STATUS "MPE SOURCE FILES ADDED.")
endif()

# BUILD MPE LIBRARY BASED ON SET LIBRARY TYPE
if(${MPE_LIBRARY_TYPE} STREQUAL STATIC)
  # MAKE MPE LIBRARY STATIC - DYNAMIC LIBRARY COULD BE SUPPORTED
  if(COMPILATION_PLATFORM STREQUAL "WIN32")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_WIN32_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_Linux_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_OSX_CPP}
    )
  endif()

  target_compile_definitions(MPE PRIVATE MPE_STATIC_LIBRARY)
elseif(${MPE_LIBRARY_TYPE} STREQUAL SHARED)
  # DOUBLE CHECKS IF BUILDSYSTEM IS USING ONLY STATIC LIBRARY. DYNAMIC LIBRARIES
  # ARE POSSIBLE TO BE USED, BUT IS NOT INTENDED WITH THIS PROJECT AT THE MOMENT.
  # DYNAMIC LIBRARIES ARE STILL IMPLEMENTED AS AN EXAMPLE AND CAN STILL BE USED IF THE
  # USERS DEEM THAT IT IS NEEDED. REMOVE #ERROR PREPROCESSOR DECLARATION ON LINE
  # 17 IN CORE.H FILE
  # get_target_property(LIBRARY_STATE MPE TYPE)
  if(COMPILATION_PLATFORM STREQUAL "WIN32")
    add_library(MPE SHARED
      ${MPE_CPP}
      ${MPE_WIN32_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    add_library(MPE SHARED
      ${MPE_CPP}
      ${MPE_UNIX_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    add_library(MPE SHARED
      ${MPE_CPP}
      ${MPE_OSX_CPP}
    )
  endif()

  target_compile_definitions(MPE PUBLIC MPE_DYNAMIC_LIBRARY)
  target_compile_definitions(MPE PRIVATE MPE_BUILD_DLL)

else()
  message(FATAL_ERROR "LIBRARY TYPE {${MPE_LIBRARY_TYPE}} NOT SUPPORTED.")
endif()

# COMPILER DEFINITIONS FOR MPE
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_WINDOWS)

elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_LINUX)

elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_OSX)
endif()

target_compile_definitions(MPE PUBLIC MPE_ENABLE_ASSERTS)
target_compile_definitions(MPE PUBLIC MPE_COMPILER_${CURRENT_COMPILER})

# ENABLE PROFILING FOR DEBUG BUILS
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_definitions(MPE PUBLIC MPE_CORE_DEBUG_PROFILING)
  target_compile_definitions(MPE PUBLIC MPE_DEBUG_PROFILING)
  target_compile_definitions(MPE PUBLIC MPE_ENABLE_DEBUG_LOG)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

target_compile_definitions(MPE PUBLIC MPE_FULL_VERSION="${PROJECT_FULL_VERSION}")

if(${VERBOSE})
  get_target_property(DEFINITIONS_LIST MPE COMPILE_DEFINITIONS)
  message(STATUS "MPE COMPILE DEFINITIONS: ${DEFINITIONS_LIST}")
endif()

target_compile_features(MPE PUBLIC ${CXX_VERSION_NAME})
set_target_properties(MPE PROPERTIES VERSION ${PROJECT_FULL_VERSION})

set_target_properties(MPE PROPERTIES OUTPUT_NAME "MPE")

# MAKE SURE TO INCLUDE LIBRARY DIRECTORIES
# target_include_directories(MPE
# PRIVATE "${glad_DIR}/include"
# PRIVATE "${imgui_DIR}"
# )
# if(${VERBOSE})
# # PRINT INCLUDE DIRECTORIES
# get_target_property(INCLUDE_DIRECTORIES MPE INCLUDE_DIRECTORIES)
# message(STATUS "MPE INCLUDE DIRECTORIES: ${INCLUDE_DIRECTORIES}")
# endif()

# ADD MPE DEPENDENCIES
target_link_libraries(
  MPE
  PUBLIC fmt::fmt
  PUBLIC spdlog::spdlog

  # OpenGL::GL
  PRIVATE glad
  PRIVATE glfw
  PUBLIC imgui
  PRIVATE glm::glm
  PRIVATE Stb

  # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
)

if(COMPILATION_PLATFORM STREQUAL "OSX")
  target_link_libraries(
    MPE
    PRIVATE ${COCOA_LIBRARY}
  )
endif()

if(COMPILATION_PLATFORM STREQUAL "UNIX")
  target_link_libraries(
    MPE
    PRIVATE ${GTK3_LIBRARIES}
  )
endif()

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(MPE
  PRIVATE
  ${Stb_INCLUDE_DIRS}
)

# ADD MPEPCH.H AS A PRECOMPILED HEADER FILE
target_precompile_headers(MPE PUBLIC
  "${PROJECT_SOURCE_DIR}/MPE/MPEPCH.h")

# ADD INCLUDE DIRECTORIES TO MAKE INCLUDES EASY TO MANAGE
target_include_directories(MPE
  PRIVATE "${PROJECT_SOURCE_DIR}"
  PRIVATE "${PROJECT_SOURCE_DIR}/MPE"

  # "${PROJECT_SOURCE_DIR}/MPE"
)

if(COMPILATION_PLATFORM STREQUAL "UNIX")
  target_include_directories(MPE
    PRIVATE "${GTK3_INCLUDE_DIRS}")
endif()

# target_include_directories(MPE PUBLIC
# "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB")
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  # INSTALLATION FOR LIBRARIES
  # EXAMPLES FOR FUTURE
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # MPE DEBUG DLLS
    set(MPE_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Debug/MPE.dll)
    set(DEPENENDENCY_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Debug/fmtd.dll
      ${PROJECT_SOURCE_DIR}/Build/Debug/spdlogd.dll

      # ${PROJECT_SOURCE_DIR}/Build/Debug/gladd.dll
      # ${PROJECT_SOURCE_DIR}/Build/Debug/glfw3d.dll
      # ${PROJECT_SOURCE_DIR}/Build/Debug/imguid.dll
      # ${PROJECT_SOURCE_DIR}/Build/Debug/glmd.dll
    )
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # MPE RELEASE DLLS
    set(MPE_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Release/MPE.dll)
    set(DEPENENDENCY_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Release/fmt.dll
      ${PROJECT_SOURCE_DIR}/Build/Release/spdlog.dll

      # ${PROJECT_SOURCE_DIR}/Build/Release/glad.dll
      # ${PROJECT_SOURCE_DIR}/Build/Release/glfw3.dll
      # ${PROJECT_SOURCE_DIR}/Build/Release/imgui.dll
      # ${PROJECT_SOURCE_DIR}/Build/Release/glm.dll
    )
  endif()

  if(${VERBOSE})
    message(STATUS "MPE DLL FILES: ${MPE_DLL_FILES}")
    message(STATUS "DEPENDENCY DLL FILES: ${DEPENENDENCY_DLL_FILES}")
  endif()
endif()

# INSTALLATION PROCEDURE FOR MPE
install(
  TARGETS MPE
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

if(${INSTALL_DLLS})
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # EXAMPLES FOR FUTURE
  # install(FILES ${GTK_DLL_DEBUG_FILES} DESTINATION bin) install(FILES
  # ${MPE_DLL_DEBUG_FILES} DESTINATION bin)
  # install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION bin)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # EXAMPLES FOR FUTURE
    # install(FILES ${GTK_DLL_RELEASE_FILES} DESTINATION bin) install(FILES
    # ${MPE_DLL_RELEASE_FILES} DESTINATION bin)
    # install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION bin)
  endif()
endif()

# PUBLIC INCLUDES
set(MPE_PUBLIC_INCLUDES
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/MPE"
)

if(${MAIN_TEST})
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tests")
endif()

if(${EXAMPLES})
  add_subdirectory("${PROJECT_SOURCE_DIR}/Examples")
endif()

# TEMPORARY

# ADDING DUMMY EXECUTABLE
if(DUMMY_EXECUTABLE)
  add_executable(DUMMY "${PROJECT_SOURCE_DIR}/DUMMY/main.cpp")

  target_link_libraries(DUMMY PRIVATE
    MPE
  )
  target_include_directories(DUMMY PRIVATE ${MPE_PUBLIC_INCLUDES})

  # COMPILER DEFINITIONS FOR DUMMY
  # THIS IS NEEDED AS CMAKE IGNORES PUBLIC/PRIVATE/INTERFACE FOR DEFINITIONS FOR SOME REASON
  # TODO: FIND A WAY TO FIX THIS ISSUE
  if(COMPILATION_PLATFORM STREQUAL "WIN32")
    target_compile_definitions(DUMMY PUBLIC MPE_PLATFORM_WINDOWS)
  elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    target_compile_definitions(DUMMY PUBLIC MPE_PLATFORM_LINUX)
  elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    target_compile_definitions(DUMMY PUBLIC MPE_PLATFORM_OSX)
  endif()

  target_compile_definitions(DUMMY PUBLIC MPE_ENABLE_ASSERTS)
  target_compile_definitions(DUMMY PUBLIC MPE_COMPILER_${CURRENT_COMPILER})

  if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(DUMMY PUBLIC MPE_CORE_DEBUG_PROFILING)
    target_compile_definitions(DUMMY PUBLIC MPE_DEBUG_PROFILING)
    target_compile_definitions(DUMMY PUBLIC MPE_ENABLE_DEBUG_LOG)
  endif(CMAKE_BUILD_TYPE STREQUAL Debug)

  if(MPE_LIBRARY_TYPE STREQUAL SHARED)
    target_compile_definitions(DUMMY PUBLIC MPE_DYNAMIC_LIBRARY)
  else()
    target_compile_definitions(DUMMY PUBLIC MPE_STATIC_LIBRARY)
  endif()

  if(${VERBOSE})
    get_target_property(DEFINITIONS_LIST DUMMY COMPILE_DEFINITIONS)
    message(STATUS "DUMMY COMPILE DEFINITIONS: ${DEFINITIONS_LIST}")
  endif()

  # INSTALLATION PROCEDURE
  install(
    TARGETS DUMMY
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:DUMMY> DESTINATION bin)
endif(DUMMY_EXECUTABLE)

# TEMPORARY

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message("MPE SUPPORTS ONLY X64 SYSTEMS.")
  return()
endif()

# TODO: Find a way to fix this issue without having to run a script or manually
# copying the dlls. install(SCRIPT
# "${CMAKE_CURRENT_SOURCE_DIR}/utils/core_copy_missing_dlls.cmake")

# ##############################################################################
# PROJECTS SANDBOX
if(${MPE_PROJECTS})
  # ADD "SANDBOX" EXECUTABLE - THE ENTRYPOINT TO MPE
  add_executable(SANDBOX "${PROJECT_SOURCE_DIR}/Sandbox/Sandbox.cpp")

  target_include_directories(SANDBOX PUBLIC "${PROJECT_SOURCE_DIR}")
  target_link_libraries(SANDBOX PUBLIC MPE)

  # ADDING SANDBOX 2D LAYER
  file(GLOB_RECURSE SANDBOX2D_CPP
    "${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D/*.cpp")
  file(GLOB_RECURSE SANDBOX2D_H
    "${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D/*.h")
  add_library(SANDBOX2D STATIC ${SANDBOX2D_CPP})
  target_include_directories(SANDBOX2D PUBLIC ${SANDBOX2D_H})
  target_link_libraries(SANDBOX2D PUBLIC MPE)
  target_link_libraries(SANDBOX PUBLIC SANDBOX2D)

  target_compile_features(SANDBOX PUBLIC ${CXX_VERSION_NAME})
  set_target_properties(SANDBOX PROPERTIES VERSION ${PROJECT_FULL_VERSION})
  set_target_properties(SANDBOX PROPERTIES OUTPUT_NAME "MPE-SANDBOX")

  # COMPILER DEFINITIONS FOR SANDBOX
  target_compile_definitions(SANDBOX PUBLIC SANDBOX_PLATFORM_WINDOWS)

  target_compile_definitions(SANDBOX PUBLIC SANDBOX_ENABLE_ASSERTS)
  target_compile_definitions(SANDBOX PUBLIC SANDBOX_COMPILER_${CURRENT_COMPILER})

  # ENABLE PROFILING FOR DEBUG BUILDS
  if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(SANDBOX PUBLIC SANDBOX_DEBUG_PROFILING)
    target_compile_definitions(SANDBOX PUBLIC SANDBOX_ENABLE_DEBUG_LOG)
  endif(CMAKE_BUILD_TYPE STREQUAL Debug)

  if(${VERBOSE})
    get_target_property(DEFINITIONS_LIST SANDBOX COMPILE_DEFINITIONS)
    message(STATUS "SANDBOX COMPILE DEFINITIONS: ${DEFINITIONS_LIST}")
  endif()

  # COMPILER DEFINITIONS FOR SANDBOX
  target_compile_definitions(SANDBOX PUBLIC MPE_PLATFORM_WINDOWS)

  # COMPILER DEFINITIONS FOR SANDBOX 2D
  target_compile_definitions(SANDBOX2D PUBLIC MPE_PLATFORM_WINDOWS)

  # INSTALLATION PROCEDURE
  install(
    TARGETS SANDBOX
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:SANDBOX> DESTINATION bin)

  if(${VERBOSE})
    message(STATUS "MPE-SANDBOX ADDED.")
  endif()
endif(${MPE_PROJECTS})

# ##############################################################################
# TESTS add_executable(TEST "${PROJECT_SOURCE_DIR}/Tests/Unit.cpp")

# file(GLOB_RECURSE TEST_CPP "${PROJECT_SOURCE_DIR}/Tests/*.cpp"
# #"${PROJECT_SOURCE_DIR}/Tests/Primitive/*.cpp" )

# file(GLOB_RECURSE TEST_H "${PROJECT_SOURCE_DIR}/Tests/*.h"
# #"${PROJECT_SOURCE_DIR}/Tests/Primitive/*.h" )

# # add_library(TEST_SRC STATIC ${TEST_CPP}) #
# target_include_directories(TEST_SRC PUBLIC ${TEST_H}) #
# target_link_libraries(TEST_SRC PUBLIC MPE) # target_link_libraries(TEST PUBLIC
# MPE) # target_link_libraries(TEST PUBLIC TEST_SRC)

# target_link_libraries(TEST PUBLIC MPE) target_include_directories(TEST PUBLIC
# ${TEST_CPP} ${TEST_H})

# ##############################################################################
# PROJECTS PONG
if(${MPE_PROJECTS})
  add_executable(PONG
    "${PROJECT_SOURCE_DIR}/Projects/Pong/ProjectSelector.cpp")

  file(GLOB_RECURSE PONG_CPP
    "${PROJECT_SOURCE_DIR}/Projects/Pong/*.cpp"
    "${PROJECT_SOURCE_DIR}/Projects/Pong/Core/*.cpp")

  file(GLOB_RECURSE PONG_H
    "${PROJECT_SOURCE_DIR}/Projects/Pong/*.h"
    "${PROJECT_SOURCE_DIR}/Projects/Pong/Core/*.h")

  add_library(PONG_SRC STATIC ${PONG_CPP})
  target_include_directories(PONG_SRC PUBLIC ${PONG_H})
  target_link_libraries(PONG_SRC PUBLIC MPE)
  target_link_libraries(PONG PUBLIC MPE)
  target_link_libraries(PONG PUBLIC PONG_SRC)

  target_compile_features(PONG PUBLIC ${CXX_VERSION_NAME})
  set_target_properties(PONG PROPERTIES VERSION ${PROJECT_FULL_VERSION})
  set_target_properties(PONG PROPERTIES OUTPUT_NAME "MPE-PONG")

  # COMPILER DEFINITIONS FOR PONG
  target_compile_definitions(PONG PUBLIC PONG_PLATFORM_WINDOWS)

  target_compile_definitions(PONG PUBLIC PONG_ENABLE_ASSERTS)
  target_compile_definitions(PONG PUBLIC PONG_COMPILER_${CURRENT_COMPILER})

  # ENABLE PROFILING FOR DEBUG BUILDS
  if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(PONG PUBLIC PONG_DEBUG_PROFILING)
    target_compile_definitions(PONG PUBLIC PONG_ENABLE_DEBUG_LOG)
  endif(CMAKE_BUILD_TYPE STREQUAL Debug)

  if(${VERBOSE})
    get_target_property(DEFINITIONS_LIST PONG COMPILE_DEFINITIONS)
    message(STATUS "PONG COMPILE DEFINITIONS: ${DEFINITIONS_LIST}")
  endif()

  # INSTALLATION PROCEDURE
  install(
    TARGETS PONG
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:PONG> DESTINATION bin)

  if(${VERBOSE})
    message(STATUS "MPE-PONG ADDED.")
  endif()
endif(${MPE_PROJECTS})

# ##############################################################################

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES EVEN THOUGH
# CURRENTLY ONLY WINDOWS IS SUPPORTED, ADDING THIS CHECK WILL MAKE IT EASIER TO
# ADD SUPPORT FOR OTHER SYSTEMS IN THE FUTURE
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  # TOGGLE WIN CMD RESOURCE COPY SCRIPT
  set(CMD_RES_CPY OFF)

  if(CMD_RES_CPY)
    # ADDING A SCRIPT THAT MIRROS THE FOLDER IN source/Sandbox/Data to build/Data
    add_custom_command(
      TARGET SANDBOX
      POST_BUILD
      COMMAND ${PROJECT_SOURCE_DIR}/utility/scripts/windows/CPBMDTB.bat)

    # THIS MIGHT THROW SOME ERRORS IN CMAKE, BUT IF BUILT AGAIN SHOULD WORK FINE
    add_custom_target(
      DATASCRIPT
      COMMAND ${PROJECT_SOURCE_DIR}/utility/scripts/windows/CPBMDTB.bat)

    add_dependencies(SANDBOX DATASCRIPT)
  endif(CMD_RES_CPY)
endif(COMPILATION_PLATFORM STREQUAL "WIN32")

if(COMPILATION_PLATFORM STREQUAL "UNIX")
endif(COMPILATION_PLATFORM STREQUAL "UNIX")

if(COMPILATION_PLATFORM STREQUAL "OSX")
endif(COMPILATION_PLATFORM STREQUAL "OSX")

message(STATUS "MPE/CMAKE SUCCESSFULLY FINISHED.")
