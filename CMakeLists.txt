cmake_minimum_required(VERSION 3.0)
project(calib4prod)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
else ()
    set(CMAKE_CXX_STANDARD 11)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SOURCE_FILES    src/main.cpp
					src/Settings.cpp
					src/CameraCalibration.cpp)

set(HEADER_FILES    include/Settings.hpp
					include/CameraCalibration.hpp)

include_directories(include)

find_package(OpenCV 3.1.0 REQUIRED)
if (OpenCV_FOUND)
    message(STATUS  "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
    message(STATUS  "OpenCV libraries:  ${OpenCV_LIBRARIES}")
else()
    message(SEND_ERROR  "OpenCV was not found.")
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

find_library(JSONCPP_LIB jsoncpp)
target_link_libraries(${PROJECT_NAME} ${JSONCPP_LIB})

message(STATUS "Linking OpenCV libraries: ${OpenCV_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} DESTINATION bin)
