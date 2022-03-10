#include "../../Includes/lib.hpp"

void	cmd_kick(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_cmd(buf);
	std::string msg;
	Channel *chan = getChan(data, cmd[1]);

	if (chan == NULL)
	{
		msg = ":server " + std::string(ERR_NOSUCHCHANNEL) + " " + cmd[1] + ": No such channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (cmd[2].empty())
	{
		msg = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cmd[0] + ": Not enough parameters\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (!checkUser(cursor, chan))
	{
		msg = ":server " + std::string(ERR_NOTONCHANNEL) + " " + cmd[1] + ": You're not on that channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (!chan->isOp(cursor))
	{
		msg = ":server " + std::string(ERR_CHANOPRIVSNEEDED) + " kick: You're not channel operator\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (!checkUserStr(cmd[2], chan))
	{
		msg = ":server " + std::string(ERR_USERNOTINCHANNEL) + " " + cmd[2] + " " + cmd[1] + ": They aren't on that channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (cmd[3][0] != ':')
		cmd[3] = ':' + cmd[3];
	for (size_t i = 3; i < cmd.size(); i++)
		 msg = msg + cmd[i] + " ";
	msg = ":" + cursor->getNick() + " KICK " + cmd[1] + " " + cmd[2] + " " + msg + "\r\n";
	send_to_all_members(msg, chan);
	chan->deleteUser(getUser(cmd[2], chan));
}
