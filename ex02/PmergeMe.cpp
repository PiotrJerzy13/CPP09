/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:59:51 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 15:35:17 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

bool isPositiveInteger(const std::string& str) 
{
	if (str.empty())
		return false;
	
	for (size_t i = 0; i < str.length(); ++i) 
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	
	try {
		size_t pos;
		long long num = std::stoll(str, &pos);
		
		if (pos != str.length() || num <= 0 || num > INT_MAX)
			return false;
		
		return true;
	} 
	catch (const std::exception& e) 
	{
		return false;
	}
}
