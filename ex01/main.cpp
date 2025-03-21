/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:03:14 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/21 12:04:01 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[]) 
{
	if (argc != 2) 
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try {
		int result = RPN::evaluate(argv[1]);
		std::cout << result << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	return 0;
}
