file(GLOB SOURCES "src/*.cpp")

if(NOT TARGET Dec4)
    add_executable(Dec4 ${SOURCES})
endif()