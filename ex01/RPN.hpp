/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:01:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/03/22 11:34:57 by pwojnaro         ###   ########.fr       */
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
	static std::optional<int> evaluate(const std::string& expression);
};
