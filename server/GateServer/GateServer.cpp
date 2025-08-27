#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"
#include "ConfigMgr.h"
#include "const.h"
#include "redisMgr.h"

int main()
{
    auto& gCfgMgr = ConfigMgr::Inst();
    std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
    unsigned short gate_port = atoi(gate_port_str.c_str());
    try {
        unsigned short port = static_cast<unsigned short>(8080);
        net::io_context ioc{ 1 };//1代表分配给ioc一个线程
        //signals作用：异步等待系统信号，收到SIGINT（中断）或SIGTERM（终止）时会触发回调函数
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
            if (error) {
                return;
            }
            ioc.stop();
            });
        std::make_shared<CServer>(ioc, port)->Start();
        std::cout << "GateServer listen on port : " << port << std::endl;
        ioc.run();
    }
    catch(std::exception const& e){
        std::cerr << "error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}