cmake_minimum_required(VERSION 2.8)

project(OpenVR_Device_Viewer)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp include/*.h)

file(GLOB IMGUI_SOURCES 3rdparty/imgui/*.cpp)
file(GLOB IMGUI_HEADERS 3rdparty/imgui/*.h 3rdparty/imgui/*.hpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenVR_Device_Viewer ${SOURCES} ${HEADERS})
target_include_directories(OpenVR_Device_Viewer PUBLIC include/)

# OpenVR headers and libs
target_include_directories(OpenVR_Device_Viewer PUBLIC 3rdparty/openvr/headers)
target_link_libraries(OpenVR_Device_Viewer ${CMAKE_SOURCE_DIR}/3rdparty/openvr/lib/win64/openvr_api.lib)
file(COPY ${CMAKE_SOURCE_DIR}/3rdparty/openvr/bin/win64/openvr_api.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug)

#Imgui headers and sources
target_include_directories(OpenVR_Device_Viewer PUBLIC 3rdparty/imgui)
add_library(imgui ${IMGUI_SOURCES} ${IMGUI_HEADERS})