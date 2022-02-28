#include "../../Includes/lib.hpp"

void	cmd_notice(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_msg(buf);


	if (cmd.size() < 3)
		return ;
	if (cmd[1][0] == '$')
	{
		return ;
	}
	if (cmd[1][0] == '#')
	{
		Channel *chan = getChan(data, cmd[1]);
		if (chan == NULL)
			return ;
		std::string msg = ":" + cursor->getNick() + " NOTICE " + cmd[1] + " :" + cmd[2] + "\r\n";
		send_to_all_members(msg, chan);
	}
	else
	{
		user *index;
		std::vector<user *>::iterator it = data.users.begin();
		while ( it != data.users.end())
		{
			index = *it;
			if (index->getNick() == cmd[1])
				break ;
			it++;
		}
		if (it == data.users.end())
			return ;
		else
		{
			std::string tmp = ":" + cursor->getNick() + " NOTICE " + cmd[1] + " :" + cmd[2] + "\r\n";
			send(index->getSd(), tmp.c_str(), tmp.length(), 0);
		}
	}
}
