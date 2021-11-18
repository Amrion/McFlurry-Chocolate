#ifndef BOOST_ASIO_SERVER_CONNECTION_H
#define BOOST_ASIO_SERVER_CONNECTION_H

#include "router.h"

namespace server3 {

        class Connection: public std::enable_shared_from_this<Connection>
        {
        public:
            /// Construct a connection with the given io_context.
            explicit Connection(tcp::socket&& socket);


            /// Start the first asynchronous operation for the connection.
            void start();

        private:
            void do_read();

            /// Handle completion of a read operation.
            void handle_read(beast::error_code e,
                             std::size_t bytes_transferred);

            /// Handle completion of a write operation.
            void handle_write(bool close,
                              beast::error_code e,
                              std::size_t bytes_transferred);

            void do_close();

        private:
            /// The handler used to process the incoming request.
            Router<http::response<http::string_body>(*)(const  http::request<http::string_body> &request)> &requestRouter_;

            beast::tcp_stream stream_;
            beast::flat_buffer buffer_;

            http::request<http::string_body> request_;
            std::shared_ptr<void> res_;
        };
} // namespace server3


#endif //BOOST_ASIO_SERVER_CONNECTION_H
