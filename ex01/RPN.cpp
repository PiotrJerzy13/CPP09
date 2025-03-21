/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:02:31 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/21 12:04:50 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

int RPN::evaluate(const std::string& expression) 
{
    std::istringstream iss(expression);
    std::string token;
    std::stack<int> stack;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") 
		{
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else {
                if (b == 0)
                    throw std::runtime_error("Error");
                stack.push(a / b);
            }
        } else if (token.size() == 1 && isdigit(token[0])) 
		{
            stack.push(token[0] - '0');
        } 
		else 
		{
            throw std::runtime_error("Error");
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error");

    return stack.top();
}
