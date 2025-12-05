file(GLOB SOURCES "src/*.cpp")

if(NOT TARGET Dec5)
    add_executable(Dec5 ${SOURCES})
endif()