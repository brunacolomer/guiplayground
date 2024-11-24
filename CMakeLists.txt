cmake_minimum_required(VERSION 3.0)
project(ImGuiExample LANGUAGES C CXX)

# Configura C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directori de llibreries de tercers
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# Llibreria de GLFW
add_subdirectory(${THIRD_PARTY_DIR}/glfw)

# Fitxers d'ImGui
file(GLOB IMGUI_SRC
    ${THIRD_PARTY_DIR}/imgui/*.cpp
    ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    ${THIRD_PARTY_DIR}/imgui
    ${THIRD_PARTY_DIR}/imgui/backends
)

# Fitxers d'ImPlot
file(GLOB IMPLOT_SRC
    ${THIRD_PARTY_DIR}/implot/*.cpp
)

add_library(implot STATIC ${IMPLOT_SRC})
target_include_directories(implot PUBLIC
    ${THIRD_PARTY_DIR}/implot
    ${THIRD_PARTY_DIR}/imgui
)

# Fitxers de GLAD
add_library(glad STATIC ${THIRD_PARTY_DIR}/glad/glad.c)
target_include_directories(glad PUBLIC ${THIRD_PARTY_DIR}/glad)

# Busca automàticament els fitxers del directori src
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Executable principal
add_executable(ImGuiExample ${SRC_FILES})

# Inclou directoris d'encapçalaments
target_include_directories(ImGuiExample PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Enllaça les llibreries necessàries
target_link_libraries(ImGuiExample
    imgui
    implot
    glfw
    glad
    GL
)
