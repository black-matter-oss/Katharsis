set(PROJECT_NAME quantum)
add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	LINKER_LANGUAGE CXX
	PREFIX lib
	OUTPUT_NAME ${PROJECT_NAME}.${SYSTEM_NAME}.${TARGET_ALIAS}.${SYSTEM_ARCH})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC godot::cpp)

# === sources
#glob_sources(${PROJECT_NAME} katharsis)
glob_sources(${PROJECT_NAME} quantum)
# sources ===

# copy resulting binary to /bin
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:${PROJECT_NAME}>
	${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin/${SYSTEM_NAME}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)
