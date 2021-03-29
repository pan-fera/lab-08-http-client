//
// Copyright 2021 pan_fera
//

#include "Client.hpp"

#include <utility>
Client::Client(std::string username_, std::string host_, std::string port_,
std::string target_):_username(std::move(username_)), _host(std::move(host_)),
                                     _port(std::move(port_)),
                                     _target(std::move(target_)){}
json Client::send(std::string input){
  int version = 11;

  net::io_context ioc;

  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

  auto const results = resolver.resolve(_host, _port);

  stream.connect(results);

  http::request<http::string_body> req{http::verb::post, _target,
                                       version};
  req.set(boost::beast::http::field::host, _host);
  req.set(boost::beast::http::field::user_agent, _username);
  req.body()="{\"input\":\""+input+"\"}";
  req.prepare_payload();
  http::write(stream, req);


  beast::flat_buffer buffer;
  http::response<http::string_body> res;

  http::read(stream, buffer, res);
  json response;

  if (res.result() == http::status::ok)
     response = json::parse(res.body());
  else
    response = res.body();

  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};
  return response;
}

std::ostream& operator<<(std::ostream &out,  Client& client) {
  std::string input;
  std::cout << "Enter your request:" << std::endl;
  std::cin >> input;
  out << client.send(input).dump(4) << std::endl;
  return out;
}
