cmake_minimum_required(VERSION 3.5)

project(SCCT LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For developement under Qt 5 / 6 simply change the line below (ex) -> Qt6 => Qt5
find_package(Qt6 COMPONENTS Widgets REQUIRED Network)

if(ANDROID)
  add_library(SCCT SHARED
    main.cpp
    scct.cpp
    scct.h
    scct.ui
  )
else()
  add_executable(SCCT WIN32
    main.cpp
    scct.cpp
    scct.h
    scct.ui
  )
endif()

target_link_libraries(SCCT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
