cmake_minimum_required(VERSION 3.24)
project(Hexagon)

set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS FALSE)#!!
include(FetchContent)
FETCHCONTENT_DECLARE(SFML
        GIT_REPOSITORY
        https://github.com/SFML/SFML.git)
FETCHCONTENT_MAKEAVAILABLE(SFML)
add_executable(Hexagon main.cpp)
target_link_libraries(Hexagon
        sfml-system sfml-window sfml-graphics)

