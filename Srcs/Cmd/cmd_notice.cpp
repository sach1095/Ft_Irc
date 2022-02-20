#include "../../Includes/lib.hpp"

void	cmd_notice(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/notice") == SUCCESS)
	{
		cmd = "NOTICE";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "NOTICE")
	{
		// cmd.
	}
}