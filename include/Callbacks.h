#pragma once

#include <functional>
#include <memory>

class Buffer;
class TimeStamp;
class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>;
using HighWaterMarkCallback = std::function<void(const TcpConnectionPtr&, size_t)>;

using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*, TimeStamp)>;
