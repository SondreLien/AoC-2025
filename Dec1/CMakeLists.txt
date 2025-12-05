file(GLOB SOURCES "src/*.cpp")

if(NOT TARGET Dec1)
    add_executable(Dec1 ${SOURCES})
endif()