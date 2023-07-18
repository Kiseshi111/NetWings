# 指定 CMake 最低版本要求为 3.10
cmake_minimum_required(VERSION 3.10)

# 设置项目名称为 MyProject
project(MyProject)
# 设置 C++ 标准为 C++11
set(CMAKE_CXX_STANDARD 11)
# 设置编译选项，添加 -fPIC 选项（位置无关代码），用于生成动态库
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# 添加子目录
add_subdirectory(net)
add_subdirectory(include)
add_subdirectory(example)

# 编译为动态库
# 使用 $<TARGET_OBJECTS:net> 引用 net 目录中生成的目标对象
add_library(NetWings SHARED $<TARGET_OBJECTS:net>)
set_target_properties(NetWings PROPERTIES POSITION_INDEPENDENT_CODE ON)
# 设置动态库的包含目录，使得其他代码可以访问 NetWings 动态库的头文件
target_include_directories(NetWings PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

