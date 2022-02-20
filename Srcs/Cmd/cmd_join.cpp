#include "../../Includes/lib.hpp"

void	cmd_join(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/join") == SUCCESS)
	{
		cmd = "JOIN";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "JOIN")
	{
		// cmd.
	}
}