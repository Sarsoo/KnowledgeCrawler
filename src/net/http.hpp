#pragma once

#include <unordered_map>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>
#include <iostream>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

namespace kc {
    http::response<http::dynamic_body> request(http::verb method, const std::string &host, std::string target, std::string body);
    http::response<http::dynamic_body> request(http::verb method, const std::string &host, std::string target, std::string body, std::unique_ptr<std::unordered_map<std::string, std::string>> headers);
    http::response<http::dynamic_body> request(http::verb method, const std::string &host, std::string target, int port, std::string body, std::unique_ptr<std::unordered_map<std::string, std::string>> headers);
}

