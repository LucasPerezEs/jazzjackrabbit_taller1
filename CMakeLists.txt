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
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
# add_executable(example example.cpp)
# target_link_libraries(example gtest_main)
# add_test(NAME example_test COMMAND example)

enable_testing()

add_subdirectory(client_src)
add_subdirectory(server_src)
add_subdirectory(editor_src)
add_subdirectory(client_src/setupscreen)
add_subdirectory(editor_src/setupscreen_editor)

add_executable (server
  server_src/main.cpp
)

find_package(Qt5Widgets REQUIRED)

# find_package(GTest REQUIRED)

add_executable (client
  client_src/main.cpp
)

add_executable (editor
  editor_src/main.cpp
)

add_executable (prueba
  tests_src/tests.cpp
)

target_link_libraries(client client_lib Qt5::Widgets setupscreen SDL2 SDL2_image pthread SDL2_ttf -lSDL2_mixer)
target_link_libraries(editor editor_lib Qt5::Widgets setupscreen_editor SDL2 SDL2_image pthread SDL2_ttf -lSDL2_mixer)
target_link_libraries(server server_lib pthread yaml-cpp)
target_link_libraries(prueba gtest_main gmock_main server_lib yaml-cpp)

include(GoogleTest)
gtest_discover_tests(prueba)
