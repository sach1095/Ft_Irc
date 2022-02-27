#include "../../Includes/lib.hpp"

static std::vector<std::string>	parse_notice(std::string buf)
{
	std::vector<std::string> cmd;

	while (buf.back() == '\n' || buf.back() == '\r')
		buf.pop_back();
	cmd.push_back(buf.substr(0, buf.find(' ')));
	buf = buf.substr(6 + 1, buf.length() - 6);
	cmd.push_back(buf.substr(0, buf.find(' ')));
	std::string to_send = buf.substr(0, buf.find(' '));
	buf = buf.substr(to_send.length(), buf.length() - to_send.length());
	std::string cmd_Msg = buf.substr(1, buf.find('\0'));
	if (cmd_Msg[0] == ':')
		cmd_Msg = buf.substr(2, buf.find('\0'));
	cmd.push_back(cmd_Msg);
	return cmd;
}

void	cmd_notice(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_notice(buf);

	
	if (cmd.size() < 3)
		return ;
	if (cmd[1][0] == '$')
	{
		return ;
	}
	if (cmd[1][0] == '#')
	{
		// privmsg pour channel
		std::string cmd_Channel = buf.substr(0, buf.find(' '));
		std::cout << "test Channel = " << cmd_Channel << std::endl;
		return ;
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
