cmake_minimum_required(VERSION 3.28)
project(MarkovChainGenerator)

set(CMAKE_CXX_STANDARD 17)
# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt6Widgets REQUIRED)

add_executable(MarkovChainGenerator
        main.cpp
        MarkovChain.cpp
        MainWindow.cpp
)

# Link the executable to the Qt libraries
target_link_libraries(MarkovChainGenerator Qt6::Widgets)
