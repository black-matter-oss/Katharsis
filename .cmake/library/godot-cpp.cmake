include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(godot-cpp
	URL https://github.com/godotengine/godot-cpp/archive/dfc51960f9563c6df39a1a0ab66350374f932897.tar.gz
)
FetchContent_MakeAvailable(godot-cpp)

# use hot reload automatically in debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(GODOT_USE_HOT_RELOAD ON)
endif()
