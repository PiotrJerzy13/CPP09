/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorSorter.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:36:52 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 15:37:10 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VectorSorter.hpp"
#include <algorithm>
#include <utility>
#include <cmath>

VectorSorter::VectorSorter(const std::vector<int>& input) : data_(input) {}

void VectorSorter::printBefore() const 
{
	std::cout << "Before: ";
	for (size_t i = 0; i < data_.size(); ++i)
		std::cout << data_[i] << " ";
	std::cout << std::endl;
}

void VectorSorter::printAfter() const 
{
	std::cout << "After: ";
	for (size_t i = 0; i < data_.size(); ++i)
		std::cout << data_[i] << " ";
	std::cout << std::endl;
}

void VectorSorter::sort() 
{
	startTime_ = std::clock();
	if (data_.size() > 1)
		data_ = fordJohnsonSort(data_);
	endTime_ = std::clock();
}

double VectorSorter::getExecutionTime() const
{
	return static_cast<double>(endTime_ - startTime_) / CLOCKS_PER_SEC * 1000.0;
}

std::vector<int> VectorSorter::fordJohnsonSort(const std::vector<int>& vec) 
{
	if (vec.size() <= 1)
		return vec;
	
	std::vector<std::pair<int, int>> pairs;
	size_t i = 0;
	
	while (i + 1 < vec.size()) 
	{
		int a = vec[i];
		int b = vec[i + 1];
		if (a > b) 
		{
			pairs.push_back(std::make_pair(a, b));
		}
		 else 
		{
			pairs.push_back(std::make_pair(b, a));
		}
		i += 2;
	}
	
	int remainingElement = -1;
	bool hasRemainingElement = (vec.size() % 2 == 1);
	if (hasRemainingElement) 
	{
		remainingElement = vec[vec.size() - 1];
	}
	
	std::vector<int> largerElements;
	std::vector<int> smallerElements;
	
	for (const auto& pair : pairs) 
	{
		largerElements.push_back(pair.first);
		smallerElements.push_back(pair.second);
	}
	
	if (largerElements.size() > 1) 
	{
		largerElements = fordJohnsonSort(largerElements);
	}
	
	std::vector<int> reorderedSmaller;
	std::vector<std::pair<int, int>> sortedPairs;
	
	for (size_t i = 0; i < largerElements.size(); ++i) 
	{
		for (size_t j = 0; j < pairs.size(); ++j) 
		{
			if (largerElements[i] == pairs[j].first && 
				(sortedPairs.empty() || pairs[j].first != sortedPairs.back().first)) 
				{
				sortedPairs.push_back(pairs[j]);
				reorderedSmaller.push_back(pairs[j].second);
				break;
			}
		}
	}
	
	std::vector<int> result = largerElements;
	
	if (!reorderedSmaller.empty()) 
	{
		std::vector<int>::iterator insertPos = std::lower_bound(result.begin(), result.end(), reorderedSmaller[0]);
		result.insert(insertPos, reorderedSmaller[0]);
		
		std::vector<size_t> jacobsthalIndices = generateJacobsthalIndices(reorderedSmaller.size());
		
		for (size_t i = 1; i < jacobsthalIndices.size(); ++i) 
		{
			size_t idx = jacobsthalIndices[i];
			if (idx < reorderedSmaller.size())
			{
				int val = reorderedSmaller[idx];
				insertPos = std::lower_bound(result.begin(), result.end(), val);
				result.insert(insertPos, val);
			}
		}
	}
	
	if (hasRemainingElement) 
	{
		std::vector<int>::iterator insertPos = std::lower_bound(result.begin(), result.end(), remainingElement);
		result.insert(insertPos, remainingElement);
	}
	
	return result;
}

std::vector<size_t> VectorSorter::generateJacobsthalIndices(size_t n) 
{
	if (n <= 1) 
	{
		return {0};
	}
	
	std::vector<size_t> jacobsthal = {0, 1};
	while (jacobsthal.back() < n) 
	{
		size_t next = jacobsthal[jacobsthal.size() - 1] * 2 + jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}
	
	std::vector<size_t> indices;
	indices.push_back(0);
	
	for (size_t i = 2; i < jacobsthal.size(); ++i) 
	{
		size_t start = jacobsthal[i - 1];
		size_t end = std::min(jacobsthal[i], n);
		
		for (size_t j = end; j > start; --j) 
		{
			indices.push_back(j - 1);
		}
	}
	
	std::vector<bool> included(n, false);
	for (size_t idx : indices) 
	{
		if (idx < n) 
		{
			included[idx] = true;
		}
	}
	
	for (size_t i = 0; i < n; ++i) 
	{
		if (!included[i]) 
		{
			indices.push_back(i);
		}
	}
	
	return indices;
}
