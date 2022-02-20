#include "../../Includes/lib.hpp"

void	cmd_name(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/name") == SUCCESS)
	{
		cmd = "NAME";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "NAME")
	{
		// cmd.
	}
}