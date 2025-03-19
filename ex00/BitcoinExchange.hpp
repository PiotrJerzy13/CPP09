/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:36:13 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/19 10:37:04 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

class BitcoinExchange {
private:
    std::map<std::string, float> database;

    bool isValidDate(const std::string& date);
    bool isValidValue(float value);

public:
    BitcoinExchange();
    void loadDatabase(const std::string& filename);
    float getExchangeRate(const std::string& date);
};

#endif