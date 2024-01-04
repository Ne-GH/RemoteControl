cmake_minimum_required(VERSION 3.5)

project(RemoteControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows-specific code
endif ()

include_directories(.)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
set(src 
        MainWindow.ui
        MainWindow.h
        MainWindow.cpp

        Event.h
        Event.cpp

        Client/Control/Control.h
        Client/Control/Control.cpp

        Client/Controlled/Controlled.h
        Client/Controlled/Controlled.cpp
)
add_executable(control control_main.cpp
    ${src}
)
add_executable(controlled controlled_main.cpp
    ${src}
)
target_link_libraries(control
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
target_link_libraries(controlled
        Qt::Core
        Qt::Gui
        Qt::Widgets
)