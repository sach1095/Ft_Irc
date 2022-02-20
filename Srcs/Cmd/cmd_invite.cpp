#include "../../Includes/lib.hpp"

void	cmd_invite(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/invite") == SUCCESS)
	{
		cmd = "INVITE";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "INVITE")
	{
		// cmd.
	}
}