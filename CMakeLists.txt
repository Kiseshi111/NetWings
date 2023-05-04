cmake_minimum_required(VERSION 3.10)

project(MyProject)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# 添加子目录
add_subdirectory(net)
add_subdirectory(include)
add_subdirectory(example)

# 编译为动态库
add_library(NetWings SHARED $<TARGET_OBJECTS:net>)
set_target_properties(NetWings PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(NetWings PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

