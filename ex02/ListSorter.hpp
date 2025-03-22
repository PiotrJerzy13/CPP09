/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListSorter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:33:21 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 13:33:35 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <list>

class ListSorter {
public:
    ListSorter(const std::list<int>& input);
    void sort();
    void printBefore() const;
    void printAfter() const;

private:
    std::list<int> data_;
    void mergeInsertSort(std::list<int>& lst);
    
};