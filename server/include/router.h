#ifndef BOOST_ASIO_SERVER_ROUTER_H
#define BOOST_ASIO_SERVER_ROUTER_H


#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


namespace server3 {
    template<typename Handler>
    class Router {
    public:
        void addHandler(std::string method, Handler handler);

        http::response<http::string_body> processRoute(const std::string &method, const http::request<http::string_body> &request);

    private:
        std::map<std::string, Handler> m_Handlers;
    };
}


#endif //BOOST_ASIO_SERVER_ROUTER_H
