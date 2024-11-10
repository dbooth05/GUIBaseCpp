cmake_minimum_required(VERSION 3.10)
project(ImGuiSDL2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# imgui setup
include_directories(include)
set(sources

)

# sdl2 setup
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# add executable
add_executable(ImGuiSDL2  
    include/imgui/imgui.cpp
    include/imgui/imgui_demo.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp
    include/imgui/backends/imgui_impl_sdlrenderer2.cpp
    include/imgui/backends/imgui_impl_sdl2.cpp
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/imgui
    ${CMAKE_SOURCE_DIR}/include/imgui/backends
)

# link sdl2 library
target_link_libraries(ImGuiSDL2 PRIVATE
    ${SDL2_LIBRARIES} 
)
