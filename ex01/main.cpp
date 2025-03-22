/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:03:14 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 11:34:29 by pwojnaro         ###   ########.fr       */
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

	auto result = RPN::evaluate(argv[1]);
	if (result) 
	{
		std::cout << *result << std::endl;
	} 
	else 
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	return 0;
}
