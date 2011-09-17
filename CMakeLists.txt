cmake_minimum_required(VERSION 2.6)
project(cppcollada)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

# Note this is the 'bad' way of doing this, but the recommended alternative is to keep a list of *all* source files =/
file(GLOB_RECURSE cppcollada_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")

# These files require qt's moc preprocessor
set(qt_CPP 
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditCollada.cpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/TreeModel.cpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditScene.cpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditGeneric.cpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditColladas.cpp"
   #"${CMAKE_SOURCE_DIR}/src/QTGui/QTColladaObjectTreeItem.cpp"
   "${CMAKE_SOURCE_DIR}/src/Viewport/ViewWindowQT.cpp"
)

set(qt_HPP 
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditCollada.hpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/TreeModel.hpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditScene.hpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditGeneric.hpp"
   "${CMAKE_SOURCE_DIR}/src/QTGui/QTEditColladas.hpp"
   #"${CMAKE_SOURCE_DIR}/src/QTGui/QTColladaObjectTreeItem.hpp"
   "${CMAKE_SOURCE_DIR}/src/Viewport/ViewWindowQT.hpp"
)

# TODO: Fix me, Unprocessed QT source files should be reoved in favour of the MOC generated ones
list(REMOVE_ITEM cppcollada_SRC $qt_CPP)

# Basic CMAKE supported libs
find_package(OpenGL REQUIRED)
find_package(DevIL REQUIRED)

# Libs using 3rd party cmake modules
find_package(GLEW REQUIRED)
find_package(XercesC REQUIRED)
find_package(Noise REQUIRED)

# SDL
find_package(SDL)
include_directories(${SDL_INCLUDE_DIR})

# Boost
find_package(Boost COMPONENTS thread system REQUIRED)
add_definitions(-D_BOOSTPTR)

# QT
find_package(Qt4 4.6 COMPONENTS QtCore QtGui QtOpenGL QtWebKit REQUIRED)
include(${QT_USE_FILE})
QT4_WRAP_CPP(cppcollada_SRC ${qt_HPP})

# Final target
add_executable(colladatest ${cppcollada_SRC})
target_link_libraries(colladatest ${QT_LIBRARIES} ${Boost_LIBRARIES} ${SDL_LIBRARY} ${XERCESC_LIBRARIES} ${IL_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${NOISE_LIBRARY})

