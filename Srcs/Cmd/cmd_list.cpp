#include "../../Includes/lib.hpp"

void	cmd_list(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/list") == SUCCESS)
	{
		cmd = "LIST";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "LIST")
	{
		// cmd.
	}
}