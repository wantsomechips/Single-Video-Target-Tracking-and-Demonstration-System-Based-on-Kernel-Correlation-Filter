cmake_minimum_required(VERSION 3.16)

project(gaohao_qt_pro)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Static Library Output Directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# Shared Library Output Directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# Executable Library Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_PREFIX_PATH /Users/gaohao/Qt/6.3.2/macos/)

set(MOC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/include/CamWidget.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/include/funcs.h 
             ${CMAKE_CURRENT_SOURCE_DIR}/include/viewer.h)


find_package(OpenCV REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia MultimediaWidgets LinguistTools)
qt_standard_project_setup()

include_directories(./kcf ./include ${OpenCV_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS} 
    ${Qt6Multimedia_INCLUDE_DIRS} ${Qt6MultimediaWidgets_INCLUDE_DIRS} 
    ${Qt6LinguistTools_INCLUDE_DIRS} )

add_subdirectory(./kcf)
add_subdirectory(./src)



