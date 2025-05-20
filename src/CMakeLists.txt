
add_library(funcs funcs.cpp)

add_library(viewer viewer.cpp CamWidget.cpp)

add_executable(main main.cpp ${MOC_SRC})

find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

target_link_libraries(main ${OpenCV_LIBS} viewer funcs kcf Qt6::Core 
Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets )



