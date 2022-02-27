#include "../../Includes/lib.hpp"

Channel::Channel(std::string name): _name(name), _Private(false)
{
	_topic = "Topic not set";
}

Channel::Channel(std::string name, std::string topic):_name(name), _topic(topic), _Private(false)
{
}

Channel::Channel(std::string name, std::string topic, std::string password):_name(name), _topic(topic) ,_password(password), _Private(false)
{
}

Channel::~Channel()
{
}

std::string	Channel::getName() const
{
	return _name;
}

std::vector<user*>	Channel::getMembers()
{
	return _members;
}

std::string	Channel::getPassword() const
{
	return _password;
}

std::string Channel::getTopic() const
{
	return _topic;
}

bool Channel::getPrivate() const
{
	return _Private;
}


user *Channel::getCli(std::string cli)
{
	for (std::vector<user*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli)
			return c;
	}
	return NULL;
}

void		Channel::setName(std::string name)
{
	_name = name;
}

void		Channel::setPassword(std::string password)
{
	_password = password;
}

void		Channel::setTopic(std::string topic)
{
	_topic = topic;
}

void	Channel::setPrivate(bool b)
{
	_Private = b;
}

void		Channel::addUser(user *cli)
{
	_members.push_back(cli);
}

void		Channel::addInvitation(user *cli)
{
	_invited.push_back(cli);
}

void		Channel::addOp(user *cli)
{
	if (isMember(cli))
	{
		_op.push_back(cli);
	}
}

void		Channel::addBan(user *cli)
{
	if (isMember(cli))
	{
		_banned.push_back(cli);
	}
}

void		Channel::deleteUser(user *cli)
{
	for (std::vector<user *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (*it == cli)
		{
			_members.erase(it);
			break ;
		}
	}
}

void		Channel::deleteOp(user *cli)
{
	for (std::vector<user *>::iterator it = _op.begin(); it != _op.end(); it++)
	{
		if (*it == cli)
		{
			_op.erase(it);
			break ;
		}
	}
}

void		Channel::deleteBan(std::string cli)
{
	for (std::vector<user *>::iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		if ((*it)->getNick() == cli)
		{
			_banned.erase(it);
			break ;
		}
	}
}

void		Channel::deleteBan(std::string cli)
{
	for (std::vector<user *>::iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		if ((*it)->getNick() == cli)
		{
			_banned.erase(it);
			break ;
		}
	}
}

bool		Channel::isInvited(user *cli) const
{
	for (std::vector<user*>::const_iterator it = _invited.begin(); it != _invited.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		Channel::isInvited(std::string cli) const
{
	for (std::vector<user*>::const_iterator it = _invited.begin(); it != _invited.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}

bool		Channel::isMember(user *cli) const
{
	for (std::vector<user*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		Channel::isMember(std::string cli) const
{
	for (std::vector<user*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}

bool		Channel::isBanned(user *cli) const
{
	for (std::vector<user*>::const_iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

bool		Channel::isBanned(std::string cli) const
{
	for (std::vector<user*>::const_iterator it = _banned.begin(); it != _banned.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli)
			return true;
	}
	return false;
}
