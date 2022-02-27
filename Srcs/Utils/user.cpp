#include "../../Includes/lib.hpp"

user::user(int sd, sockaddr_in address): _sd(sd), _address(address), _access(false)
{
}

user::~user()
{
}

std::string	user::getNick() const
{
	return _nick;
}

std::string	user::getLogin() const
{
	return _login;
}

std::string	user::getRealName() const
{
	return _realName;
}

bool		user::getAccept() const
{
	return _access;
}

void	user::setAccept(bool integer)
{
	_access = integer;
}

std::string	user::getBuffer() const
{
	return _buffer;
}

int			user::getSd() const
{
	return _sd;
}

sockaddr_in	user::getAddress() const
{
	return _address;
}

void	user::setNick(std::string nick)
{
	_nick = nick;
}

void	user::setLogin(std::string login)
{
	_login = login;
}

void	user::setRealName(std::string realName)
{
	_realName = realName;
}

void	user::setBuffer(std::string buffer)
{
	_buffer = buffer;
}

void	user::cleanBuffer()
{
	_buffer.clear();
}

void	user::setSd(int sd)
{
	_sd = sd;
}

void	user::setAddr(sockaddr_in address)
{
	_address = address;
}

std::string	user::getIp() const
{
	std::string ip = inet_ntoa(_address.sin_addr);
	return ip;
}

user*	getUser(std::string name, Channel *channel)
{
	user *c;
	std::vector<user*> members = channel->getMembers();
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getNick() == name)
			return c;
	}
	return NULL;
}

bool	checkUser(user *cli, Channel *channel)
{
	std::vector<user *> members = channel->getMembers();
	user *c;
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getSd() == cli->getSd())
			return true;
	}
	return false;
}

bool	checkUserStr(std::string cli, Channel *channel)
{
	std::vector<user *> members = channel->getMembers();
	user *c;
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}

void		user::addInvitation(std::string name_chan)
{
	_invited.push_back(name_chan);
}

bool		user::isInvited(std::string cli) const
{
	for (std::vector<std::string>::const_iterator it = _invited.begin(); it != _invited.end(); it++)
	{
		std::string cursor = *it;
		if (cli.compare(cursor))
			return true;
	}
	return false;
}
