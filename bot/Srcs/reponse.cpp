#include "../Includes/lib.hpp"

void	rep_1(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan :Hello.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_2(Bot &bot)
{
	std::string msg = "PRIVMSG #bot_chan :ça va et toi ?\r\n";
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
	aa << "PRIVMSG #bot_chan : la il est " << ltm->tm_hour << ":" << ltm->tm_min <<  " et " << ltm->tm_sec << " secondes excatement.\r\n";
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
	msg = "KICK #bot_chan " + bot.to_ban + " :Pas de gros mots ici!\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	bot.to_ban.clear();
}

void	rep_9(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : quand c'est trop, c'est tropico ;)\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_10(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : sur ton nez ^^.\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_11(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : bien sur au lit.\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_12(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : pas de chocola.\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_13(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : et des NANA da dadirlada\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_14(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : hooo une marseillaise !\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
	usleep(1000);
	msg = "KICK #bot_chan " + bot.to_ban + " : Ici c'est PARISSSSS !!!\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	bot.to_ban.clear();
	msg.clear();
	msg = "PRIVMSG #bot_chan : PARISSSS est MAGIQUEEEE !!!\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
	usleep(1000);
}

void	rep_15(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : oh mon jojo <3\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_16(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : entre la peste et le colera ? aucune envie delire ses profiteur.\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_17(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : j'ai pas de carte d'identité lol\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_18(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : tabarnak!\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_19(Bot &bot)
{
	bot.actuel = time(0);
	tm *ltm = localtime(&bot.actuel);
	std::stringstream aa;

	aa << "PRIVMSG #bot_chan : ... Con, vive les bretonsss ahahah!\r\n";
	std::string msg = aa.str();
	send(bot.sock , msg.c_str() , msg.size(), 0);
}
