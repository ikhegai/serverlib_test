#include <vector>
#include <thread>

#include "clientserver/clientserver.h"

using namespace clientserver;

using buff = std::vector<unsigned char>;

void foo(const std::string& host, int port, int n)
{
    buff b(3);

    for (int i = 0; i < n; i++)
    {
        try
        {
            client_buffer c = connect(host, port);

            c << "foo";
            c >> b;
        } catch (std::exception& e)
        {
            std::cerr << "CLIENT ERR: " << e.what() << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 5)
        exit(1);

    std::string host(argv[1]);
    auto port = ::atoi(argv[2]);
    auto conn_num = ::atoi(argv[3]);
    auto conc_num = ::atoi(argv[4]);


    std::vector<std::thread> pool;
    for (int i = 0; i < conc_num; i++)
    {
        pool.push_back(std::thread(foo, host, port, conn_num / conc_num));
    }

    for (auto&x : pool)
    {
        if (x.joinable())
            x.join();
    }
}
