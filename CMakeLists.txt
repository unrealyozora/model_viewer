cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)

FetchContent_Declare(
  glm 
  GIT_REPOSITORY https://github.com/g-truc/glm.git 
)

FetchContent_MakeAvailable(glm)

project(model_viewer VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64")
if (MSVC)
  add_compile_options(/Zc:__cplusplus /permissive-)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)

file(GLOB_RECURSE SOURCES 
  "src/*.cpp"
  "third-party/stb_image/*.cpp"
)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third-party/stb_image)

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)


set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)

add_custom_target(copy_compile_commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json
  ${CMAKE_SOURCE_DIR}/compile_commands.json
  DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)

