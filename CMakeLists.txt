cmake_minimum_required(VERSION 3.26)
project(Dishonored_Int)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH "../")
include_directories(include)

include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")



set(UTILS
        src/Utils/GraphicsUtil.cpp
        src/Utils/UiUtil.cpp
        src/Utils/MemUtil.cpp
        src/Utils/GameUtils.cpp
        src/Utils/Directx9Utils.cpp
        src/Utils/Draw.cpp
)

add_library(${PROJECT_NAME} SHARED main.cpp
        ${UTILS}

        src/MainHackThread.cpp
        src/HackList.cpp
)