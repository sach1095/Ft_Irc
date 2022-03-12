#include "../../Includes/lib.hpp"

void	cmd_quit(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	std::string msg;
	if(cmd.size() == 1)
		cmd.push_back(" left the serveur.");
	if (cmd[1][0] == ':')
		cmd[1] = &cmd[1][1];
	if (cmd.size() > 2 && cmd[2][0] == ':')
	{
		cmd[2] = &cmd[2][1];
		for (size_t i = 3; i < cmd.size(); i++)
			cmd[2] = cmd[2] + " " + cmd[i];
	}
	msg = ":" + cursor->getNick() + "!" + cursor->getLogin() + "@" + cursor->getIp() + " QUIT :Quit: " + cmd[1] + "\r\n";
	send_msg_to_all_channels(data, msg, cursor);
}
