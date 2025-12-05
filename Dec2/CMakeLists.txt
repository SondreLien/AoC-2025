file(GLOB SOURCES "src/*.cpp")

if(NOT TARGET Dec2)
    add_executable(Dec2 ${SOURCES})
endif()