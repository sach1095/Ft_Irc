#include "../../Includes/lib.hpp"

bool	exec_o(data<user *> &data ,Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	user *index = getUser(cmd[3], chan);
	if (index == NULL)
	{
		std::string str = ":server " + std::string(ERR_NOSUCHNICK) + " " + cmd[3] + " :No such nick, User not on the channel.\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return FAIL;
	}
	index = getUser_from_list(cmd[3], data.users);
	if (add_or_remove == true)
	{
		if (!chan->isOp(index))
		{
			chan->addOp(index);
			std::string message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cursor->getNick() + " " + chan->getName() + " :" + cursor->getNick() +  " use +o \r\n";
			send_to_all_members(message, chan);
		}
		return SUCCESS;
	}
	else
	{
		if (chan->isOp(index))
		{
			chan->deleteOp(index);
			std::string message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cursor->getNick() + " " + chan->getName() + " :" + cursor->getNick() +  " use -o \r\n";
			send_to_all_members(message, chan);
		}
	}
	return SUCCESS;
}

bool	exec_i(Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	(void)cmd;
	if (add_or_remove == true)
	{
		if (!chan->getPrivate())
		{
			chan->setPrivate(true);
			std::string message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cursor->getNick() + " " + chan->getName() + " :" + cursor->getNick() +  " use +i \r\n";
			send_to_all_members(message, chan);
		}
		return SUCCESS;
	}
	else
	{
		if (chan->getPrivate())
		{
			chan->setPrivate(false);
			std::string message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cursor->getNick() + " " + chan->getName() + " :" + cursor->getNick() +  " use -i \r\n";
			send_to_all_members(message, chan);
		}
		return SUCCESS;
	}
	return SUCCESS;
}

bool	exec_b(Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	std::string message;
	if (cmd.size() < 4)
	{
		message = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cursor->getNick() + " :Mode :Not enough parameters\r\n";
		send(cursor->getSd(), message.c_str(), message.length(), 0);
		return FAIL;
	}
	else if (!chan->isMember(cmd[3]) && !chan->isBanned(cmd[3]))
	{
		message = ":server " + std::string(ERR_NOSUCHNICK) + " " + cmd[3] + " :No such nick\r\n";
		send(cursor->getSd(), message.c_str(), message.length(), 0);
		return FAIL;
	}
	else {
		if (add_or_remove == true && !chan->isOp(chan->getCli(cmd[3])))
		{
			chan->addBan(chan->getCli(cmd[3]));
			message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cursor->getNick() + " " + chan->getName() + " :" + cursor->getNick() +  " use +b \r\n";
			send_to_all_members(message, chan);
			return SUCCESS;
		}
		else if ( add_or_remove == false)
		{
			chan->deleteBan(cmd[3]);
			message = ":server " + std::string(RPL_CHANNELMODEIS) + " " + cursor->getNick() + " " + chan->getName() + " :" + cursor->getNick() +  " use -b \r\n";
			send_to_all_members(message, chan);
			return SUCCESS;
		}
	}
	return SUCCESS;
}

void	cmd_mode(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	bool add_or_remove = false;

	Channel *chan = getChan(data, cmd[1]);
	if (cmd.size() > 1 && cmd[1][0] == '#')
	{
		if (chan == NULL)
		{
			std::string str = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cmd[1] + " : No such channel\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		if (!chan->isOp(cursor))
		{
			std::string str = ":server " + std::string(ERR_USERSDONTMATCH) + " " + cmd[1] + " : You are not operator\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		if (cmd[2][0] == '+')
			add_or_remove = true;
		else if (cmd[2][0] == '-')
			add_or_remove = false;
		else
		{
			std::string str = ":server " + std::string(ERR_UMODEUNKNOWNFLAG) + " " + cmd[2] + " : Unknown flags\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		for (size_t i = 1; cmd[2][i] != '\0'; i++)
		{
			if (cmd[2][i] == 'o' && !(cmd.size() < 4))
			{
				if (exec_o(data, chan, cursor, cmd, add_or_remove))
					return ;
			}
			else if (cmd[2][i] == 'o' && cmd.size() < 4)
			{
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[2] + " : to more param\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
			else if (cmd[2][i] == 'i')
			{
				if (exec_i(chan, cursor, cmd, add_or_remove))
					return ;
			}
			else if (cmd[2][i] == 'b')
			{
				if (exec_b(chan, cursor, cmd, add_or_remove))
					return ;
			}
			else
			{
				std::string str = ":server " + std::string(ERR_UMODEUNKNOWNFLAG) + " " + cmd[2] + " : Unknown flags\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
		}
	}
	else
	{
		std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + " : Not enough parameters\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
}
