#include "../../Includes/lib.hpp"

void	cmd_mode(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/mode") == SUCCESS)
	{
		cmd = "MODE";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "MODE")
	{
		// cmd.
	}
}