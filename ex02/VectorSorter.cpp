/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorSorter.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:36:52 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 13:53:56 by pwojnaro         ###   ########.fr       */
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
    
    // Step 1: Create pairs of elements
    std::vector<std::pair<int, int>> pairs;
    size_t i = 0;
    
    // Create pairs and sort each pair internally (larger first, smaller second)
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
    
    // Save the remaining element if array size is odd
    int remainingElement = -1;
    bool hasRemainingElement = (vec.size() % 2 == 1);
    if (hasRemainingElement) {
        remainingElement = vec[vec.size() - 1];
    }
    
    // Step 2: Sort pairs by their larger element
    std::vector<int> largerElements;
    std::vector<int> smallerElements;
    
    // Extract larger elements for sorting
    for (const auto& pair : pairs) 
	{
        largerElements.push_back(pair.first);
        smallerElements.push_back(pair.second);
    }
    
    // Recursively sort the larger elements if there are more than one pair
    if (largerElements.size() > 1) 
	{
        largerElements = fordJohnsonSort(largerElements);
    }
    
    // Step 3: Reorder smaller elements to match the new order of larger elements
    std::vector<int> reorderedSmaller;
    std::vector<std::pair<int, int>> sortedPairs;
    
    // Create a mapping from original pairs to sorted larger elements
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
    
    // Step 4: Start with the sorted larger elements
    std::vector<int> result = largerElements;
    
    // Step 5: Insert the smaller elements using the Ford-Johnson insertion sequence
    if (!reorderedSmaller.empty()) 
	{
        // Insert the first smaller element
        std::vector<int>::iterator insertPos = std::lower_bound(result.begin(), result.end(), reorderedSmaller[0]);
        result.insert(insertPos, reorderedSmaller[0]);
        
        // Define the Ford-Johnson insertion sequence
        // Jacobsthal numbers determine the insertion order
        std::vector<size_t> jacobsthalIndices = generateJacobsthalIndices(reorderedSmaller.size());
        
        // Insert remaining elements according to the Ford-Johnson sequence
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
    
    // Insert the remaining element if exists
    if (hasRemainingElement) {
        std::vector<int>::iterator insertPos = std::lower_bound(result.begin(), result.end(), remainingElement);
        result.insert(insertPos, remainingElement);
    }
    
    return result;
}

// Generate Jacobsthal indices for Ford-Johnson algorithm
std::vector<size_t> VectorSorter::generateJacobsthalIndices(size_t n) 
{
    if (n <= 1) 
	{
        return {0};
    }
    
    // Generate Jacobsthal numbers
    std::vector<size_t> jacobsthal = {0, 1};
    while (jacobsthal.back() < n) 
	{
        size_t next = jacobsthal[jacobsthal.size() - 1] * 2 + jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
    }
    
    // Generate sequence indices based on Jacobsthal numbers
    std::vector<size_t> indices;
    indices.push_back(0);  // Always start with index 0
    
    for (size_t i = 2; i < jacobsthal.size(); ++i) 
	{
        size_t start = jacobsthal[i - 1];
        size_t end = std::min(jacobsthal[i], n);
        
        // Add indices in reverse from this Jacobsthal range
        for (size_t j = end; j > start; --j) 
		{
            indices.push_back(j - 1);
        }
    }
    
    // Ensure all indices up to n-1 are included
    std::vector<bool> included(n, false);
    for (size_t idx : indices) 
	{
        if (idx < n) 
		{
            included[idx] = true;
        }
    }
    
    // Add any missing indices
    for (size_t i = 0; i < n; ++i) 
	{
        if (!included[i]) 
		{
            indices.push_back(i);
        }
    }
    
    return indices;
}
