/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:02:47 by ekoljone          #+#    #+#             */
/*   Updated: 2024/02/08 17:05:34 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"

User::User() : _isRegistered(false), _passFlag(false), _pingResponseTimer(time(0)), _isRestricted(false) {}

User::User(User const &cpy)
{
	_nick = cpy._nick;
	_user = cpy._user;
	_ipAddr = cpy._ipAddr;
	_userInfo = cpy._userInfo;
	_userInput = cpy._userInput;
	_sendBuffer = cpy._sendBuffer;
	_isRegistered = cpy._isRegistered;
	_passFlag = cpy._passFlag;
	_pingResponseTimer = cpy._pingResponseTimer;
	_isRestricted = cpy._isRestricted;
}

User::~User(){}

User &User::operator=(User const &rhs)
{
    if (this != &rhs)
    {
		_nick = rhs._nick;
		_user = rhs._user;
		_ipAddr = rhs._ipAddr;
		_userInfo = rhs._userInfo;
		_userInput = rhs._userInput;
		_sendBuffer = rhs._sendBuffer;
		_isRegistered = rhs._isRegistered;
		_passFlag = rhs._passFlag;
		_pingResponseTimer = rhs._pingResponseTimer;
		_isRestricted = rhs._isRestricted;
    }
    return (*this);
}

std::string const User::extractFromSendBuffer()
{
	std::string msg;
	if (!_sendBuffer.empty())
	{
		msg = _sendBuffer[0];
		_sendBuffer.erase(_sendBuffer.begin());
	}
	return (msg);
}

void User::addToSendBuffer(std::string const &msg)
{
	_sendBuffer.push_back(msg);
}

// t_command *User::extractCommand()
// {
// 	std::cout << "hi" << std::endl;
// 	if (!_userInput.empty())
// 		std::cout << "inside userinput = " << _userInput[0] << std::endl;
// 	if (_userInput.empty() || _userInput[0].find("\n") == std::string::npos)
// 		return (NULL);
// 	std::vector<std::string> splitted_input = split(extractInput(), ' ');
// 	t_command *command = new t_command;
// 	size_t size = splitted_input.size();
// 	for (size_t i = 0; i < size; i++)
// 	{
// 		while (i < size && splitted_input[i].empty())
// 			i++;
// 		if (command->prefix.empty()
// 			&& command->command.empty()
// 			&& command->params.empty()
// 			&& splitted_input[i].at(0) == ':')
// 			command->prefix = splitted_input[i];
// 		else if (command->command.empty()
// 				&& command->params.empty())
// 			command->command = splitted_input[i];
// 		else if (!command->command.empty()
// 				&& splitted_input[i].at(0) == ':')
// 		{
// 			std::string msg;
// 			while (i < size)
// 			{
// 				msg.append(splitted_input[i++]);
// 				if (i < size)
// 					msg.append(" ");
// 			}
// 			command->params.push_back(msg);
// 		}
// 		else
// 			command->params.push_back(splitted_input[i]);

// 	}
// 	printCommand(command);
// 	return (command);
// }

void appendInput(std::vector<std::string> &buf, std::string const &str)
{
	if (!buf.empty() && buf[0].find("\n") == std::string::npos)
		buf[0].append(str);
	else
		buf.push_back(str);
}

void User::addToInputBufferFront(std::string const &input)
{
	_userInput.insert(_userInput.begin(), input);
}

void User::addToInputBuffer(std::string msg)
{
	std::string cmd(msg);
	while (msg.find("\n") != std::string::npos)
	{
		cmd = msg.substr(0, msg.find("\n") + 1);
		msg.erase(0, msg.find("\n") + 1);
		appendInput(_userInput, cmd);
	}
	if (!msg.empty())
	{
		size_t msgSize = msg.size();
		if (msgSize == 510 && msg[msgSize - 1] != '\n')
			msg += "\n";
		appendInput(_userInput, msg);
	}
}

std::string const User::extractInput()
{
	if (_userInput.empty() || _userInput[0].find("\n") == std::string::npos)
	 	return (std::string());
	std::string const msg = _userInput[0];
	_userInput.erase(_userInput.begin());
	return (msg);
}

t_client &User::getUserInfo(){
	return _userInfo;
}

std::string const &User::getNick(){
	return _nick;
}

std::string const	&User::getUser(){
	return _user;
}

void User::setNick(std::string const &nick)
{
	_nick = nick;
}

void User::setUser(std::string const &user)
{
	_user = user;
}

bool const &User::isRegistered() const
{
	return (_isRegistered);
}

void	User::setRegistrationFlag(bool flag)
{
	_isRegistered = flag;
}

bool const	&User::isPassCorrect() const
{
	return _passFlag;
}

void	User::setPassFlag(bool flag)
{
	_passFlag = flag;
}

void User::removeUserMode(std::string const &mode)
{
	if (_userModes.empty())
		return ;
	size_t pos = _userModes.find(mode);
	if (pos != std::string::npos)
		_userModes.erase(pos, 1);
}

void User::addUserMode(std::string const &mode)
{
	if (_userModes.find(mode) == std::string::npos)
		_userModes.append(mode);
}

std::string const &User::getUserMode() const
{
	return (_userModes);
}

std::string const &User::getIP() const
{
	return (_ipAddr);
}

void User::setIP(std::string const &ip)
{
	_ipAddr = ip;
}

void User::resetPingResponseTimer()
{
	_pingResponseTimer = time(0);
}

time_t const &User::getPingResponseTimer()
{
	return (_pingResponseTimer);
}

void User::setPongResponse(std::string const &msg)
{
	_pongRespone = msg;
}

std::string const &User::getPongResponse() const
{
	return (_pongRespone);
}

std::vector<Channel *> User::getChannels() const
{
	return (_channels);
}

void User::addNewChannel(Channel *channel)
{
	_channels.push_back(channel);
}

void User::setClientInfo(t_client const &info)
{
	_userInfo = info;
}

void User::removeChannel(Channel *channel)
{
	std::vector<Channel *>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
	if (it != _channels.end())
		_channels.erase(it);
}

void User::restrictUser()
{
	_isRestricted = true;
}

bool const &User::isRestricted() const
{
	return (_isRestricted);
}