file(GLOB SOURCES "src/*.cpp")

if(NOT TARGET Dec6)
    add_executable(Dec6 ${SOURCES})
endif()