cmake_minimum_required(VERSION 3.10)

project(Assignment1) # project name

aux_source_directory(./src SRCS) # src dir

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin>) # fixed dir
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} -O3") # flag
endif()

add_executable(${PROJECT_NAME} ${SRCS}) # generate