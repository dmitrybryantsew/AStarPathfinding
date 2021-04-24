cmake_minimum_required(VERSION 3.5)

set(HUNTER_ROOT  "E://.hunter")

#SET(GCC_COVERAGE_COMPILE_FLAGS -shared -nostartfiles)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/Hunter/HunterGate.cmake)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.253.tar.gz"
    SHA1 "88ea6d37c897a81a080eb9ae0f69d7807bbb3c73"
    LOCAL
)

project(AStarPathfinding)

hunter_add_package(SFML)

file(GLOB_RECURSE SOURSES src/*.cpp)

include_directories("${PROJECT_SOURCE_DIR}/include")
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} ${SOURSES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
