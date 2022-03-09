#include "../../Includes/lib.hpp"

void	cmd_privmsg(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_msg(buf);

	if (cmd.size() < 3)
	{
		std::string str = ":server " + std::string(ERR_NOTEXTTOSEND) + " " + cmd[0] + " :No text to send\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
	if (cmd[1][0] == '$')
	{
		std::string str = ":server " + std::string(ERR_UNKNOWNCOMMAND) + " " + cmd[0] + " :Command non gere\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
	if (cmd[1][0] == '#')
	{
		Channel *chan = getChan(data, cmd[1]);
		if (chan == NULL) {
			std::cout << "OUPS" << std::endl;
			return ;
		}
		std::string msg = ":" + cursor->getNick() + " PRIVMSG " + cmd[1] + " :" + cmd[2] + "\r\n";
		send_msg_to_all_members(msg, chan, cursor);
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
		{
			std::string tmp = ":server " + std::string(ERR_NOSUCHNICK) + " " + cmd[1] + " :Nick dest dont existe\r\n";
			send(cursor->getSd(), tmp.c_str(), tmp.length(), 0);
			return ;
		}
		else
		{
			std::string tmp = ":" + cursor->getNick() + " PRIVMSG " + cmd[1] + " :" + cmd[2] + "\r\n";
			send(index->getSd(), tmp.c_str(), tmp.length(), 0);
		}
	}
}
