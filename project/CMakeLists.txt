cmake_minimum_required(VERSION 3.21)
project(UltrasonicExperiment VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automoc, autouic, and autorcc for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find required Qt packages
find_package(Qt6 COMPONENTS Core Gui Widgets Charts REQUIRED)

# MATLAB includes and libraries
# Set MATLAB Runtime include directory
set(MATLAB_RUNTIME_INCLUDE_DIR "C:/Program Files/MATLAB/MATLAB Runtime/R2023b/extern/include")
set(MATLAB_RUNTIME_LIB_DIR "C:/Program Files/MATLAB/MATLAB Runtime/R2023b/extern/lib/win64/mingw64")
set(MATLAB_LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/funcs/UsbConnect")

include_directories(${MATLAB_RUNTIME_INCLUDE_DIR})
link_directories(${MATLAB_LIBS_DIR} ${MATLAB_RUNTIME_LIB_DIR})

# Add the executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/MainWindow.cpp
    src/ParaGroupBox.cpp
    include/MainWindow.h
    include/ParaGroupBox.h
    include/UsbConnect.h)

# Include directories for your project
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Linking the Qt libraries and the MATLAB library
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
        UsbConnect
        mclmcrrt)  # Assuming the library name is UsbConnect

# Make sure to copy the UsbConnect.dll to your project's binary directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${MATLAB_LIBS_DIR}/UsbConnect.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
