cmake_minimum_required(VERSION 2.6)

project (Mini8BVM)

#CORE FILES
file(GLOB
     source_files
     ${CMAKE_SOURCE_DIR}/src/*.cpp
     ${CMAKE_SOURCE_DIR}/src/Computer/*.cpp
     ${CMAKE_SOURCE_DIR}/src/Editor/*.cpp
     ${CMAKE_SOURCE_DIR}/src/Electronic/*.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/imgui/*.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/ImGuiColorTextEdit/TextEditor.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/imgui-sfml/*.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/thirdparty/
                    ${CMAKE_SOURCE_DIR}/thirdparty/imgui
                    ${CMAKE_SOURCE_DIR}/thirdparty/imgui-sfml/
                    ${CMAKE_SOURCE_DIR}/thirdparty/SFML/include
                    )

#Global Parameter
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Build sequence
add_executable(Mini8BVM ${source_files})


# SFML
set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/thirdparty/SFML/build)
find_package(SFML 2.5 COMPONENTS audio graphics window system)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
     message(FATAL_ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

target_link_libraries(Mini8BVM PRIVATE ${OPENGL_LIBRARIES} sfml-graphics sfml-window sfml-system sfml-audio)