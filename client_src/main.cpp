#include <exception>
#include <fstream>
#include <iostream>

//#include "client.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3 && argc != 4) {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << " <hostname> <servername> [<filename>]\n";
            return -1;
        }

        const std::string hostname = std::string(argv[1]);
        const std::string servername = std::string(argv[2]);

        std::ifstream input;

        std::istream* in = (argc == 4) ? &input : &std::cin;

        //Client client(hostname, servername);
        //client.run(*in);

        input.close();

        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
