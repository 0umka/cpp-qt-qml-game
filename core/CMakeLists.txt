cmake_minimum_required(VERSION 3.16)
project(myGameCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_definitions(-DCMAKE)

find_package(Qt6 REQUIRED COMPONENTS Core)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB FORMS *.ui)

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RSS}
    ${QM_FILES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Core
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)
