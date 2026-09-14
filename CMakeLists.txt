cmake_minimum_required(VERSION 3.20)

project(FastTrack2026_TankGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL3 package location
set(SDL3_DIR
    "${CMAKE_SOURCE_DIR}/third_party/SDL3/cmake")

find_package(SDL3 REQUIRED)

add_executable(
    FastTrack2026_TankGame
    src/main.cpp
)

target_link_libraries(
    FastTrack2026_TankGame
    PRIVATE
    SDL3::SDL3
)

# Copy SDL3.dll next to executable after build
add_custom_command(
    TARGET FastTrack2026_TankGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/third_party/SDL3/x86_64-w64-mingw32/bin/SDL3.dll"
        $<TARGET_FILE_DIR:FastTrack2026_TankGame>
)