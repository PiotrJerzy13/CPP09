/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListSorter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:32:21 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 13:52:32 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListSorter.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

ListSorter::ListSorter(const std::list<int>& input) : data_(input) {}

void ListSorter::printBefore() const 
{
    std::cout << "Before: ";
    for (std::list<int>::const_iterator it = data_.begin(); it != data_.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void ListSorter::printAfter() const 
{
    std::cout << "After: ";
    for (std::list<int>::const_iterator it = data_.begin(); it != data_.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void ListSorter::sort() 
{
    startTime_ = std::clock();
    if (data_.size() > 1)
        fordJohnsonSort(data_);
    endTime_ = std::clock();
}

double ListSorter::getExecutionTime() const
{
    return static_cast<double>(endTime_ - startTime_) / CLOCKS_PER_SEC * 1000.0;
}

// Ford-Johnson algorithm for lists
void ListSorter::fordJohnsonSort(std::list<int>& lst) 
{
    if (lst.size() <= 1)
        return;
    
    // Step 1: Create pairs of elements
    typedef std::pair<int, int> Pair;
    std::vector<Pair> pairs;
    
    std::list<int>::iterator it = lst.begin();
    std::list<int> remaining;
    
    // Create pairs and remember odd element if any
    while (it != lst.end()) 
	{
        int first = *it++;
        if (it != lst.end()) 
		{
            int second = *it++;
            // Order each pair (larger, smaller)
            if (first > second)
                pairs.push_back(std::make_pair(first, second));
            else
                pairs.push_back(std::make_pair(second, first));
        } 
		else 
		{
            // Handle remaining odd element
            remaining.push_back(first);
        }
    }
    
    // Step 2: Sort the pairs by their larger elements
    typedef std::vector<std::vector<Pair>::iterator> PairIterVec;
    PairIterVec pairIters;
    
    for (std::vector<Pair>::iterator pit = pairs.begin(); pit != pairs.end(); ++pit) 
	{
        pairIters.push_back(pit);
    }
    
    std::sort(pairIters.begin(), pairIters.end(), 
        [](const std::vector<Pair>::iterator& a, const std::vector<Pair>::iterator& b) 
		{
            return a->first < b->first;
        });
    
    // Step 3: Build the result list with the larger elements
    std::list<int> result;
    
    // Add all larger elements in sorted order
    for (PairIterVec::iterator it = pairIters.begin(); it != pairIters.end(); ++it) 
	{
        result.push_back((*it)->first);
    }
    
    // Step 4: Insert the smaller elements using the Ford-Johnson insertion sequence
    // First insert the first smaller element
    if (!pairIters.empty()) 
	{
        std::list<int>::iterator insertPos = result.begin();
        int insertVal = pairIters[0]->second;
        
        // Find the position to insert
        while (insertPos != result.end() && *insertPos < insertVal)
            ++insertPos;
        
        result.insert(insertPos, insertVal);
        
        // Insert remaining elements using the Ford-Johnson sequence
        size_t groupSize = 2;
        size_t start = 1;
        
        while (start < pairIters.size()) 
		{
            // Process the current group
            size_t end = std::min(start + groupSize, pairIters.size());
            
            for (size_t i = start; i < end; ++i) 
			{
                insertVal = pairIters[i]->second;
                insertPos = result.begin();
                
                // Binary search-like insertion for lists
                // (not as efficient as with random access containers)
                size_t count = 0;
                size_t pos = 0;
                std::list<int>::iterator it = result.begin();
                
                // Find insertion position
                while (it != result.end() && count < i + 1) 
				{
                    if (*it < insertVal) 
					{
                        insertPos = ++it;
                        pos++;
                    } 
					else 
					{
                        break;
                    }
                    count++;
                }
                
                result.insert(insertPos, insertVal);
            }
            
            start = end;
            groupSize *= 2;
        }
    }
    
    // Add remaining odd element if any
    if (!remaining.empty()) 
	{
        int val = remaining.front();
        std::list<int>::iterator pos = result.begin();
        
        while (pos != result.end() && *pos < val)
            ++pos;
        
        result.insert(pos, val);
    }
    
    lst = result;
}
