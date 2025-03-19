/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:36:13 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/19 11:45:55 by pwojnaro         ###   ########.fr       */
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

public:
    BitcoinExchange() = default;
    
    void loadDatabase(const std::string& filename);
    [[nodiscard]] float getExchangeRate(const std::string& date) const;
    [[nodiscard]] bool isValidDate(std::string_view date);
    [[nodiscard]] bool isValidValue(float value);
};
