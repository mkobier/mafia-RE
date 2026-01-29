cmake_minimum_required(VERSION 3.15)

project(MafiaRE VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/dllmain.cpp
    
    src/Core/Memory.h
    src/Core/Memory.cpp
    
    src/Game/Math/Vector3.h
    src/Game/Math/Vector3.cpp
)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(WIN32_LEAN_AND_MEAN)
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})


set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".asi"
    PREFIX "" 
)

target_link_libraries(${PROJECT_NAME} PRIVATE kernel32)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Plugin: $<TARGET_FILE:${PROJECT_NAME}>"
	)