project(setupscreen_editor)

find_package(Qt5Widgets REQUIRED)

set(HEADER_FILES
        SetupScreen.h
        AppMenu.h
        CreateMap.h
        ModifyMap.h

)

set(SOURCE_FILES
        SetupScreen.cpp
        AppMenu.cpp
        CreateMap.cpp
        ModifyMap.cpp
)


qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})

add_library(setupscreen_editor STATIC ${SOURCE_FILES} ${MOC_FILES})

target_link_libraries(setupscreen_editor Qt5::Widgets)

target_include_directories(setupscreen_editor PUBLIC ..)