/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:36:13 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 14:35:40 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <optional>
#include <string_view>

class BitcoinExchange {
	private:
		std::map<std::string, float> database;
		const std::string MIN_DATE = "2009-01-03";
		const std::string MAX_DATE = "2025-03-22";
	public:
		BitcoinExchange() = default;
		~BitcoinExchange() = default;
		BitcoinExchange(const BitcoinExchange& other) = delete;
		BitcoinExchange& operator=(const BitcoinExchange& other) = delete;
		void loadDatabase(const std::string& filename);
		[[nodiscard]] std::optional<float> getExchangeRate(std::string_view date) const;
		[[nodiscard]] bool isValidDate(std::string_view date) const;
		[[nodiscard]] bool isValidValue(float value) const;
		bool isWithinDateRange(std::string_view date) const;
		void processInputFile(const std::string& filename);
		std::string_view trim(std::string_view sv) const;
		std::optional<float> parseValue(std::string_view valueStr) const;
		void processLine(const std::string& line);
		std::optional<std::string> validateDate(std::string_view dateStr) const;
	};
