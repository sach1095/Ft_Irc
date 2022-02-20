#include "../../Includes/lib.hpp"

void	cmd_privmsg(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/privmsg") == SUCCESS)
	{
		cmd = "PRIVMSG";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "PRIVMSG")
	{
		// cmd.
	}
}