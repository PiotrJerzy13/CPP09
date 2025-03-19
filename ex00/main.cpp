#include "BitcoinExchange.hpp"
#include "BitcoinExchange.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    try {
        btc.loadDatabase("data.csv");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error: could not open input file." << std::endl;
        return 1;
    }

    return 0;
}