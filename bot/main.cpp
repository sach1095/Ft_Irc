#include "Includes/lib.hpp"

#define PORT 8080

bool	ret_error(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

void	go_connect(Bot &bot)
{
	std::string msg = bot._Pass + "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	sleep(500);
	msg.clear();
	msg = bot._Nick + "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	sleep(500);
	msg.clear();
	msg = bot._User_name + "\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	sleep(500);
	msg.clear();
	msg = "JOIN #bot\r\n";
	send(bot.sock , msg.c_str() , msg.size(), 0);
	sleep(500);
}

void	parse_cmd(Bot &bot, std::string buf)
{
	std::cout << "buffer = : " << buf << std::endl;

	if (quest_1(buf))
		rep_1(bot);
	else if (quest_2(buf))
		rep_2(bot);
}

void	go_online(Bot &bot)
{
	char	buffer[1024];
	int		valread;
	int		online = 1;

	while (true)
	{
		if((valread = read(bot.sock , buffer, 1024)) == 0){
			close(bot.sock);
			online = 0;
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
		parse_cmd(bot, bot._buffer);
		bot._buffer.clear();
	}
}

int main(int ac, char **av)
{
	Bot bot;
	
	if (ac > 4 || ac < 3)
		return(ret_error("Errro bad number of arguments, Need <ip_Serveur> <Port> <Password>\n"));

	bot.sock = 0;
	bot._Ip = av[1];
	bot._port = av[2];
	bot._Pass = "PASS ";
	bot._Nick = "Mr_robot";
	bot._User_name = "bot * rob ot";
	bot._Pass = bot._Pass + av[3];

	if ((bot.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return(ret_error("Socket creation error \n"));
	bot.serv_addr.sin_family = AF_INET;
	bot.serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, bot._Ip.c_str(), &bot.serv_addr.sin_addr)<=0)
		return(ret_error("\nInvalid address/ Address not supported \n"));
	if (connect(bot.sock, (struct sockaddr *)&bot.serv_addr, sizeof(bot.serv_addr)) < 0)
		return(ret_error("\nConnection Failed \n \n"));
	go_connect(bot);

	while (bot._online)
		go_online(bot);
	return 0;
}
