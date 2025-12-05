file(GLOB SOURCES "src/*.cpp")

if(NOT TARGET Dec3)
    add_executable(Dec3 ${SOURCES})
endif()