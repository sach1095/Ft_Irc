#include "../../Includes/lib.hpp"

void	cmd_privmsg(data<user *> &data , user *cursor, std::string buf)
{
	std::cout << "debug in PRIVMSG " << std::endl;
	std::string cmd = buf.substr(0, buf.find(' '));

	buf = buf.substr(cmd.length(), buf.length() - cmd.length());
	if (buf.find(';') != buf.npos)
	{
		std::string str = ":server " + std::string(ERR_NOTEXTTOSEND) + " " + cmd + " :No text to send\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
	}
	if (buf[0] == '#' || buf[0] == '$')
	{
		std::string str = ":server " + std::string(ERR_UNKNOWNCOMMAND) + " " + cmd + " :Command non gere\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
		return ;
	}

}
