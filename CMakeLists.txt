cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(cs2d_vscode)


set(CMAKE_CXX_STANDARD 17)
enable_language(CXX)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib/64)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)
	
#list(REMOVE_ITEM SOURCE_FILES "src/Common.cpp")
#list(REMOVE_ITEM HEADER_FILES "src/Common.hpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*src/Common.cpp$")
list(FILTER HEADER_FILES EXCLUDE REGEX ".*src/Common.hpp$")
	
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})



# Put all libraries into a variable
set(LIBS ${CMAKE_SOURCE_DIR}/lib/64/libglfw3dll.a glew32s glew32 glfw3 opengl32 freetype)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})


