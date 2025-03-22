/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorSorter.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:36:52 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 13:37:24 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VectorSorter.hpp"

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

void VectorSorter::sort() {
    if (!data_.empty())
        mergeInsertSort(data_, 0, data_.size() - 1);
}

void VectorSorter::mergeInsertSort(std::vector<int>& vec, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeInsertSort(vec, left, mid);
    mergeInsertSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

void VectorSorter::merge(std::vector<int>& vec, int left, int mid, int right) 
{
    std::vector<int> leftVec(vec.begin() + left, vec.begin() + mid + 1);
    std::vector<int> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftVec.size() && j < rightVec.size()) 
	{
        if (leftVec[i] <= rightVec[j])
            vec[k++] = leftVec[i++];
        else
            vec[k++] = rightVec[j++];
    }

    while (i < leftVec.size())
        vec[k++] = leftVec[i++];
    while (j < rightVec.size())
        vec[k++] = rightVec[j++];
}
