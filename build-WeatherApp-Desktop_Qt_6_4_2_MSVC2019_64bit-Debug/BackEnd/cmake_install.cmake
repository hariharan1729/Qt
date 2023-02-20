# Install script for directory: F:/Qt/Git/Qt/WeatherApp/BackEnd

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/WeatherApp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BackEnd-bin" TYPE STATIC_LIBRARY FILES "F:/Qt/Git/Qt/build-WeatherApp-Desktop_Qt_6_4_2_MSVC2019_64bit-Debug/BackEnd/BackEnd.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BackEnd-include" TYPE FILE FILES
    "F:/Qt/Git/Qt/WeatherApp/BackEnd/BackEnd.h"
    "F:/Qt/Git/Qt/WeatherApp/BackEnd/IRequestMessage.h"
    "F:/Qt/Git/Qt/WeatherApp/BackEnd/IResponse.h"
    "F:/Qt/Git/Qt/WeatherApp/BackEnd/IParser.h"
    "F:/Qt/Git/Qt/WeatherApp/BackEnd/Parser.h"
    )
endif()

