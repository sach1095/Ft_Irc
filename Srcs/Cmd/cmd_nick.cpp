#include "../../Includes/lib.hpp"

void	cmd_nick(data<user *> &data , user *cursor, std::string buf)
{
	buf.erase(remove(buf.begin(), buf.end(), '\r'), buf.end());
	std::vector<std::string> cmd;
	std::stringstream ss(buf);
	std::string line;
	std::string msg;
	bool first = false;
	if (buf.find('\n') != std::string::npos)
	{
		while (std::getline(ss, line, '\n'))
		{
			if (first == false)
				cmd.push_back(line + " ");
			else
				cmd.push_back(line);
			first = true;
		}
	}
	buf.clear();
	for (size_t i = 0; i < cmd.size(); i++)
		buf = buf + cmd[i];
	cmd.clear();
	cmd = parse_cmd(buf);
	if (cmd.size() < 2)
	{
		msg = ":server " + std::string(ERR_NONICKNAMEGIVEN) + "nick: No nickname given\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (getUser_from_list(cmd[1], data.users))
	{
		msg = ":server " + std::string(ERR_NICKNAMEINUSE) + "nick: Nickname in use\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	cursor->setNick(cmd[1]);
	if (cmd.size() > 2)
	{
		if (cmd[3].compare("USER"))
		{
			for (size_t i = 3; i < cmd.size(); i++)
				msg = msg + " " + cmd[i];
			cmd_user(data, cursor, msg);
		}
	}
}
