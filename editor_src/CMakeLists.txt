add_library(editor_lib
    map_creator.cpp
    sdl_libs/Animation.cpp
    sdl_libs/Area.cpp
    sdl_libs/Exception.cpp
    sdl_libs/SdlException.cpp
    sdl_libs/SdlTexture.cpp
    sdl_libs/SdlWindow.cpp
    sdl_libs/Fuente.cpp
    sdl_libs/Music.cpp
    sdl_libs/Sound.cpp
)

target_link_libraries(editor_lib setupscreen_editor)
target_include_directories(editor_lib PRIVATE headers/*)
target_include_directories(editor_lib PRIVATE ../common_src/headers/* setupscreen_editor)




