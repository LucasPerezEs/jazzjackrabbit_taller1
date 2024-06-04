project(setupscreen)

set(HEADER_FILES
        ConnectMenu.h
        SetupScreen.h
        MultiplayerMenu.h
)

set(SOURCE_FILES
        ConnectMenu.cpp
        SetupScreen.cpp
        MultiplayerMenu.cpp
        CreateGame.cpp
        CreateGame.h
        JoinGame.cpp
        JoinGame.h
        GameList.cpp
        GameList.h
)

add_library(setupscreen STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(Qt5Widgets REQUIRED)


target_link_libraries(setupscreen Qt5::Widgets )

target_include_directories(setupscreen PUBLIC ..)