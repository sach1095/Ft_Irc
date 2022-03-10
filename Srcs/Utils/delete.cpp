#include "../../Includes/lib.hpp"

void	delete_all(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	std::stringstream ss;
	int pass = 0;
	ss << cmd[1];
	ss >> pass;
	if (cmd.size() < 2)
	{
		std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + " : Need more param for close serveur. (Password_root)\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
	else if (pass != PASS_ROOT)
	{
		std::string msg = ":server " + std::string(ERR_PASSWDMISMATCH) + " " + cmd[0] + " : Password root incorect.\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	else
	{
		data.online = false;
	}
}

void	delete_user(data<user *> &data, user *cursor)
{
	std::vector<user *>::iterator it = data.users.begin();
	std::vector<Channel*>::iterator ite = data.channels.end();
	for (std::vector<Channel*>::iterator it = data.channels.begin(); it != ite; it++)
	{
		(*it)->deleteEverywhere(cursor);
	}
	while (it != data.users.end())
	{
		if (*it == cursor)
			break ;
		it++;
	}
	delete cursor;
	data.users.erase(it);
}
