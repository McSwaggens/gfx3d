cmake_minimum_required(VERSION 3.10)

project(gfx3d CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Use vender agnostic opengl dispatch layer
# You can also use `cmake_policy(SET CMP0072 NEW)`
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_executable(gfx3d
	"src/main.cpp"
	"src/Engine.cpp"
	"src/shader.cpp"
	"src/Keyboard.cpp"
	"src/Time.cpp"
	"src/Window.cpp"
	"src/Buffer.cpp"
	"src/Quaternion.cpp"
	"src/Matrix.cpp"
	)
target_include_directories(gfx3d PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(gfx3d GLEW OpenGL glfw)

