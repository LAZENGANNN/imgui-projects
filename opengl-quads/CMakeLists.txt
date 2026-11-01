cmake_minimum_required(VERSION 4.4.0)

project(project2)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include)
set(GLFW_LIB_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/lib)
set(IMGUI_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${GLFW_INCLUDE_DIR}
)

add_executable(app main.cpp)

target_include_directories(app PUBLIC
    ${GLFW_INCLUDE_DIR}
    ${IMGUI_DIR}
)

target_link_directories(app PUBLIC ${GLFW_LIB_DIR})

target_link_libraries(app PRIVATE
    imgui
    glfw3
    opengl32
)
