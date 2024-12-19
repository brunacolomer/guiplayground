cmake_minimum_required(VERSION 3.5)
project(ImGuiExample LANGUAGES C CXX)

# Configura C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directori de llibreries de tercers
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# =======================
# GLFW
# =======================
add_subdirectory(${THIRD_PARTY_DIR}/glfw)

# =======================
# ImGui
# =======================
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

# =======================
# ImPlot
# =======================
file(GLOB IMPLOT_SRC
    ${THIRD_PARTY_DIR}/implot/*.cpp
)
add_library(implot STATIC ${IMPLOT_SRC})
target_include_directories(implot PUBLIC
    ${THIRD_PARTY_DIR}/implot
    ${THIRD_PARTY_DIR}/imgui
)

# =======================
# GLAD
# =======================
add_library(glad STATIC ${THIRD_PARTY_DIR}/glad/glad.c)
target_include_directories(glad PUBLIC ${THIRD_PARTY_DIR}/glad)

# =======================
# Native File Dialog (NFD)
# =======================
# Configura les fonts de NFD (Linux només)
file(GLOB NFD_SRC
    ${THIRD_PARTY_DIR}/nfd/nfd_common.c
    ${THIRD_PARTY_DIR}/nfd/nfd_gtk.c       # Linux
)
# Verifica que els fitxers existeixin
if(NFD_SRC)
    add_library(nfd STATIC ${NFD_SRC})
    target_include_directories(nfd PUBLIC ${THIRD_PARTY_DIR}/nfd/include)

    # Afegeix dependència de GTK+3 per Linux
    if(UNIX AND NOT APPLE)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
        target_include_directories(nfd PUBLIC ${GTK3_INCLUDE_DIRS})
        target_link_libraries(nfd ${GTK3_LIBRARIES})
    endif()
else()
    message(FATAL_ERROR "No sources found for Native File Dialog! Verifica les rutes.")
endif()

# =======================
# Codi principal
# =======================
# Busca els fitxers de codi del projecte
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Executable principal
add_executable(ImGuiExample ${SRC_FILES})

# Inclou directoris d'encapçalaments per al projecte
target_include_directories(ImGuiExample PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# =======================
# Enllaça les llibreries necessàries
# =======================
target_link_libraries(ImGuiExample
    imgui
    implot
    glfw
    glad
    GL
    nfd # Enllaça Native File Dialog
)
