#include "../../Includes/lib.hpp"

Channel::Channel(std::string name): _name(name), _Private(false)
{
	_topic = "No Topic";
}

Channel::Channel(std::string name, std::string topic):_name(name), _topic(topic), _Private(false)
{
}

Channel::~Channel()
{
	_op.clear();
	_members.clear();
}

std::string	Channel::getName() const
{
	return _name;
}

std::vector<user*>	Channel::getMembers()
{
	return _members;
}

std::string Channel::getTopic() const
{
	return _topic;
}

bool Channel::getPrivate() const
{
	return _Private;
}

bool Channel::isPrivate() const
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

void		Channel::addOp(user *cli)
{
	if (isMember(cli))
	{
		_op.push_back(cli);
	}
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

bool		Channel::isOp(user *cli) const
{
	for (std::vector<user*>::const_iterator it = _op.begin(); it != _op.end(); it++)
	{
		user *c = *it;
		if (c->getNick() == cli->getNick())
			return true;
	}
	return false;
}

void		Channel::deleteUser(user *cli)
{
	for (std::vector<user *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
		if (*it == cli)
		{
			_members.erase(it);
			return ;
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
			return ;
		}
	}
}

bool		Channel::isMember(std::string cli) const
{
	for (std::vector<user*>::const_iterator it = _members.begin(); it != _members.end(); it++)
	{
		if ((*it)->getNick() == cli)
			return true;
	}
	return false;
}

void		Channel::deleteEverywhere(user *cursor)
{
	deleteOp(cursor);
	deleteUser(cursor);
}

Channel*	getChan(data<user *> &data, std::string name)
{
	for (std::vector<Channel *>::iterator it = data.channels.begin(); it != data.channels.end(); it++)
	{
		Channel *index = *it;
		if (index->getName() == name)
			return index;
	}
	return NULL;
}

void	send_to_all_members(std::string message, Channel *channel)
{
	user *c = NULL;
	std::vector<user*> members = channel->getMembers();
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

void	send_msg_to_all_members(std::string message, Channel *channel, user *sender)
{
	user *c = NULL;
	std::vector<user*> members = channel->getMembers();
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (sender->getNick() != c->getNick())
			send(c->getSd(), message.c_str(), message.length(), 0);
	}
}

static bool insave(user *sender, std::vector<user *> save)
{
	for (std::vector<user *>::iterator it = save.begin(); it != save.end(); it++)
	{
		user *search = *it;
		if (search->getNick() == sender->getNick())
			return true;
	}
	return false;
}

void	send_msg_to_all_channels(data<user *> &data, std::string message, user *sender)
{
	std::vector<user *> save;
	save.push_back(sender);

	for (std::vector<Channel *>::iterator it = data.channels.begin(); it != data.channels.end(); it++)
	{
		Channel *index = *it;
		if (index->isMember(sender->getNick()))
		{
			std::vector<user *> cls = index->getMembers();
			for (std::vector<user *>::iterator it2 = cls.begin(); it2 != cls.end(); it2++)
			{
				user *dest = *it2;
				if (!(insave(dest, save)))
				{
					send(dest->getSd(), message.c_str(), message.length(), 0);
					save.push_back(dest);
				}
			}
			index->deleteEverywhere(sender);
		}
	}
}

bool	Channel::OpisEmpty()
{
	if (_op.size() == 0)
		return true;
	return false;
}

bool	Channel::MemberisEmpty()
{
	if (_members.size() == 0)
		return true;
	return false;
}

void	Channel::setNewOp()
{
	if (_members.size() != 0)
	{
		user *member = _members[0];
		addOp(member);
	}
}

void	delete_chan(data<user *> &data, Channel *chan)
{
	for (std::vector<Channel *>::iterator it = data.channels.begin(); it != data.channels.end(); it++)
	{
		if ((*it)->getName() == chan->getName())
		{
			delete *it;
			data.channels.erase(it);
			return ;
		}
	}
}
