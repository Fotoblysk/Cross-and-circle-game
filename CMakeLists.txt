cmake_minimum_required(VERSION 3.5)
project(Cross_and_circle_game)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
set(SOURCE_FILES main.cpp src/AiPlayer.cpp include/AiPlayer.h src/Board.cpp include/Board.h src/Engine.cpp include/Engine.h src/Game.cpp include/Game.h src/HumanPlayer.cpp include/HumanPlayer.h src/NetworkEngine.cpp include/NetworkEngine.h src/Player.cpp include/Player.h src/Square.cpp include/Square.h include/BoardTree.cpp include/BoardTree.h)
add_executable(Cross_and_circle_game ${SOURCE_FILES})
include_directories(include)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(Threads REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Cross_and_circle_game ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif ()
if (SFML_FOUND AND ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SFML_BIN "${SFML_INCLUDE_DIR}/../bin")
    set(BIN_OUTPUT "${CMAKE_BINARY_DIR}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${SFML_BIN} ${BIN_OUTPUT})
endif ()
set(ResourceTexturesDir "${CMAKE_SOURCE_DIR}/textures")
set(ResourceFontsDir "${CMAKE_SOURCE_DIR}/fonts")

set(ResourceTexturesOutDir "${CMAKE_BINARY_DIR}/textures")
set(ResourceFontsOutDir "${CMAKE_BINARY_DIR}/fonts")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ResourceFontsDir} ${ResourceFontsOutDir}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ResourceTexturesDir} ${ResourceTexturesOutDir})
