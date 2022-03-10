#include "../Includes/lib.hpp"

void	rep_1(Bot &bot)
{
	std::string msg = "Hello a toi aussi.\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}

void	rep_2(Bot &bot)
{
	std::string msg = "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
}
