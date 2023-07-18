# 使用 add_library 命令创建一个对象库（Object Library）名为 net
# OBJECT 表示这个库是一个对象库，不会生成可执行文件或共享库，而是在链接时被其他目标使用
add_library(net OBJECT
    Acceptor.cpp
    Buffer.cpp
    Channel.cpp
    CurrentThread.cpp
    DefaultPoller.cpp
    EpollPoller.cpp
    EventLoop.cpp
    EventLoopThread.cpp
    EventLoopThreadPool.cpp
    InetAddress.cpp
    Poller.cpp
    Socket.cpp
    TcpConnection.cpp
    TcpServer.cpp
    Thread.cpp
    TimeStamp.cpp
)
