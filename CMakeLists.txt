cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(cs2d_vscode)

set(CMAKE_C_COMPILER C:/ProgramData/chocolatey/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/ProgramData/chocolatey/bin/g++.exe)
enable_language(CXX)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib/x64)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)
	
#list(REMOVE_ITEM SOURCE_FILES "src/Common.cpp")
#list(REMOVE_ITEM HEADER_FILES "src/Common.h")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*src/Common.cpp$")
list(FILTER HEADER_FILES EXCLUDE REGEX ".*src/Common.h$")
	
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# We need a CMAKE_DIR with some code to find external dependencies
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
#find_package(OpenGL REQUIRED)

# FREETYPE
#find_package(Freetype REQUIRED)

# GLAD
#add_library(GLAD "include/glad.c")

# Put all libraries into a variable
set(LIBS ${CMAKE_SOURCE_DIR}/lib/x64/libglfw3dll.a glew32s glew32 glfw3 opengl32 freetype stdc++fs)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})

# Copy dlls
#if(WIN32)
#	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#		COMMAND ${CMAKE_COMMAND} -E copy_directory
#		"${PROJECT_SOURCE_DIR}/dlls"
#		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
#endif()
