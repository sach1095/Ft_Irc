#include "../Includes/lib.hpp"

void	rep_1(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan :Hello a toi aussi.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_2(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan :ca va et toi.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_3(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan : WAZAAAAAAA !!!!!.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_4(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan : bof rien de special, je tchate tranquille.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_5(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan : vsccodee la baseee, mais vim est puissant si tu le maitrisse bien.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_6(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;
	aa << "PRIVMSG #bot_chan : la il est " << ltm->tm_hour << ":" << ltm->tm_min <<  " et " << ltm->tm_sec << " excatement.\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_7(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : nous somme le " << ltm->tm_mday << "/0" << ltm->tm_mon << " de l'annee " << (ltm->tm_year + 1900) << " autre chose ?\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_8(Bot &bot)
{
	std::stringstream aa;
	aa << "PRIVMSG #bot_chan : c'est pas bien les gros mots.\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
	usleep(1000);
	msg = "KICK #bot_chan " + bot.to_ban + "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	bot.to_ban.clear();
}
