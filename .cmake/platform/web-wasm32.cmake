set(PLATFORM_ID Emscripten)
set(CMAKE_SYSTEM_NAME Emscripten)
set(CMAKE_SYSTEM_PROCESSOR wasm32)

set(CMAKE_CROSSCOMPILING TRUE)

set(SYSTEM_NAME web)
set(SYSTEM_ARCH wasm32)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(TARGET_ALIAS template_debug)
else()
	set(TARGET_ALIAS template_release)
endif()

# C++20: use em-scan-deps in .cmake/emscripten
set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS ${CMAKE_SOURCE_DIR}/.cmake/emscripten/em-scan-deps)

# options below are mostly taken from emscripten's .cmake module
# so we don't have to bother trying to locate the user's SDK
set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)
set(CMAKE_NM emnm)
set(CMAKE_AR emar)
set(CMAKE_RANLIB emranlib)
set(CMAKE_C_COMPILER_AR "${CMAKE_AR}")
set(CMAKE_CXX_COMPILER_AR "${CMAKE_AR}")
set(CMAKE_C_COMPILER_RANLIB "${CMAKE_RANLIB}")
set(CMAKE_CXX_COMPILER_RANLIB "${CMAKE_RANLIB}")

set(CMAKE_LIBRARY_ARCHITECTURE "wasm32-emscripten")
set(CMAKE_SIZEOF_VOID_P 4)
set(CMAKE_C_SIZEOF_DATA_PTR 4)
set(CMAKE_CXX_SIZEOF_DATA_PTR 4)

set(CMAKE_EXECUTABLE_SUFFIX ".js")

set(CMAKE_C_USE_RESPONSE_FILE_FOR_LIBRARIES 1)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_LIBRARIES 1)
set(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS 1)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES 1)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 1)

set(CMAKE_C_RESPONSE_FILE_LINK_FLAG "@")
set(CMAKE_CXX_RESPONSE_FILE_LINK_FLAG "@")

set(WIN32)
set(APPLE)
set(UNIX 1)

# Enable $<LINK_LIBRARY:WHOLE_ARCHIVE,static_lib> for CMake 3.24+
set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE "-Wl,--whole-archive" "<LINK_ITEM>" "-Wl,--no-whole-archive")
set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE_SUPPORTED TRUE)

set(CMAKE_SHARED_LIBRARY_SONAME_C_FLAG "-Wl,-soname,")
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

# Set a global EMSCRIPTEN variable that can be used in client CMakeLists.txt to
# detect when building using Emscripten.
set(EMSCRIPTEN 1 CACHE INTERNAL "If true, we are targeting Emscripten output.")

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
set(CMAKE_SHARED_LIBRARY_SUFFIX) # remove the suffix from the shared lib
set(CMAKE_STRIP TRUE)  # used by default in pybind11 on .so modules

add_compile_options(-sUSE_PTHREADS=1 -sSIDE_MODULE=1)
add_link_options(-sSIDE_MODULE=1 -sUSE_PTHREADS=1 --shared-memory --import-memory --max-memory=2130706432)

# Hardwire support for cmake-2.8/Modules/CMakeBackwardsCompatibilityC.cmake
# without having CMake to try complex things to autodetect these:
set(CMAKE_SKIP_COMPATIBILITY_TESTS 1)
set(CMAKE_SIZEOF_CHAR 1)
set(CMAKE_SIZEOF_UNSIGNED_SHORT 2)
set(CMAKE_SIZEOF_SHORT 2)
set(CMAKE_SIZEOF_INT 4)
set(CMAKE_SIZEOF_UNSIGNED_LONG 4)
set(CMAKE_SIZEOF_UNSIGNED_INT 4)
set(CMAKE_SIZEOF_LONG 4)
set(CMAKE_SIZEOF_FLOAT 4)
set(CMAKE_SIZEOF_DOUBLE 8)
set(CMAKE_HAVE_LIMITS_H 1)
set(CMAKE_HAVE_UNISTD_H 1)
set(CMAKE_HAVE_PTHREAD_H 1)
set(CMAKE_HAVE_SYS_PRCTL_H 1)
set(CMAKE_WORDS_BIGENDIAN 0)
set(CMAKE_C_BYTE_ORDER "LITTLE_ENDIAN")
set(CMAKE_CXX_BYTE_ORDER "LITTLE_ENDIAN")
set(CMAKE_DL_LIBS)
