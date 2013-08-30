cmake_minimum_required(VERSION 2.8)
project(rad)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

find_package(Lua51 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OggVorbis REQUIRED)
find_package(SDL_image REQUIRED)

add_definitions(-DUSE_SDL)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

add_subdirectory(LuaBindings)
add_subdirectory(Physics)
add_subdirectory(SDL)

file(GLOB rad_SOURCES *.cpp)
add_executable(rad ${rad_SOURCES})
target_link_libraries(rad LuaBindings Physics GraphicsSDL)
target_link_libraries(rad ${LUA_LIBRARY} ${OPENAL_LIBRARY} ${OGGVORBIS_LIBRARIES} ${OPENGL_LIBRARY} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})

#install(TARGETS rad RUNTIME DESTINATION bin)
