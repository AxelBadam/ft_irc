/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:55:53 by ekoljone          #+#    #+#             */
/*   Updated: 2024/01/25 11:03:54 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <vector>
#include <iostream>
#include <sstream>
#include <regex>

std::vector<std::string> split(std::string const &str, char const &delimeter);
std::string truncateLFCR(std::string const &str);
bool checkIrcPattern(std::string const &str);

#endif
