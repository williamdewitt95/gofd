cmake_minimum_required(VERSION 3.0)

project(gofd VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

# add the executable
add_executable(gofd
	${ENGINE_SRC}
	${GAME_SRC}
)

target_include_directories(gofd PUBLIC
	"${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(
	gofd
	glfw ${CMAKE_DL_LIBS}
	${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
)