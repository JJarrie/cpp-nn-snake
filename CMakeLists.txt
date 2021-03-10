cmake_minimum_required(VERSION 3.13)

project(snakenn VERSION 0.1)
set(CMAKE_CXX_FLAGS "-DIMGUI_IMPL_OPENGL_LOADER_GLAD")

set(OpenGL_GL_PREFERENCE "GLVND")

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library("glad" "glad/src/glad.c")
include_directories("glad/include")

file(GLOB SOURCES src/*.cpp)

set(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_sdl.cpp
)

include_directories("includes" "imgui")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${IMGUI_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} "glad" ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARIES} ${CMAKE_DL_LIBS})