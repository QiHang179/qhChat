#pragma once
#include "const.h"

class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(boost::asio::io_context& ioc);
	void Start();
	tcp::socket& GetSocket() {
		return _socket;
	}
private:
	void CheckDeadline();              //检查并处理链接超时
	void WriteResponse();              //发送http响应
	void HandleReq();                  //处理http请求
	void PreParseGetParam();           //解析http请求
	tcp::socket _socket;
	beast::flat_buffer _buffer{ 1892 };
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;
	net::steady_timer deadline_{ _socket.get_executor(),std::chrono::seconds(60) };
	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

