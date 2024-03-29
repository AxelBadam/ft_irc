/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandExecution.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:29:01 by ekoljone          #+#    #+#             */
/*   Updated: 2024/02/09 17:00:02 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMMANDEXECUTION_HPP__
#define __COMMANDEXECUTION_HPP__

#include "Server.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "Utils.hpp"
#include <regex>
#include "Channel.hpp"
#include <algorithm>

class Server;

class CommandExecution
{
public:
	static void	execute(User *user, Server *server, Command &command);

private:
	CommandExecution();
	CommandExecution(User *user, Server *server);
    CommandExecution(CommandExecution const &cpy);
    ~CommandExecution();
    CommandExecution &operator=(CommandExecution const &rhs);

	static User		*_user;
	static Server	*_server;
	static Command	_command;

	static void		_motd();
	static void		_join();
	static void		_joinExistingChannel(Channel *channel, std::string const &key);
	static void		_joinNewChannel(std::string const &name);
	static void		_joinSucces(Channel *channel);
	static void		_nick();
	static bool 	_isValidNick();
	static void		_pass();
	static void		_userF();
	static void		_kick();
	static void		_mode();
	static void		_userMode();
	static void		_channelMode();
	static void		_removeChannelModes(Channel *channel, std::string const &mode, std::string const &channelName, std::vector<std::string> const &modeParams);
	static void		_addChannelModes(Channel *channel, std::string const &mode, std::string const &channelName, std::vector<std::string> const &modeParams);
	static bool		_checkForOpPrivilages(Channel *channel);
	static void		_ping();
	static void		_pong();
	static void		_invite();
	static void		_privmsg();
	static void		_quit();
	static void		_topic();
	static void		_part();
	static void		_who();
	};


#endif
