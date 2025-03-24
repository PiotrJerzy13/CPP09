/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListSorter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:33:21 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 15:30:09 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <list>
#include <iostream>
#include <ctime>

class ListSorter {
public:
	ListSorter(const std::list<int>& input);
	~ListSorter() = default;
	ListSorter(const ListSorter&) = default;
	ListSorter& operator=(const ListSorter&) = default;
	void sort();
	void printBefore() const;
	void printAfter() const;
	double getExecutionTime() const;

private:
	std::list<int> data_;
	std::clock_t startTime_;
	std::clock_t endTime_;
	
	void fordJohnsonSort(std::list<int>& lst);
};
