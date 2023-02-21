cmake_minimum_required(VERSION 3.16)

#project(WeatherApp VERSION 0.1 LANGUAGES CXX)


add_library(common "")

set(INCLUDE_FILES
    Utils.h
    Message.h
    IMessage.h
    Tracing.h
)

target_sources(common
    PRIVATE
        Message.cpp
    PUBLIC
        ${INCLUDE_FILES}
)

target_link_libraries(common
    PUBLIC
        Qt::Core
        Qt6::Quick
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS common DESTINATION common-bin)
install(FILES ${INCLUDE_FILES} DESTINATION common-include)
