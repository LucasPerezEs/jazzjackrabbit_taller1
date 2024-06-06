cmake_minimum_required(VERSION 2.8.12)

project(jazzjackrabbit
    DESCRIPTION "TP Final para la materia Taller de Programacion I - 1C2024"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L -I/usr/include/SDL2")

if(APPLE)
  message("Estoy en OSX")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf")
endif()


add_subdirectory(client_src)
add_subdirectory(server_src)
add_subdirectory(client_src/setupscreen)




add_executable (server
  server_src/main.cpp
)

find_package(Qt5Widgets REQUIRED)

add_executable (client
  client_src/main.cpp

)


target_link_libraries(client client_lib Qt5::Widgets setupscreen SDL2 SDL2_image pthread SDL2_ttf)

target_link_libraries(server server_lib pthread)