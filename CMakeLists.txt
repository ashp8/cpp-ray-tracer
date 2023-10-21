cmake_minimum_required(VERSION 3.19)
project(rayTracing)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(
        include/
        qbLinAlg/
)

file(GLOB SRC_FILES "src/*.cpp")
file(GLOB HEADER_FILES "include/*.h")

add_executable(rayTracing
        ${SRC_FILES}
        ${HEADER_FILES})

target_link_libraries(rayTracing ${SDL2_LIBRARIES})