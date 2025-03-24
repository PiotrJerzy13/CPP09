/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:02:36 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 15:34:42 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VectorSorter.hpp"
#include "ListSorter.hpp"
#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iomanip>
#include <sstream>

int main(int argc, char* argv[]) 
{
	if (argc < 2) 
	{
		std::cerr << "Error: No arguments provided." << std::endl;
		std::cerr << "Usage: " << argv[0] << " [positive integers...]" << std::endl;
		return 1;
	}
	
	std::vector<int> numbers;
	
	for (int i = 1; i < argc; ++i) 
	{
		std::string arg = argv[i];
		
		if (!isPositiveInteger(arg)) 
		{
			std::cerr << "Error: Invalid argument '" << arg << "'. Only positive integers are allowed." << std::endl;
			return 1;
		}
		
		int num = std::atoi(arg.c_str());
		numbers.push_back(num);
	}
	
	std::vector<int> vec(numbers);
	std::list<int> lst(numbers.begin(), numbers.end());
	
	VectorSorter vectorSorter(vec);
	ListSorter listSorter(lst);
	
	std::cout << "Number of elements: " << numbers.size() << std::endl;
	
	if (numbers.size() <= 5) 
	{
		vectorSorter.printBefore();
	} 
	else 
	{
		std::cout << "Before: ";
		for (size_t i = 0; i < 5 && i < numbers.size(); ++i) 
		{
			std::cout << numbers[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	
	vectorSorter.sort();
	listSorter.sort();
	
	if (numbers.size() <= 5) 
	{
		vectorSorter.printAfter();
	} 
	else 
	{
		std::cout << "After: ";
		std::vector<int> sortedVec = vec;
		std::sort(sortedVec.begin(), sortedVec.end());
		for (size_t i = 0; i < 5 && i < sortedVec.size(); ++i) {
			std::cout << sortedVec[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " << vectorSorter.getExecutionTime() 
			  << " ms" << std::endl;
	
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::list : " << listSorter.getExecutionTime() 
			  << " ms" << std::endl;
	
	return 0;
}