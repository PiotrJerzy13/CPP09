#include "BitcoinExchange.hpp"

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
	{
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }
    
    BitcoinExchange btc;
    try {
        btc.loadDatabase("data.csv");
    } 
	catch (const std::exception& e)
	{
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    btc.processInputFile(argv[1]);
    return 0;
}