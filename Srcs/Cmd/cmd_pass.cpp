#include "../../Includes/lib.hpp"

void	cmd_pass(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	if (cmd.compare("PASS") == SUCCESS)
	{
		int start = cmd.length() + 1;

		/*
		* Le client nc envoie la chaine avec saut a la ligne et un retour chariot
		* Donc on fait -2.
		*/
		std::string pass = buf.substr(start, buf.length() - (cmd.length() + 2));
		/*
		* Le client limeChat lui envoie la chaine avec un tab, un saut a la ligne
		* et un retour chariot.
		* Donc on fait -3.
		*/
		if (buf.find('\r') != buf.npos)
			pass = buf.substr(start, buf.length() - (cmd.length() + 3));

		if (pass.compare(data.password) == SUCCESS)
		{
			cursor->setAccept(true);
			std::string str = ":server " + std::string(RPL_WELCOME) + "\r\n";
			send(cursor->getSd(), str.c_str(), str.length(), 0);
			return ;
		}
		else
			throw exception_class::pass_mismatch();
	}
	else
		throw exception_class::pass_param();

}
