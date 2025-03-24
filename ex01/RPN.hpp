/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:01:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/24 15:23:44 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>
#include <sstream>
#include <optional>
#include <variant>
#include <stdexcept>
#include <cctype>

class RPN {
	private:
	using Token = std::variant<int, char>;
	static std::optional<Token> parseToken(const std::string& tokenStr);
	
public:
	RPN() = default;
	~RPN() = default;
	RPN(const RPN&) = default;
	RPN& operator=(const RPN&) = default;
	static std::optional<int> evaluate(const std::string& expression);
};
