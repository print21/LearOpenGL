# learn opengl

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(LearnOpenGL)

# add our macro directory to cmake search path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Qt5 COMPONENTS Core)

if(Qt5Core_FOUND)
    set(QT5_FOUND TRUE)
    set(QT5_BIN_DIR ${_qt5_install_prefix}/../../bin)

    # Enable automoc, autouic and auto rcc
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
else(Qt5Core_FOUND)
    message (FATAL_ERROR "Qt5 not found!")
endif(Qt5Core_FOUND)

# check for OpenGL, GLEW as our required dependencies
find_package (OpenGL)

if (NOT OPENGL_FOUND)
  message (FATAL_ERROR "OpengGL not found!")
endif ()

find_package(glew)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)
