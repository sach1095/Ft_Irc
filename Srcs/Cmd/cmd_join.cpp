#include "../../Includes/lib.hpp"

bool	checkExisteBefor(user *cli, Channel *chan)
{
	std::vector<user *> members = chan->getMembers();
	user *index;
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		index = *it;
		if (index->getSd() == cli->getSd())
			return true;
	}
	return false;
}

std::string	listClients(Channel *chan_cmd)
{
	std::string liste;
	std::vector<user*> members = chan_cmd->getMembers();
	user *index;
	for (std::vector<user *>::iterator it = members.begin(); it != members.end(); it++)
	{
		index = *it;
		if (chan_cmd->isOp(index))
			liste += "@";
		liste += index->getNick() + " ";
	}
	return liste;
}

void	cmd_join(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_msg(buf);
	Channel *chan_cmd = NULL;
	std::string msg;
	bool first_time = false;

	if ((cmd.size() < 2))
	{
		msg = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + " : Not enough parameters\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd[1][0] != '#')
		cmd[1] = '#' + cmd[1];
	// rajouter une fonction to_upper pour mettre le nom des channel en minuscule;
	if (chan_cmd == NULL && cmd.size() == 2)
		data.channels.push_back(new Channel(cmd[1]));
	else if (!getChan(data, cmd[1]))
		data.channels.push_back(new Channel(cmd[1], cmd[2]));
	chan_cmd = getChan(data, cmd[1]);
	if (chan_cmd->isPrivate())
	{
		if (!cursor->isInvited(chan_cmd->getName()))
		{
			msg = ":server " + std::string(ERR_INVITEONLYCHAN) + " " + cmd[1] + " :Cannot join channel, your are not invited\r\n";
			send(cursor->getSd(), msg.c_str(), msg.length(), 0);
			return;
		}
	}
	if (chan_cmd->isMember(cursor))
	{
		msg = ":server " + std::string(ERR_USERONCHANNEL) + " " + cursor->getNick() + " " + cursor->getNick() + " :is already on channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	else if (!checkExisteBefor(cursor, chan_cmd))
	{
		chan_cmd->addUser(cursor);
		if (chan_cmd->getMembers().size() == 1 || cursor->getNick() == "Mr_robot")
			chan_cmd->addOp(cursor);
		first_time = true;
	}
	msg = ":" + cursor->getNick() + "!" + cursor->getLogin() + "@" + cursor->getIp() + " JOIN " + cmd[1] + "\r\n";
	send_to_all_members(msg, chan_cmd);
	if (first_time == true)
	{
		msg = ":server " + std::string(RPL_TOPIC) + " " + cursor->getNick() + " " + cmd[1] + " :" + chan_cmd->getTopic() + "\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		std::vector<user*> members = chan_cmd->getMembers();
		for (std::vector<user*>::iterator it =  members.begin(); it != members.end(); it++)
		{
			msg = ":server " + std::string(RPL_NAMREPLY) + " " + (*it)->getNick() + " = " + chan_cmd->getName() + " :" + listClients(chan_cmd) + "\r\n";
			send((*it)->getSd(), msg.c_str(), msg.length(), 0);
			msg = ":server " + std::string(RPL_ENDOFNAMES) + " " + chan_cmd->getName() + " :End of NAMES list\r\n";
			send((*it)->getSd(), msg.c_str(), msg.length(), 0);
		}
	}
	return ;
}
