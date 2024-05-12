cmake_minimum_required(VERSION 3.26)
project(MkUltraTron)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_FOLDER Tron)

# Code found at https://discourse.cmake.org/t/how-do-i-set-define-based-on-current-build-type/6890
if (DEBUG_MODE)
    add_compile_definitions("NDEBUG")
endif()

add_subdirectory(includes/imgui)
add_subdirectory(includes/soloud)
add_subdirectory(MkUltra)
add_subdirectory(Tron)