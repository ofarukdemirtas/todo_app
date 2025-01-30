cmake_minimum_required(VERSION 3.10)
project(TodoApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt5Widgets_INCLUDE_DIRS}
)

# Source files
set(TODO_LIB_SOURCES src/todo/Todo.cpp)
set(TODO_GUI_SOURCES
    src/todo/TodoGUI.cpp
    src/todo/main_gui.cpp
    include/todo/TodoGUI.h  # Add header file explicitly
)

# Library and executables
add_library(todo_lib STATIC ${TODO_LIB_SOURCES})

add_executable(todo_gui ${TODO_GUI_SOURCES})
target_link_libraries(todo_gui 
    PRIVATE 
    todo_lib 
    Qt5::Widgets
)

add_executable(todo_console src/todo/main_console.cpp)
target_link_libraries(todo_console PRIVATE todo_lib)
