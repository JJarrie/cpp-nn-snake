cmake_minimum_required(VERSION 3.13)

project(snakenn VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp)

set(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_allegro5.cpp
)

include_directories(includes imgui /usr/local/include/allegro5)
link_directories(/usr/local/lib)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${IMGUI_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} allegro allegro_primitives ${CMAKE_DL_LIBS})