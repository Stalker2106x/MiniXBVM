cmake_minimum_required(VERSION 2.6)

project (Mini8BVM)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#CORE FILES
file(GLOB
     source_files
     ${CMAKE_SOURCE_DIR}/src/*.cpp
     ${CMAKE_SOURCE_DIR}/src/Computer/*.cpp
     ${CMAKE_SOURCE_DIR}/src/Editor/*.cpp
     ${CMAKE_SOURCE_DIR}/src/Electronic/*.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/imgui/*.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/imgui/examples/imgui_impl_glut.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/imgui/examples/imgui_impl_opengl2.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/imgui/examples/imgui_impl_opengl2.cpp
     ${CMAKE_SOURCE_DIR}/thirdparty/ImGuiColorTextEdit/TextEditor.cpp
)

set(OPENGL_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/thirdparty/FreeGLUT/freeglut/freeglut/build/lib)
set(GLUT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/FreeGLUT/freeglut/freeglut/include)

# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
if(NOT GLUT_FOUND)
     message(ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
     message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

include_directories(${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/thirdparty/
                    ${CMAKE_SOURCE_DIR}/thirdparty/imgui
                    ${CMAKE_SOURCE_DIR}/thirdparty/FreeGLUT/freeglut/freeglut/include
                    )


#Global Parameter
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Build sequence
add_executable(Mini8BVM ${source_files})

target_link_libraries(Mini8BVM ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})