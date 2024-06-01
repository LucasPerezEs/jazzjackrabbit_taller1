project(setupscreen)

set(HEADER_FILES
        MenuDialog.h
)

set(SOURCE_FILES
        MenuDialog.cpp
)

add_library(setupscreen STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(Qt5Widgets REQUIRED)


target_link_libraries(setupscreen Qt5::Widgets )

target_include_directories(setupscreen PUBLIC ..)