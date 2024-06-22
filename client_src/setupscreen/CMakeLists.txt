project(setupscreen)

find_package(Qt5Widgets REQUIRED)

set(HEADER_FILES
        ConnectMenu.h
        SetupScreen.h
        MultiplayerMenu.h
        CreateGame.h
        JoinGame.h
        GameList.h
        ClientName.h
)

set(SOURCE_FILES
        ConnectMenu.cpp
        SetupScreen.cpp
        MultiplayerMenu.cpp
        CreateGame.cpp
        JoinGame.cpp
        GameList.cpp
        ClientName.cpp
)


qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})

add_library(setupscreen STATIC ${SOURCE_FILES} ${MOC_FILES})

target_link_libraries(setupscreen Qt5::Widgets)

target_include_directories(setupscreen PUBLIC ..)