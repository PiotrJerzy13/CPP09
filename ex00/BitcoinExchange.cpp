/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:38:06 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/21 12:06:17 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <filesystem>
#include <cctype>
#include "BitcoinExchange.hpp"

bool BitcoinExchange::isValidDate(std::string_view date) const {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7) continue;
		if (!isdigit(date[i])) return false;
	}
	return true;
}

bool BitcoinExchange::isValidValue(float value) const 
{
	return (value >= 0 && value <= 1000);
}

void BitcoinExchange::loadDatabase(const std::string& filename) 
{
	std::ifstream file(filename);
	std::string line, date;
	float price;

	if (!file) {
		throw std::runtime_error("Error: could not open database file.");
	}

	while (getline(file, line)) {
		std::stringstream ss(line);
		getline(ss, date, ',');
		ss >> price;
		if (!isValidDate(date)) {
			throw std::runtime_error("Error: invalid date format in database.");
		}
		database[date] = price;
	}

	if (database.empty()) {
		throw std::runtime_error("Error: database is empty.");
	}
}

float BitcoinExchange::getExchangeRate(std::string_view date) const {
	if (!isValidDate(date)) {
		throw std::runtime_error("Error: invalid date format in input.");
	}

	// Convert std::string_view to std::string
	std::string dateStr(date);
	auto it = database.lower_bound(dateStr);
	if (it == database.end() || it->first != dateStr) {
		if (it == database.begin()) {
			throw std::runtime_error("Error: no valid exchange rate found for the given date.");
		}
		--it;
	}
	return it->second;
}
