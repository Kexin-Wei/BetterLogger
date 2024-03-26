cmake_minimum_required(VERSION 3.16)

project(BetterLogger VERSION 1.0 LANGUAGES CXX)

set(Qt5_DIR "C:/Qt/Qt5.12.10/5.12.10/msvc2015_64/lib/cmake/Qt5")
set(spdlog_DIR ${PROJECT_SOURCE_DIR}/lib/spdlog_x64/lib/cmake/spdlog)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_subdirectory(src)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
    logCpp
    Qt5::Core
)

# copy dlls
# get windeployqt.exe path
GET_TARGET_PROPERTY(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
GET_FILENAME_COMPONENT(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
FIND_PROGRAM(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
    --verbose 0
    --dir "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>" $<TARGET_FILE:${PROJECT_NAME}>
)