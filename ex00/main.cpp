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

	std::string line, date;
    float value;
    while (getline(input, line)) {
        std::stringstream ss(line);
        if (!getline(ss, date, '|') || !(ss >> value)) {
            std::cerr << "Error: invalid input format => " << line << std::endl;
            continue;
        }

        date.erase(date.find_last_not_of(' ') + 1); // Trim trailing spaces
        if (!btc.isValidDate(date)) {
            std::cerr << "Error: invalid date format => " << date << std::endl;
            continue;
        }

        if (!btc.isValidValue(value)) {
            std::cerr << "Error: value must be between 0 and 1000 => " << value << std::endl;
            continue;
        }

        try {
            float rate = btc.getExchangeRate(date);
            std::cout << date << " => " << value << " = " << value * rate << " USD" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}