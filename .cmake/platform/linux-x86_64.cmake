set(PLATFORM_ID Linux)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(SYSTEM_NAME linux)
set(SYSTEM_ARCH x86_64)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(TARGET_ALIAS template_debug)
else()
	set(TARGET_ALIAS template_release)
endif()

set(CMAKE_C_COMPILER clang CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER clang++ CACHE STRING "C++ compiler")
