cmake_minimum_required(VERSION 3.28)
project(Katharsis)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CXX_SOURCE_EXTENSION ".cpp")
set(CXX_HEADER_EXTENSION ".hpp")
set(CXX_MODULE_EXTENSION ".cppm")

# === macros
macro(glob_sources target directory)
	file(GLOB_RECURSE ADD_SOURCES CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/${directory}/*${CXX_SOURCE_EXTENSION}"
		"${CMAKE_CURRENT_SOURCE_DIR}/${directory}/*${CXX_HEADER_EXTENSION}")
	
	file(GLOB_RECURSE ADD_MODULES CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/${directory}/*${CXX_MODULE_EXTENSION}")

	target_sources(${target} PUBLIC
		${ADD_SOURCES})
	 target_sources(${target} PUBLIC
	 	FILE_SET CXX_MODULES
	 	FILES ${ADD_MODULES})
		
	 set_source_files_properties(${ADD_MODULES} PROPERTIES LANGUAGE CXX)
	
	unset(ADD_SOURCES)
	unset(ADD_MODULES)
endmacro()
# macros ===

include(.cmake/library/godot-cpp.cmake)
include(quantum.cmake)
