#include "Includes/lib.hpp"

bool	ret_error(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

void	go_connect(Bot &bot)
{
	std::string msg = bot._Pass;
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
	usleep(1000);
	msg = bot._Nick + "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
	usleep(1000);
	msg = bot._User_name + "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
	usleep(1000);
	msg = "JOIN #bot_chan\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	msg.clear();
}

void	parse_cmd(Bot &bot, std::string buf)
{
	std::cout << "buffer = " << buf << std::endl;

	if (quest_1(buf))
		rep_1(bot);
	usleep(1000);
	if (quest_2(buf))
		rep_2(bot);
	usleep(1000);
	if (quest_3(buf))
		rep_3(bot);
	usleep(1000);
	if (quest_4(buf))
		rep_4(bot);
	usleep(1000);
	if (quest_5(buf))
		rep_5(bot);
	usleep(1000);
	if (quest_6(buf))
		rep_6(bot);
	usleep(1000);
	if (quest_7(buf))
		rep_7(bot);
	usleep(1000);
	if (quest_8(bot, buf))
		rep_8(bot);
	if (quest_9(buf))
		rep_9(bot);
	usleep(1000);
	if (quest_10(buf))
		rep_10(bot);
	usleep(1000);
	if (quest_11(buf))
		rep_11(bot);
	usleep(1000);
	if (quest_12(buf))
		rep_12(bot);
	usleep(1000);
	if (quest_13(buf))
		rep_13(bot);
	usleep(1000);
	if (quest_14(bot, buf))
		rep_14(bot);
	usleep(1000);
	if (quest_15(buf))
		rep_15(bot);
	usleep(1000);
	if (quest_16(buf))
		rep_16(bot);
	usleep(1000);
	if (quest_17(buf))
		rep_17(bot);
	usleep(1000);
	if (quest_18(buf))
		rep_18(bot);
	usleep(1000);
	if (quest_19(buf))
		rep_19(bot);
	usleep(1000);
}

void	go_online(Bot &bot)
{
	char	buffer[1024] = {0};
	int		valread;
	while (bot._online)
	{
		if((valread = recv(bot.sock, buffer, 1024, 0)) <= 0){
			close(bot.sock);
			bot._online = 0;
		}
		else{
			buffer[valread] = '\0';
			if (buffer[valread - 1] != '\n')
			{
				bot._buffer = bot._buffer + buffer;
				return;
			}
			if (bot._buffer.empty())
				bot._buffer = buffer;
			else
				bot._buffer = bot._buffer + buffer;
		}
		if (bot._buffer.find('\n') != std::string::npos)
		{
			parse_cmd(bot, bot._buffer);
			bot._buffer.clear();
		}
	}
	bot._online = 0;
}

int main(int ac, char **av)
{
	Bot bot;

	if (ac > 4 || ac < 3)
		return(ret_error("Error: wrong number of arguments, use: <server_ip> <port> <password>\n"));

	bot.sock = 0;
	bot._Ip = av[1];
	std::stringstream aa(av[2]);
	aa >> bot._port;
	bot._Pass = "PASS ";
	bot._Nick = "NICK Mr_robot";
	bot._User_name = "USER bot * rob ot";
	bot._Pass = bot._Pass + av[3] + "\r\n";

	if ((bot.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return(ret_error("Socket creation error\n"));
	bot.serv_addr.sin_family = AF_INET;
	bot.serv_addr.sin_addr.s_addr = INADDR_ANY;
	bot.serv_addr.sin_port = htons(bot._port);

	if(inet_pton(AF_INET, bot._Ip.c_str(), &bot.serv_addr.sin_addr)<=0)
		return(ret_error("\nInvalid address / Address not supported\n"));
	bot.server = gethostbyname(bot._Ip.c_str());
	if (bot.server == NULL)
		ret_error(strerror(errno));

	std::memcpy((char *)bot.server->h_addr, (char *)&bot.serv_addr.sin_addr.s_addr, bot.server->h_length);

	if (connect(bot.sock, (struct sockaddr *)&bot.serv_addr, sizeof(bot.serv_addr)) == -1)
		return(ret_error("\nConnection Failed\n"));

	go_connect(bot);

	while (bot._online)
		go_online(bot);
	return 0;
}
