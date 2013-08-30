set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenAL)

file(GLOB luabindings_SOURCES *.cpp)
add_library(LuaBindings ${luabindings_SOURCES})