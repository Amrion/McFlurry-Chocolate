#ifndef BOOST_ASIO_SERVER_ASYNC_HTTP_SERVER_H
#define BOOST_ASIO_SERVER_ASYNC_HTTP_SERVER_H

#include <boost/asio.hpp>
#include "router.h"


namespace server3 {

        class server : public std::enable_shared_from_this<server>
        {
        public:
            explicit server(const std::string& address, const std::string& port,
                            std::size_t thread_pool_size);

            /// Run the server's io_context loop.
            void run();

        private:
            /// Initiate an asynchronous accept operation.
            void start_accept();

            /// Handle completion of an asynchronous accept operation.
            void handle_accept(beast::error_code e, tcp::socket socket);

            /// Handle a request to stop the server.
            void handle_stop();

        private:

            /// The handler for all incoming requests.
            Router<http::response<http::string_body>(*)(const  http::request<http::string_body> &request)> request_router;

            net::io_context io_context_;
            tcp::acceptor acceptor_;

            /// The number of threads that will call io_context::run().
            std::size_t thread_pool_size_;
        };

} // namespace server3


#endif //BOOST_ASIO_SERVER_ASYNC_HTTP_SERVER_H
