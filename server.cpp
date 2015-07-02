#include <vector>
#include <thread>
#include <chrono>

#include "clientserver/clientserver.h"

using namespace clientserver;

using buff = std::vector<unsigned char>;

struct service_thread
{
    void operator()(service_buffer s)
    {
        buff b(3);

        try
        {
            s >> b;
            s << "bar";
        } catch (std::exception& e)
        {
            std::cerr << "SERVER ERR: " << e.what() << std::endl;
        }
    }

};

int main(int argc, char** argv)
{
    if (argc < 3)
        exit(1);

    std::string host(argv[1]);
    auto port = ::atoi(argv[2]);


    server_socket server(host, port);
    service_thread service;
    serve(server, service);

    std::chrono::seconds duration(1);

    while (1)
    {
        std::this_thread::sleep_for(duration);
    }
}
