cmake_minimum_required(VERSION 3.20)

find_package(spdlog REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS
    Core
)

SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

set(LIB_SRCS
    Logger.cpp
    AWorker.cpp
)

set(LIB_HDRS
    Logger.h
    BLogger.h
    AWorker.h
)

set(OTHER_LIBS
    Qt5::Core
    spdlog::spdlog
)

set(LIB_NAME logCpp)

add_library(${LIB_NAME}
    ${LIB_SRCS}
    ${LIB_HDRS}
)

target_link_libraries(${LIB_NAME}
    ${OTHER_LIBS}
)