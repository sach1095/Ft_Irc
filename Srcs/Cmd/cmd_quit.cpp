#include "../../Includes/lib.hpp"

void	cmd_quit(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/quit") == SUCCESS)
	{
		cmd = "QUIT";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "QUIT")
	{
		// cmd.
	}
}