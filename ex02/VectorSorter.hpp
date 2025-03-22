/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorSorter.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:34:15 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 13:48:34 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <vector>
#include <iostream>
#include <ctime>

class VectorSorter {
public:
    VectorSorter(const std::vector<int>& input);
    void sort();
    void printBefore() const;
    void printAfter() const;
    double getExecutionTime() const;

private:
    std::vector<int> data_;
    std::clock_t startTime_;
    std::clock_t endTime_;
    
    std::vector<int> fordJohnsonSort(const std::vector<int>& vec);
    std::vector<size_t> generateJacobsthalIndices(size_t n);
};
