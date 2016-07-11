cmake_minimum_required (VERSION 3.1)
project (pair)

include_directories(bprinter/include)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message(STATUS ">>> Linux")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

endif()

set (CMAKE_CXX_STANDARD 11)

add_executable(prog main.cpp bprinter/src/table_printer.cpp)