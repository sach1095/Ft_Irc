#include "../../Includes/lib.hpp"

static bool	exec_o(data<user *> &data ,Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	user *index = getUser(cmd[3], chan);
	if (index == NULL)
	{
		std::string str = ":server " + std::string(ERR_NOSUCHNICK) + " " + cmd[3] + ": No such nick, User not on the channel.\r\n";
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

static bool	exec_i(Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
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

void	cmd_mode(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	bool add_or_remove = false;

	Channel *chan = getChan(data, cmd[1]);
	if (cmd.size() > 1 && cmd[1][0] == '#')
	{
		if (chan == NULL)
		{
			std::string str = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cmd[1] + ": No such channel\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		if (!chan->isOp(cursor))
		{
			std::string str = ":server " + std::string(ERR_USERSDONTMATCH) + " " + cmd[1] + ": You are not operator\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		if (cmd[2][0] == '+')
			add_or_remove = true;
		else if (cmd[2][0] == '-')
			add_or_remove = false;
		else
		{
			std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": Unknown flag\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		for (size_t i = 1; cmd[2][i] != '\0'; i++)
		{
			if (cmd[2][i] == 'o' && cmd.size() == 4){
				if (exec_o(data, chan, cursor, cmd, add_or_remove))
					return ;
			}
			else if (cmd[2][i] == 'o' && cmd.size() > 4){
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": to more param\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
			else if (cmd[2][i] == 'o' && cmd.size() <= 3){
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": need more param\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
			else if (cmd[2][i] == 'i' && cmd.size() == 3){
				if (exec_i(chan, cursor, cmd, add_or_remove))
					return ;
			}
			else if (cmd[2][i] == 'i'){
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": to more param\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
			else if (cmd[2][i] == 'i' && cmd.size() > 3){
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": to more param\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
			else if (cmd[2][i] == 'i' && cmd.size() <= 2){
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": need more param\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
			else{
				std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": Unknown flag\r\n";
				send(cursor->getSd(), str.c_str(), str.length(), 0);
				return ;
			}
		}
	}
	else
	{
		std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": Not enough parameters\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
}
