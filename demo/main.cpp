#include "Client.hpp"

int main(int argc, char** argv)
{
  try
  {
    if(argc != 5)
    {
      std::cerr <<
                "Usage: http-client-sync <username> <host> <port> <target>]\n" <<
                "Example:\n" <<
                "http-client-sync client 0.0.0.0 8080 /v1/api/suggest /\n";
      return EXIT_FAILURE;
    }
    auto const username = argv[1];
    auto const host = argv[2];
    auto const port = argv[3];
    auto const target = argv[4];

    Client client(username, host, port, target);

    std::string _continue;
   // do {
      std::cout << client;
      std::cout<<"Proceed? y/n: ";
      std::cin>>_continue;
   // }while(_continue == "y");
  }
  catch(std::exception const& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

