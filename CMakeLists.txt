cmake_minimum_required(VERSION 3.20)
project(LightGameEngine)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

## Find dependencies
find_path(STB_INCLUDE_DIRS "stb_image.h")
find_path(STB_INCLUDE_DIRS "linalg.h")
find_package(glfw3 REQUIRED CONFIG)
find_package(Vulkan REQUIRED)
find_package(imgui REQUIRED CONFIG)
find_package(EnTT REQUIRED CONFIG)

## Create main executable
set(INCLUDE_DIR "include")
set(SRC_DIR "src")
set(TST_DIR "test")

add_executable(lightgameengine
    ${SRC_DIR}/main.cpp
)

target_include_directories(
    lightgameengine 
    PRIVATE
        ${INCLUDE_DIR}
        ${STB_INCLUDE_DIRS}
        ${LINALG_INCLUDE_DIRS}
)

target_link_libraries(
    lightgameengine
    PRIVATE
        glfw
        Vulkan::Vulkan
        imgui::imgui
        EnTT::EnTT
)

## Testing
add_executable(lightgameengine-test 
    ${TST_DIR}/alltests.cpp
)
target_include_directories(
    lightgameengine-test 
    PRIVATE 
        ${TST_DIR}
        ${INCLUDE_DIR}
)
if (BUILD_TESTING)
    add_test(NAME lightgameengine-test
            COMMAND lightgameengine-test)
endif()

# https://stackoverflow.com/questions/68014365/how-can-i-link-glfw-and-dear-imgui-in-cmake