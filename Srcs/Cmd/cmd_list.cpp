#include "../../Includes/lib.hpp"

void	cmd_list(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	std::string msg;
	std::string list_channel;


	if (cmd.size() == 1)
	{
		msg = ":server " + std::string(RPL_LISTSTART) + " Channel :Users Name\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		for (std::vector<Channel *>::iterator it = data.channels->begin(); it != data.channels->end(); it++)
		{
			if ((*it)->isMember(cursor))
			{
				list_channel.append(cursor->getNick() + " " + (*it)->getName() + " " + std::to_string((*it)->getMembers().size()));
				if (!(*it)->getPrivate() || (*it)->isMember(cursor))
					list_channel.append(" :" + (*it)->getTopic());
				msg = ":server " + std::string(RPL_LIST) + " " + list_channel + "\r\n";
				send(cursor->getSd(), msg.c_str(), msg.length(), 0);
			}
			list_channel.clear();
		}
		msg = ":server " + std::string(RPL_LISTEND) + " :End of /LIST\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
	}
	else
	{
		msg = ":server " + std::string(ERR_UNKNOWNCOMMAND) + " " + " :Not accepte arguments\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
	}
}
