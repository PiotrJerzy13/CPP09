/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorSorter.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:34:15 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 13:36:29 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <vector>
#include <iostream>

class VectorSorter {
public:
    VectorSorter(const std::vector<int>& input);
    void sort();
    void printBefore() const;
    void printAfter() const;

private:
    std::vector<int> data_;
    void mergeInsertSort(std::vector<int>& vec, int left, int right);
    void merge(std::vector<int>& vec, int left, int mid, int right);
};

