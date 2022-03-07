#include "../../Includes/lib.hpp"

void	cmd_invite(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	std::string msg;
	Channel *Channel_to_invite;

	if (cmd.size() < 3)
	{
		msg = ":server " + std::string(ERR_NEEDMOREPARAMS) + " invite :Not enough parameters\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd[2][0] != '#')
		cmd[2] = '#' + cmd[2];
	Channel_to_invite = getChan(data, cmd[2]);
	if (Channel_to_invite == NULL)
		return;
	if (!Channel_to_invite->isOp(cursor))
	{
		msg = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " " + cursor->getNick() + " " + Channel_to_invite->getName() + " :You're not channel operator\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	if (!Channel_to_invite->isMember(cursor))
	{
		msg = ":server " + std::string(ERR_NOTONCHANNEL) + " " + cursor->getNick() + " " + Channel_to_invite->getName() + " :You're not on that channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	if (Channel_to_invite->isMember(cmd[1]))
	{
		msg = ":server " + std::string(ERR_USERONCHANNEL) + " " + cursor->getNick() + " " + Channel_to_invite->getName() + " :is already on channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	std::vector<user *>::iterator it = data.users.begin();
	user *index;
	bool isExist = false;
	while (it != data.users.end())
	{
		index = *it;
		if (index->getNick() == cmd[1])
		{
			isExist = true;
			break;
		}
		it++;
	}
	if (!isExist)
	{
		msg = ":server " + std::string(ERR_NOSUCHNICK) + " " + Channel_to_invite->getName() + " :There was no such nickname\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	else
	{
		index->addInvitation(Channel_to_invite->getName());
		msg = ":" + cursor->getNick() + " INVITE " + cmd[1] + " " + cmd[2] + "\r\n";
		send(index->getSd(), msg.c_str(), msg.length(), 0);

		msg = ":server " + std::string(RPL_INVITING) + " nick " + index->getNick() + " " + Channel_to_invite->getName() + "\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
	}
}
