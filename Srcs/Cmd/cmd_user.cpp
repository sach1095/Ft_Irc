#include "../../Includes/lib.hpp"


void	cmd_user(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("/user") == SUCCESS)
	{
		cmd = "USER";
		buf = buf.substr(1, buf.length() - 1);
	}

	buf = buf.substr(5, buf.length() - 5);

	std::string user = buf.substr(0, buf.find(' '));
	cursor->setLogin(user);
	std::cout << "Test login = " << cursor->getLogin() << std::endl;

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
	std::cout << "Test realname = " << cursor->getRealName() << std::endl;
}