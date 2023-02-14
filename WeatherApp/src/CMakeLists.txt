cmake_minimum_required(VERSION 3.16)

#project(WeatherApp VERSION 0.1 LANGUAGES CXX)


target_sources(appWeatherApp
    PRIVATE
        main.cpp
        RequestMsgBuilder.cpp
        RequestMsgBuilder.h
        BackEndMgr.cpp
        BackEndMgr.h
        ReqMsg.cpp
        ReqMsg.h
        Response.h
        Response.cpp
        Message.cpp
        Message.h
    PUBLIC
        WeatherChartItem.cpp
        WeatherChartItem.h
#    PUBLIC
#        foo.h  # poor PUBLIC example, see discussion below for why
)

target_include_directories(appWeatherApp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
