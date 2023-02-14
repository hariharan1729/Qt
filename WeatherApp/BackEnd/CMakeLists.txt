cmake_minimum_required(VERSION 3.16)

#project(WeatherApp VERSION 0.1 LANGUAGES CXX)


target_sources(appWeatherApp
    PRIVATE
        BackEnd.cpp
    PUBLIC
        BackEnd.h
        Utils.h
        IMessage.h
        IRequestMessage.h
        IResponse.h

)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Network #[[Core5Compat]])
#find_package(Qt6 REQUIRED COMPONENTS )

# This call requires CMake 3.13 or later, see next section

target_link_libraries(appWeatherApp
    PRIVATE
    Qt6::Quick
    Qt::Core
    Qt::Network
#    Qt6::Core5Compat #QRegExp
)

#target_compile_definitions(myLib PUBLIC USE_BARRY)

target_include_directories(appWeatherApp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
