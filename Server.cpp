#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;


io_service service;
ip::tcp::endpoint endpoint(ip::tcp::v4(), 1338);
ip::tcp::acceptor acceptor(service, endpoint);
ip::tcp::socket socket2(service);
std::vector<boost::asio::ip::tcp::socket> sockets;

void accept2()
{
    acceptor.accept(socket2);
    std::cout << "Client connected" << std::endl;
}

int main()
{
    std::cout << "Server started" << std::endl;
    std::thread t1(accept2);
    while (true) {
        //std::cout << "Client connected" << std::endl;


        std::string message;
        // Take input using cin
        std::getline(std::cin, message);
        boost::system::error_code error;
        write(socket2, buffer(message), error);
        if (error) {
            std::cout << "Error: " << error.message() << std::endl;
        }
    }
    return 0;
}
