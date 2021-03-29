//
// Copyright 2021 pan_fera
//

#ifndef INCLUDE_CLIENT_HPP_
#define INCLUDE_CLIENT_HPP_
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>
using json = nlohmann::json;

class Client {
 public:
  Client(const char* username, const char* host, const char* port,
         const char* target);
  json send(const std::string& input);
  friend std::ostream& operator<<(std::ostream &out, Client& client);
 private:
  std::string _username, _host, _port, _target;
};

#endif  // INCLUDE_CLIENT_HPP_
