#include "../../Includes/lib.hpp"

void	cmd_nick(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	int start = cmd.length() + 1;

	std::string nick = buf.substr(start, buf.length() - (cmd.length() + 2));
	if (buf.find('\r') != buf.npos)
		nick = buf.substr(start, buf.length() - (cmd.length() + 3));

	cursor->setNick(nick);
}
