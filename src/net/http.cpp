#include "http.hpp"

#include <boost/beast/version.hpp>
#include <boost/log/trivial.hpp>
#include <utility>

// https://www.boost.org/doc/libs/1_87_0/libs/beast/example/http/client/sync-ssl/http_client_sync_ssl.cpp

namespace kc {

http::response<http::dynamic_body> read_response(const std::shared_ptr<ssl::stream<beast::tcp_stream>> &stream) {
    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    BOOST_LOG_TRIVIAL(debug) << "Reading HTTP response";
    http::read(*stream, buffer, res);
    BOOST_LOG_TRIVIAL(debug) << "Received response from (" << res.result_int() << ")";

    return res;
}

void shutdown_stream(const std::shared_ptr<ssl::stream<beast::tcp_stream>> &stream) {
    // Gracefully close the socket
    beast::error_code ec;
    BOOST_LOG_TRIVIAL(debug) << "Gracefully shutting down stream";
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

void request(http::verb method, const std::string &host, std::string target, std::string body, std::unique_ptr<std::unordered_map<std::string, std::string>> headers) {
    request(std::move(method), std::move(host), std::move(target), 443, std::move(body), std::move(headers));
}

void request(http::verb method, const std::string &host, std::string target, std::string body) {
    request(std::move(method), std::move(host), std::move(target), 443, std::move(body), nullptr);
}

void request(http::verb method, const std::string &host, std::string target, int port, std::string body, std::unique_ptr<std::unordered_map<std::string, std::string>> headers) {

    BOOST_LOG_TRIVIAL(info) << "Opening connection to [" << host << ":" << port << "]";

    // The io_context is required for all I/O
    net::io_context ioc;

    // The SSL context is required, and holds certificates
    ssl::context ctx(ssl::context::tlsv12_client);

    // This holds the root certificate used for verification
    // load_root_certificates(ctx);

    // Verify the remote server's certificate
    // ctx.set_verify_mode(ssl::verify_peer);

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
    BOOST_LOG_TRIVIAL(debug) << "Resolving IP for [" << host << "]";
    auto const results = resolver.resolve(host, std::to_string(port));

    // Make the connection on the IP address we get from a lookup
    BOOST_LOG_TRIVIAL(debug) << "Connecting stream [" << host << ":" << port << "]";
    beast::get_lowest_layer(*stream).connect(results);

    // Perform the SSL handshake
    BOOST_LOG_TRIVIAL(debug) << "Performing TLS handshake [" << host << ":" << port << "]";
    stream->handshake(ssl::stream_base::client);

    http::request<http::string_body> req{method, target, 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    if (headers) {
        for (auto const &kv : *headers) {
            req.set(kv.first, kv.second);
        }
    }

    req.body() = body;

    req.prepare_payload(); // set content-length based on the body

    // Send the HTTP request to the remote host
    BOOST_LOG_TRIVIAL(debug) << "Writing HTTP request to stream [" << host << ":" << port << "]";
    http::write(*stream, req);

    auto response = read_response(stream);

    shutdown_stream(stream);
}
}