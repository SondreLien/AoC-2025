cmake_minimum_required(VERSION 3.20)

project(AoC-2025 LANGUAGES CXX)

# Global settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add boost
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/ThirdParty/boost)

add_subdirectory(Dec1)
add_subdirectory(Dec2)
add_subdirectory(Dec3)
add_subdirectory(Dec4)
add_subdirectory(Dec5)

target_include_directories(Dec3 
    PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/boost/libs/multiprecision/include
    PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/boost/libs/config/include)