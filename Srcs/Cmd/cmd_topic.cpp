#include "../../Includes/lib.hpp"

void	cmd_topic(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_msg(buf);

	std::string msg;
	Channel *chan = NULL;
	if (cmd.size() < 2)
	{
		msg = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": Not enough parameters\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (cmd[1][0] != '#')
		cmd[1] = '#' + cmd[1];
	chan = getChan(data, cmd[1]);
	if (chan != NULL)
	{
		if (!chan->isMember(cursor))
		{
			msg = ":server " + std::string(ERR_NOTONCHANNEL) + " " + cursor->getNick() + " " + chan->getName() + ": You're not on that channel\r\n";
			send(cursor->getSd(), msg.c_str(), msg.length(), 0);
			return ;
		}
		else if (cmd.size() == 2)
		{
			msg = ":server " + std::string(RPL_TOPIC) + " " + cursor->getNick() + " " + chan->getName() + " :" + chan->getTopic() + "\r\n";
			send(cursor->getSd(), msg.c_str(), msg.length(), 0);
			return ;
		}
		else if (!chan->isOp(cursor))
		{
			msg = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cursor->getNick() + " " + chan->getName() + ": You're not channel operator\r\n";
			send(cursor->getSd(), msg.c_str(), msg.length(), 0);
			return;
		}
		else
		{
			if (cmd[2].front() == ':')
				chan->setTopic(&cmd[2][1]);
			else
				chan->setTopic(cmd[2]);
		}
	}
	else
	{
		msg = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cursor->getNick() + " " + chan->getName() + ": No such channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
}
