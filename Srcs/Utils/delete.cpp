#include "../../Includes/lib.hpp"

void	delete_all(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	std::stringstream ss;
	if (cmd.size() < 2)
	{
		std::string str = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + " : Need more param to close the server. (Password_root)\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}
	int pass = 0;
	ss << cmd[1];
	ss >> pass;
	if (pass != PASS_ROOT)
	{
		std::string msg = ":server " + std::string(ERR_PASSWDMISMATCH) + " " + cmd[0] + " : Root password is incorect.\r\n";
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
		if ((*it)->isMember(cursor))
		{
			(*it)->deleteEverywhere(cursor);
			if ((*it)->OpisEmpty() && !(*it)->MemberisEmpty())
				(*it)->setNewOp();
			else if ((*it)->MemberisEmpty())
				delete_chan(data, *it);
			break;
		}
	}
	cursor->setIdentfy(false);
	while (it != data.users.end())
	{
		if (*it == cursor)
		{
			delete cursor;
			data.users.erase(it);
			return ;
		}
		it++;
	}
}
