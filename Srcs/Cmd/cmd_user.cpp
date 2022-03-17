#include "../../Includes/lib.hpp"

void	cmd_user(data<user *> &data , user *cursor, std::string buf)
{
	(void)data;
	std::string cmd = buf.substr(0, buf.find(' '));

	buf = buf.substr(5, buf.length() - 5);

	std::string user = buf.substr(0, buf.find(' '));
	cursor->setLogin(user);

	std::string realname;
	if (buf.find('*') != buf.npos)
	{
		realname = buf.substr(buf.find('*') + 2, buf.length() - buf.find('*') + 2);
		if (realname[0] == ':')
			realname = realname.substr(1, realname.length() - 1);
		if (realname.find('\r') != buf.npos)
			realname = realname.substr(0, realname.length() - 2);
		else
			realname.pop_back();
	}
	cursor->setRealName(realname);
	if (!cursor->getIdentify())
	{
		cursor->setIdentfy(true);
		std::string msg = ":server " + std::string(RPL_WELCOME) + "	:Welcome " + cursor->getNick() + " !\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		msg = ":server " + std::string(RPL_YOURHOST) + " :Your host is ircserv , running version 2.0\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		msg = ":server " + std::string(RPL_CREATED) + ":This server was created 13/02/2022-13:05\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		msg = ":server " + std::string(RPL_MYINFO) + " : ircserv 2.0 0 0\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		std::cout << "test = " << cursor->getNick() << std::endl;
	}
}
