set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL REQUIRED)

file(GLOB physics_SOURCES *.cpp)
add_library(Physics ${physics_SOURCES})