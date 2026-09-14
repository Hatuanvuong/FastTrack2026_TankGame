cmake_minimum_required(VERSION 3.20)

project(FastTrack2026_TankGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL3 package location
set(SDL3_DIR
    "${CMAKE_SOURCE_DIR}/third_party/SDL3/cmake")

# SDL3_image package location
set(SDL3_image_DIR
    "${CMAKE_SOURCE_DIR}/third_party/SDL3_image/cmake")

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(
    FastTrack2026_TankGame

    src/main.cpp

    src/core/Map.cpp

    src/game/Game.cpp

    src/render/ResourceManager.cpp
    
    src/render/Renderer.cpp
)

target_link_libraries(
    FastTrack2026_TankGame
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)

# Copy assets directory after build
add_custom_command(
    TARGET FastTrack2026_TankGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:FastTrack2026_TankGame>/assets"
)

# Copy SDL3.dll
add_custom_command(
    TARGET FastTrack2026_TankGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/third_party/SDL3/x86_64-w64-mingw32/bin/SDL3.dll"
        $<TARGET_FILE_DIR:FastTrack2026_TankGame>
)

# Copy SDL3_image.dll
add_custom_command(
    TARGET FastTrack2026_TankGame
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/third_party/SDL3_image/x86_64-w64-mingw32/bin/SDL3_image.dll"
        $<TARGET_FILE_DIR:FastTrack2026_TankGame>
)