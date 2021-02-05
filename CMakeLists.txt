cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(cs2d_vscode)


set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 17)

enable_language(CXX)

#set(CMAKE_SOURCE_DIR ../)
#set(CMAKE_BINARY_DIR ../)

# Add source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)
	
#list(REMOVE_ITEM SOURCE_FILES "src/Common.cpp")
#list(REMOVE_ITEM HEADER_FILES "src/Common.hpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*src/Common.cpp$")
list(FILTER HEADER_FILES EXCLUDE REGEX ".*src/Common.hpp$")
	
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Define the include DIRs
include_directories("${CMAKE_SOURCE_DIR}/include")


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin/Release)

execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})


# glfw
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glew EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE libglew_static)

# freetype
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/freetype EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE freetype)


if(MINGW)
	SET(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc")
endif()

if(MSVC_IDE)
	message("msvc")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin)
	target_compile_definitions(${PROJECT_NAME} PUBLIC -D_UNICODE -DUNICODE)
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()