set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB graphics_sdl_SOURCES *.cpp)

add_library(GraphicsSDL ${graphics_sdl_SOURCES})