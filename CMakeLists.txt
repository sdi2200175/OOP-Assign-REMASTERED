cmake_minimum_required(VERSION 3.2)
project(UniManagement)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g)

add_executable(UniManagement src/main.cpp
        src/secretary/person.cpp
        src/secretary/secretary.cpp
        src/interface/interface.cpp
        src/interface/student.cpp
        src/interface/professor.cpp
        src/secretary/course.cpp
        inc/course.h
        src/interface/course.cpp
)

target_include_directories(UniManagement PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_custom_command(TARGET UniManagement POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --green
                    "! SUCCESS: University Management System has been compiled successfully. ")
