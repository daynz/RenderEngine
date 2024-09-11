cmake_minimum_required(VERSION 3.20)
project(RenderEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("lib/imgui")
include_directories("lib/imgui/backends")
include_directories("include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB PLATFORM_SRC
    ./lib/imgui/backends/imgui_impl_glfw.*
    ./lib/imgui/backends/imgui_impl_opengl3.*
    ./lib/imgui/*.h
    ./lib/imgui/*.cpp
)

add_executable(RenderEngine ${SOURCES} ${PLATFORM_SRC})

add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
add_subdirectory(lib/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
# Link OpenGL library
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})
endif()