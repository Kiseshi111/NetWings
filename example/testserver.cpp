#include <iostream>
#include <string>


#include "../include/TcpServer.h"


class EchoServer
{
public:
    EchoServer(EventLoop* loop, const InetAddress& addr, const std::string& name)
        : server_(loop, name, addr)
        , loop_(loop)
    {
        // 注册回调函数
        server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        
        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        // 设置合适的subloop线程数量
        server_.setThreadNum(3);
    }

    void start()
    {
        server_.start();
    }

private:
    void onConnection(const TcpConnectionPtr& conn)
    {
        if (conn->connected())
        {
            std::cout << " Connection Up : " << conn->peerAddress().toIpPort() << std::endl;
            //conn->send("hello world\n");
        }
        else
        {
            std::cout << " Connection Down : " << conn->peerAddress().toIpPort() << std::endl;
        }
    }

    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, TimeStamp time)
    {
        std::string msg = buf->retrieveAllString();
        std::cout << conn->name() << " echo " << msg.size() << " bytes, data received at " << time.toString() << std::endl;
        conn->send(msg);
    }

    EventLoop* loop_;
    TcpServer server_;
};


int main()
{
    std::cout << "pid = " << getpid() << std::endl;

    EventLoop loop;
    InetAddress addr(8002);

    EchoServer server(&loop, addr, "EchoServer");
    server.start();

    loop.loop();

    return 0;
}
