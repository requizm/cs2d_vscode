cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
#set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "VCPKG Target Triplet to use")
project(cs2d_vscode)

set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 17)

enable_language(CXX)

# Add source files
# file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/include/tracy/TracyClient.cpp)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*src/Common.cpp$")
list(FILTER HEADER_FILES EXCLUDE REGEX ".*src/Common.hpp$")

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin/Release)
execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if(UNIX)
	message("unix")
	add_definitions(-DLINUX)
endif(UNIX)

if(WIN32)
	message("win32")
	add_definitions(-DWIN32 -DGLEW_STATIC)
endif(WIN32)


include_directories("${CMAKE_SOURCE_DIR}/include")

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(FREETYPE CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(spdlog CONFIG REQUIRED)

include_directories(${glfw3_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${spdlog_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL fmt::fmt glfw freetype GLEW::GLEW spdlog::spdlog)

if(MINGW)
	SET(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc")
	target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 imagehlp)
endif(MINGW)

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
endif(MSVC_IDE)