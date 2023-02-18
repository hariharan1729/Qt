cmake_minimum_required(VERSION 3.16)

#project(WeatherApp VERSION 0.1 LANGUAGES CXX)


add_library(BackEnd "")

set(INCLUDE_FILES
    BackEnd.h
    IRequestMessage.h
    IResponse.h
    IParser.h
    Parser.h
)

target_sources(BackEnd
    PRIVATE
        BackEnd.cpp
        Parser.cpp
    PUBLIC
          ${INCLUDE_FILES}


)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Network #[[Core5Compat]])
#find_package(Qt6 REQUIRED COMPONENTS )

# This call requires CMake 3.13 or later, see next section

target_link_libraries(BackEnd
    PRIVATE
    Qt6::Quick
    Qt::Core
    Qt::Network
    common
#    Qt6::Core5Compat #QRegExp
)

#target_compile_definitions(myLib PUBLIC USE_BARRY)

target_include_directories(BackEnd PUBLIC ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS BackEnd DESTINATION BackEnd-bin)
install(FILES ${INCLUDE_FILES} DESTINATION BackEnd-include)
