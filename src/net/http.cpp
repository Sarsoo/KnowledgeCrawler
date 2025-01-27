#include "http.hpp"

// https://www.boost.org/doc/libs/1_87_0/libs/beast/example/http/client/sync-ssl/http_client_sync_ssl.cpp

std::shared_ptr<ssl::stream<beast::tcp_stream>> connect_stream(const std::string &host, int port) {
    // The io_context is required for all I/O
    net::io_context ioc;

    // The SSL context is required, and holds certificates
    ssl::context ctx(ssl::context::tlsv12_client);

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Verify the remote server's certificate
    ctx.set_verify_mode(ssl::verify_peer);

    // These objects perform our I/O
    tcp::resolver resolver(ioc);
    auto stream = std::make_shared<ssl::stream<beast::tcp_stream>>(ioc, ctx);

    // Set SNI Hostname (many hosts need this to handshake successfully)
    if(! SSL_set_tlsext_host_name(stream->native_handle(), host.c_str()))
    {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        throw beast::system_error{ec};
    }

    // Look up the domain name
    auto const results = resolver.resolve(host, std::to_string(port));

    // Make the connection on the IP address we get from a lookup
    beast::get_lowest_layer(*stream).connect(results);

    // Perform the SSL handshake
    stream->handshake(ssl::stream_base::client);

    return stream;
}

http::response<http::dynamic_body> read_response(const std::shared_ptr<ssl::stream<beast::tcp_stream>> &stream) {
    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(*stream, buffer, res);

    return res;
}

void shutdown_stream(const std::shared_ptr<ssl::stream<beast::tcp_stream>> &stream) {
    // Gracefully close the socket
    beast::error_code ec;
    stream->shutdown(ec);
    if(ec == net::error::eof)
    {
        // Rationale:
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if(ec)
        throw beast::system_error{ec};
}

http::response<http::dynamic_body> request(http::verb method, const std::string &host, int port, std::string target) {

    auto stream = connect_stream(host, port);

    // if (method == http::verb::get) {
    //     // Set up an HTTP GET request message
    //     http::request<http::string_body> req{method, target, 11};
    //     req.set(http::field::host, host);
    //     req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    //
    //     // Send the HTTP request to the remote host
    //     http::write(stream, req);
    // }
    // else if (method == http::verb::post) {
    //     // Set up an HTTP GET request message
    //     http::request<json_body> req{method, target, 11};
    //     req.set(http::field::host, host);
    //     req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    //
    //     // Send the HTTP request to the remote host
    //     http::write(stream, req);
    // }

    auto response = read_response(stream);

    shutdown_stream(stream);

    // Write the message to standard out
    std::cout << response << std::endl;
    return response;
}