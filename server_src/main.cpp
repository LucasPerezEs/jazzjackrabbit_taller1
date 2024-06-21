#include <exception>
#include <iostream>

#include "headers/server.h"

int main(int argc, char* argv[]) {
    try {
        int ret = -1;

        if (argc != 2) {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        Server server(argv[1]);
        server.run();

        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cout << "entro en catch B\n";
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
