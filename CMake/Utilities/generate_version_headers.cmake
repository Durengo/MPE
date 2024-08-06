# FIRST CHECK IF THESE VARIABLES ARE DEFINED
if(NOT DEFINED GIT_BRANCH)
    set(GIT_BRANCH "UNKNOWN")
endif()

if(NOT DEFINED GIT_COMMIT_HASH)
    set(GIT_COMMIT_HASH "UNKNOWN")
endif()

if(NOT DEFINED GIT_COMMIT_HASH_SHORT)
    set(GIT_COMMIT_HASH_SHORT "UNKNOWN")
endif()

if(NOT DEFINED PROJECT_FULL_VERSION)
    set(PROJECT_FULL_VERSION "UNKNOWN")
endif()

configure_file(
    ${PROJECT_SOURCE_DIR}/MPE/Core/_VERSION.h.in
    ${PROJECT_SOURCE_DIR}/MPE/Core/_VERSION.h
    @ONLY
)