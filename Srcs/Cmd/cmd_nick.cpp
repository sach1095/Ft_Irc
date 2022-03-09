#include "../../Includes/lib.hpp"

void	cmd_nick(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_msg(buf);
	std::string msg;
	if (cmd.size() < 2)
	{
		msg = ":server " + std::string(ERR_NONICKNAMEGIVEN) + " nick: No nickname given\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	cursor->setNick(cmd[1]);
	std::cout << "test nick = " << cursor->getNick() << std::endl;
	if (cmd.size() > 2)
	{
		if (cmd[3].compare("USER"))
		{
			for (size_t i = 3; i < cmd.size(); i++)
				msg = msg + cmd[i];
			std::cout << "test msg = " << msg << std::endl;
			cmd_user(data, cursor, msg);
		}
	}
}
