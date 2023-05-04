# 添加 testserver.cpp 到 example 目标中
add_executable(testserver testserver.cpp)

# 链接 NetWings 库
target_link_libraries(testserver PRIVATE NetWings)

