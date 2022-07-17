cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)
project(MERELY_PRIMITIVE_ENGINE)

# MPE CURRENTLY SUPPORTS ONLY WINDOWS-X64 SYSTEMS.

# VCPKG IS USED TO MANAGE DEPENDENCIES. SPECIFICALLY X64 TRIPLET ([x64-windows]).
# ANY OTHER DEPENDENCY MANAGER CAN BE USED OR EXCLUDED ENTIRELY.

# SET TOOLCHAIN FILE IF NEEDED.
# set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/scripts/buildsystems/vcpkg.cmake)

# FOR ME IT'S EASIER TO HAVE ALL DEPENDECIES LINKED TO CMAKE DIRECTLY.
include_directories(C:/vcpkg/installed/x64-windows/include)
LINK_DIRECTORIES(C:/vcpkg/installed/x64-windows/lib)

# FIND DEPENDCIES PROVIDED BY DEPENDENCY MANAGER.
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
# find_package(imguizmo CONFIG REQUIRED)
# find_package(yaml-cpp CONFIG REQUIRED)

# MPE LIBRARY .CPP FILES.
file(GLOB_RECURSE MPE_CPP
                        "${PROJECT_SOURCE_DIR}/source/MPE/*.cpp"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Base/*.cpp"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Events/*.cpp"
                        "${PROJECT_SOURCE_DIR}/source/MPE/ImGui/*.cpp"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Platform/OpenGL/*.cpp"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Platform/Windows/*.cpp"
)

# MPE LIBRARY .H FILES.
file(GLOB RECURSE MPE_H
                        "${PROJECT_SOURCE_DIR}/source/MPE/Base/*.h"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Events/*.h"
                        "${PROJECT_SOURCE_DIR}/source/MPE/ImGui/*.h"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Platform/OpenGL/*.h"
                        "${PROJECT_SOURCE_DIR}/source/MPE/Platform/Windows/*.h"
)

# MAKE MPE LIBRARY STATIC - DYNAMIC LIBRARY UNSUPPORTED.
add_library(MPE STATIC ${MPE_CPP})

# ADD MPE DEPENDENCIES.
target_link_libraries(MPE PUBLIC 
                                fmt::fmt
                                spdlog::spdlog
                                OpenGL::GL
                                glad::glad
                                glfw
                                imgui::imgui
                                glm::glm

                                # CURRENTLY NOT IN USE:
                                #imguizmo::imguizmo
                                #yaml-cpp
                                )

# WILL BE NEEDED LATER.
# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")

# ADD MPEPCH.H AS A PRECOMPILED HEADER FILE.
target_precompile_headers(MPE PUBLIC "${PROJECT_SOURCE_DIR}/source/MPE/MPEPCH.h")

# ADD INCLUDE DIRECTORIES TO MAKE INCLUDES EASY TO MANAGE.
target_include_directories(MPE PUBLIC ${MPE_H})
target_include_directories(MPE PUBLIC "${PROJECT_SOURCE_DIR}/source")

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES.
if(WIN32)

        # COMPILER DEFINITIONS FOR MPE.
        target_compile_definitions(MPE PUBLIC MPE_PLATFORM_WINDOWS)
        target_compile_definitions(MPE PUBLIC MPE_STATIC_LIBRARY)
        target_compile_definitions(MPE PUBLIC MPE_ENABLE_ASSERTS)

        # ADD "SANDBOX" EXECUTABLE - THE ENTRYPOINT TO MPE.
        add_executable(SANDBOX "${PROJECT_SOURCE_DIR}/source/Sandbox/Sandbox.cpp")
        target_include_directories(SANDBOX PUBLIC "${PROJECT_SOURCE_DIR}/source")
        target_link_libraries(SANDBOX PUBLIC MPE)

        # COMPILER DEFINITIONS FOR SANDBOX.
        target_compile_definitions(SANDBOX PUBLIC MPE_PLATFORM_WINDOWS)

endif (WIN32)

# DOUBLE CHECKS IF BUILDSYSTEM IS USING ONLY STATIC LIBRARY.
# DYNAMIC LIBRARIES ARE POSSIBLE TO BE USED, BUT IS NOT INTENDED WITH THIS PROJECT.
# DYNAMIC LIBRARIES ARE STILL IMPLEMENTED AS AN EXAMPLE AND CAN STILL BE USED IF THE USERS DEEMS THAT IT IS NEEDED.
# REMOVE #ERROR PREPROCESSOR DECLARATION ON LINE 17 IN CORE.H FILE
get_target_property(LIBRARY_STATE MPE TYPE)
if(${LIBRARY_STATE} STREQUAL SHARED_LIBRARY)

        # CURRENTLY NOT WORKING AT ALL.
        target_compile_definitions(MPE PUBLIC MPE_PLATFORM_WINDOWS)
        target_compile_definitions(MPE PUBLIC MPE_DYNAMIC_LIB)
        target_compile_definitions(MPE PUBLIC MPE_ENABLE_ASSERTS)
        target_compile_definitions(SANDBOX PUBLIC MPE_PLATFORM_WINDOWS)
        target_compile_definitions(SANDBOX PUBLIC MPE_DYNAMIC_LIB)
        target_compile_definitions(SANDBOX PUBLIC MPE_BUILD_DLL)

endif(${LIBRARY_STATE} STREQUAL SHARED_LIBRARY)

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Please switch to x64 build.")
    return()
endif()