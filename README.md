# NetWings
 仿muduo网络库
 本项目是参考 muduo 实现的基于 Reactor 模型的多线程网络库。使用 C++ 11 编写去除 muduo 对 boost 的依赖。

 它采用非阻塞IO模型，基于事件驱动和回调，是一个oneloop per thread + threadpool框架。

 大量使用了智能指针，bind，function等技术，对socket和epoll进行了封装，使其便于使用。
