#include "../../Includes/lib.hpp"

bool	exec_o(Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	if (chan->isOp(cursor))
		return SUCCESS;
	else
		chan->addOp(cursor);
	return SUCCESS;
}

bool	exec_k(Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	if (!chan->isOp(cursor))
	{
		std::string str = ":server " + std::string(ERR_USERSDONTMATCH) + " " + cmd[1] + " : You are not operator\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return FAIL;
	}
	if (chan->needPassord() == true)
		chan->setPassword(cmd[3]);
	else
	{
		chan->setneedPassword(true);
		chan->setPassword(cmd[3]);
	}
	return SUCCESS;
}

bool	exec_i(Channel *chan , user *cursor, std::vector<std::string> cmd, bool add_or_remove)
{
	if (!chan->isOp(cursor))
	{
		std::string str = ":server " + std::string(ERR_USERSDONTMATCH) + " " + cmd[1] + " : You are not operator\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return FAIL;
	}
	if (chan->getPrivate())
		return SUCCESS;
	else
	{
		chan->setPrivate(true);
	}
	return SUCCESS;
}

void	cmd_mode(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	bool add_or_remove = false;
	bool isExist = false;
	user *index;

	Channel *chan = getChan(data, cmd[1]);
	if (chan == NULL)
	{
		std::string str = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cmd[1] + " : No such channel\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
	int i = 0;
	if (cmd[2][i] == '+')
		add_or_remove = true;
	else if (cmd[2][i] == '-')
		add_or_remove = false;
	else
	{
		std::string str = ":server " + std::string(ERR_UMODEUNKNOWNFLAG) + " " + cmd[2] + " : Unknown flags\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
	i++;
	while (cmd[2][i] != '\0')
	{
		if (cmd[2][i] != 'k' || cmd[2][i] != 'i' || cmd[2][i] != 'o')
		{
			std::string str = ":server " + std::string(ERR_UMODEUNKNOWNFLAG) + " " + cmd[2] + " : Unknown flags\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		if (cmd[2][i] == 'o' && cmd.size() < 4)
		{
			std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[2] + " : to more param\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
	}

	for (size_t i = 0; cmd[2][i] != '\0'; i++)
	{
		if (cmd[2][i] != 'k')
		{
			if (exec_i(chan, cursor, cmd, add_or_remove))
				return ;
		}
		else if (cmd[2][i] != 'i')
		{
		}
		else if (cmd[2][i] != 'o')
		{
		}
	}


}
