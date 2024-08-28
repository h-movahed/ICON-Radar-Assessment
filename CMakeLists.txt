cmake_minimum_required(VERSION 3.0)
project(Icon_Radar)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

# find OpenCV
find_package(OpenCV REQUIRED)

# Add your executable
add_executable(Icon_Radar main.cpp)

# Include openCV headers
target_include_directories(Icon_Radar PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link OpenCV libraries
target_link_libraries(Icon_Radar ${OpenCV_LIBS} )

set_property(TARGET Icon_Radar PROPERTY CXX_STANDARD 17)