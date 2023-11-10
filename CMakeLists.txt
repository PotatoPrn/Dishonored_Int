cmake_minimum_required(VERSION 3.26)
project(IntTemplate)

set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_OUTPUT_PATH "../")
include_directories(include)

set(UTILS
        src/Utils/GraphicsUtil.cpp
        src/Utils/UiUtil.cpp
        src/Utils/MemUtil.cpp
)

add_library(${PROJECT_NAME} SHARED main.cpp
        ${UTILS}

        src/HackList.cpp


)