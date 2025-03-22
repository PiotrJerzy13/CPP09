/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:02:31 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 11:34:36 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <optional>

std::optional<RPN::Token> RPN::parseToken(const std::string& tokenStr)
 {
	if (tokenStr.size() == 1 && std::isdigit(tokenStr[0])) 
	{
		return tokenStr[0] - '0';
	} 
	else if (tokenStr.size() == 1 && (tokenStr[0] == '+' || tokenStr[0] == '-' || tokenStr[0] == '*' || tokenStr[0] == '/')) 
	{
		return tokenStr[0];
	}
	return std::nullopt;
}

	std::optional<int> RPN::evaluate(const std::string& expression) 
	{
	std::istringstream iss(expression);
	std::string tokenStr;
	std::stack<int> stack;

	while (iss >> tokenStr) 
	{
		auto tokenOpt = parseToken(tokenStr);
		if (!tokenOpt) 
		{
			return std::nullopt;
		}

		auto token = *tokenOpt;
		if (std::holds_alternative<int>(token)) 
		{
			stack.push(std::get<int>(token));
		} 
		else 
		{
			char op = std::get<char>(token);
			if (stack.size() < 2) 
			{
				return std::nullopt;
			}

			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();

			switch (op) 
			{
				case '+': stack.push(a + b); break;
				case '-': stack.push(a - b); break;
				case '*': stack.push(a * b); break;
				case '/':
					if (b == 0) 
					{
						return std::nullopt;
					}
					stack.push(a / b);
					break;
				default:
					return std::nullopt;
			}
		}
	}

	if (stack.size() != 1) 
	{
		return std::nullopt;
	}

	return stack.top();
}
