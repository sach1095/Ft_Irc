#include "../../Includes/lib.hpp"

void	cmd_quit(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(5, buf.length() - 5);
	if (cmd[0] == ':')
		cmd = cmd.substr(1, cmd.length() - 1);
	buf = ":" + cursor->getNick() + "!" + cursor->getLogin() + "@" + cursor->getIp() + " QUIT :Quit: " + cmd + "\r\n";
	send(cursor->getSd(), buf.c_str(), buf.length(), 0);
}
