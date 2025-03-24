/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:38:06 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 15:11:25 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <filesystem>
#include <cctype>

bool BitcoinExchange::isValidDate(std::string_view date) const 
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	
	for (size_t i = 0; i < 10; i++) 
	{
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(date[i])) return false;
	}
	
	int year = std::stoi(std::string(date.substr(0, 4)));
	int month = std::stoi(std::string(date.substr(5, 2)));
	int day = std::stoi(std::string(date.substr(8, 2)));
	
	if (month < 1 || month > 12) return false;
	
	const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDays = daysInMonth[month];
	
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		maxDays = 29;
	
	return day >= 1 && day <= maxDays;
}

bool BitcoinExchange::isWithinDateRange(std::string_view date) const 
{
	std::string dateStr(date);
	return dateStr >= MIN_DATE && dateStr <= MAX_DATE;
}

bool BitcoinExchange::isValidValue(float value) const 
{
	return (value >= 0 && value <= 1000);
}

std::string_view BitcoinExchange::trim(std::string_view sv) const 
{
	const auto start = sv.find_first_not_of(" \t");
	if (start == std::string_view::npos) return {};
	
	const auto end = sv.find_last_not_of(" \t");
	return sv.substr(start, end - start + 1);
}

void BitcoinExchange::loadDatabase(const std::string& filename) 
{
	std::ifstream file(filename);
	std::string line, date;
	float price;

	if (!file) 
	{
		throw std::runtime_error("Error: could not open database file.");
	}

	if (std::getline(file, line) && line != "date,exchange_rate") 
	{
		std::stringstream ss(line);
		if (std::getline(ss, date, ',') && ss >> price) 
		{
			date = std::string(trim(std::string_view(date)));
			if (isValidDate(date)) 
			{
				database[date] = price;
			}
		}
	}
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		if (std::getline(ss, date, ',') && ss >> price) 
		{
			date = std::string(trim(std::string_view(date)));
			if (isValidDate(date)) 
			{
				database[date] = price;
			}
		}
	}

	if (database.empty()) 
	{
		throw std::runtime_error("Error: database is empty or contains no valid entries.");
	}
}

std::optional<float> BitcoinExchange::getExchangeRate(std::string_view date) const 
{
	if (!isValidDate(date)) 
	{
		return std::nullopt;
	}

	if (!isWithinDateRange(date)) 
	{
		return std::nullopt;
	}

	std::string dateStr(date);
	auto it = database.upper_bound(dateStr);
	if (it == database.begin()) 
	{
		return std::nullopt;
	}
	--it;
	return it->second;
}

std::optional<std::string> BitcoinExchange::validateDate(std::string_view dateStr) const 
{
	std::string date(dateStr);
	if (!isValidDate(date)) return std::nullopt;
	if (!isWithinDateRange(date)) return std::nullopt;
	return date;
}

std::optional<float> BitcoinExchange::parseValue(std::string_view valueStr) const 
{
	try {
		float value = std::stof(std::string(valueStr));
		if (value < 0) return std::nullopt;
		if (value > 1000) return std::nullopt;
		return value;
	} 
	catch (const std::exception&) 
	{
		return std::nullopt;
	}
}

void BitcoinExchange::processInputFile(const std::string& filename) 
{
	std::ifstream input(filename);
	if (!input) 
	{
		std::cerr << "Error: could not open input file." << std::endl;
		return;
	}

	std::string line, date;
	
	std::getline(input, line);
	if (line != "date | value") 
	{
		processLine(line);
	}

	while (std::getline(input, line)) 
	{
		processLine(line);
	}
}

void BitcoinExchange::processLine(const std::string& line) 
{
    std::stringstream ss(line);
    std::string dateStr;
    std::string valueStr;
    
    if (!std::getline(ss, dateStr, '|') || !std::getline(ss, valueStr)) 
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }
    
    auto trimmedDate = trim(std::string_view(dateStr));
    auto trimmedValue = trim(std::string_view(valueStr));
    
    auto date = validateDate(trimmedDate);
    if (!date) 
    {
        if (!isValidDate(std::string(trimmedDate))) 
        {
            std::cout << "Error: bad input => " << trimmedDate << std::endl;
        }
        else 
        {
            std::cout << "Error: date not in range => " << trimmedDate << std::endl;
        }
        return;
    }
    
    auto value = parseValue(trimmedValue);
    if (!value) 
    {
        try {
            float testValue = std::stof(std::string(trimmedValue));
            if (testValue < 0) 
            {
                std::cout << "Error: not a positive number." << std::endl;
            } 
            else if (testValue > 1000) 
            {
                std::cout << "Error: too large a number." << std::endl;
            }
        } 
        catch (const std::exception&) 
        {
            std::cout << "Error: bad input => " << trimmedValue << std::endl;
        }
        return;
    }
    
    auto rate = getExchangeRate(*date);
    if (!rate) 
    {
        std::cout << "Error: no exchange rate available for " << *date << std::endl;
        return;
    }
    float result = *value * *rate;
    std::cout << *date << " => " << *value << " = " << std::fixed << std::setprecision(2) << result << std::endl;
}
