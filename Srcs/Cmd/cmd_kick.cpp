#include "../../Includes/lib.hpp"

void	cmd_kick(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/kick") == SUCCESS)
	{
		cmd = "KICK";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "KICK")
	{
		// cmd.
	}
}