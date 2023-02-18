cmake_minimum_required(VERSION 3.16)

#project(WeatherApp VERSION 0.1 LANGUAGES CXX)


target_sources(appWeatherApp
    PRIVATE
        main.cpp
        RequestMsgBuilder.cpp
        RequestMsgBuilder.h
        Renderer.cpp
        Renderer.h
        ReqMsg.cpp
        ReqMsg.h
        Response.h
        Response.cpp
    PUBLIC
        WeatherChartItem.cpp
        WeatherChartItem.h
)

target_include_directories(appWeatherApp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
