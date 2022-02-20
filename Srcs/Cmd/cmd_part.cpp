#include "../../Includes/lib.hpp"

void	cmd_part(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/part") == SUCCESS)
	{
		cmd = "PART";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (cmd == "PART")
	{
		// cmd.
	}
}