cmake_minimum_required(VERSION 3.5)

project(RemoteControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
       add_definitions(/utf-8)
endif ()

include_directories(.)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(RemoteControl
		main.cpp

		MainWindow.ui
		MainWindow.h
		MainWindow.cpp

		Event.h
		Event.cpp
)

target_link_libraries(RemoteControl
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)
