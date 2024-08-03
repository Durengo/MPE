if(${MPE_LIBRARY_TYPE} STREQUAL STATIC)
    add_library(MPE STATIC
        ${MPE_CPP}
        ${MPE_OSX_CPP}
    )

    target_compile_definitions(MPE PRIVATE MPE_STATIC_LIBRARY)
elseif(${MPE_LIBRARY_TYPE} STREQUAL SHARED)
    add_library(MPE SHARED
        ${MPE_CPP}
        ${MPE_OSX_CPP}
    )

    target_compile_definitions(MPE PUBLIC MPE_DYNAMIC_LIBRARY)
    target_compile_definitions(MPE PRIVATE MPE_BUILD_DLL)
else()
    message(FATAL_ERROR "LIBRARY TYPE {${MPE_LIBRARY_TYPE}} NOT SUPPORTED.")
endif()

target_compile_definitions(MPE PUBLIC MPE_PLATFORM_OSX)
target_compile_definitions(MPE PUBLIC MPE_ENABLE_ASSERTS)
target_compile_definitions(MPE PUBLIC MPE_COMPILER_${CURRENT_COMPILER})

# ENABLE PROFILING FOR DEBUG BUILS
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(MPE PUBLIC MPE_CORE_DEBUG_PROFILING)
    target_compile_definitions(MPE PUBLIC MPE_DEBUG_PROFILING)
    target_compile_definitions(MPE PUBLIC MPE_ENABLE_DEBUG_LOG)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

target_compile_definitions(MPE PUBLIC MPE_FULL_VERSION_${PROJECT_FULL_VERSION})

# CMAKE IS NOT INHERETING COMPILER FLAGS PROPERLY
set(MPE_PUBLIC_DEFINITIONS)

if(MPE_LIBRARY_TYPE STREQUAL SHARED)
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_DYNAMIC_LIBRARY)
else()
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_STATIC_LIBRARY)
endif()

if(COMPILATION_PLATFORM STREQUAL "WIN32")
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_WINDOWS)
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_LINUX)
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_LINUX MPE_PLATFORM_RPI4)
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_OSX)
endif()

list(APPEND MPE_PUBLIC_DEFINITIONS MPE_ENABLE_ASSERTS)
list(APPEND MPE_PUBLIC_DEFINITIONS MPE_COMPILER_${CURRENT_COMPILER})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_CORE_DEBUG_PROFILING MPE_DEBUG_PROFILING MPE_ENABLE_DEBUG_LOG)
endif()

list(APPEND MPE_PUBLIC_DEFINITIONS MPE_FULL_VERSION_${PROJECT_FULL_VERSION})

if(${VERBOSE})
    get_target_property(DEFINITIONS_LIST MPE COMPILE_DEFINITIONS)
    message("
-----------------------------------------------------------
MPE COMPILE DEFINITIONS\n")

    foreach(DEFINITION ${DEFINITIONS_LIST})
        message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()

target_compile_features(MPE PUBLIC ${CXX_VERSION_NAME})
set_target_properties(MPE PROPERTIES VERSION ${PROJECT_FULL_VERSION})

set_target_properties(MPE PROPERTIES OUTPUT_NAME "MPE")