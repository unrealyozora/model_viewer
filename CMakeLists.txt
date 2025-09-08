cmake_minimum_required(VERSION 3.16)

project(model_viewer VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64")
if (MSVC)
  add_compile_options(/Zc:__cplusplus /permissive-)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)

qt_standard_project_setup()

qt_add_executable(model_viewer src/main.cpp src/MainWindow.cpp src/GlWidget.cpp)

target_link_libraries(model_viewer PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)

