cmake_minimum_required(VERSION 3.27)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
project(RemoteControl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LLVM_ENABLE_LIBCXX ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CXX_SCAN_FOR_MODULES ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
add_library(CXXModules)
target_sources(CXXModules
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Tmp.cppm
)
add_executable(RemoteControl main.cpp

)
target_link_libraries(RemoteControl
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CXXModules
)












