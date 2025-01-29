cmake_minimum_required(VERSION 3.30.0)
project(ViCE)
add_executable(ViCE
	# source files		# header files
	program.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}})
target_link_libraries(ViCE ${OpenCV_LIBS})
