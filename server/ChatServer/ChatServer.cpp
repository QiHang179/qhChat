#include "LogicSystem.h"
#include <csignal>
#include <thread>
#include <mutex>
#include "AsioIOServicePool.h"
#include "CServer.h"
#include "ConfigMgr.h" 
bool bstop = false;
std::condition_variable cond_quit;
std::mutex mutex_quit;

#include <iostream>
#include <boost/asio.hpp>
#include "ConfigMgr.h"
#include "AsioIOServicePool.h"
#include "CServer.h"

int main()
{
    try {
        // 获取配置管理器实例
        auto& cfg = ConfigMgr::Inst();

        // 获取Asio IO服务池实例
        auto pool = AsioIOServicePool::GetInstance();

        // 创建一个io_context对象
        boost::asio::io_context io_context;

        // 创建一个信号集，监听SIGINT和SIGTERM信号
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

        // 设置异步等待信号的回调函数
        signals.async_wait([&io_context, &pool](auto, auto) {
            io_context.stop();  // 停止io_context
            pool->Stop();       // 停止Asio IO服务池
            });

        // 从配置中获取端口号
        auto port_str = cfg["SelfServer"]["Port"];

        // 创建服务器实例并绑定到指定端口
        CServer s(io_context, atoi(port_str.c_str()));

        // 运行io_context，开始处理事件循环
        io_context.run();
    }
    catch (std::exception& e) {
        // 捕获并打印异常信息
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}