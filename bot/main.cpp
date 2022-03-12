#include "Includes/lib.hpp"

bool	ret_error(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

void	go_connect(Bot &bot)
{
	std::string msg = bot._Pass;
	std::cout << "debug pass = " << bot._Pass << std::endl;
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
	std::cout << "buffer = : " << buf << std::endl;

	if (quest_1(buf))
		rep_1(bot);
	else if (quest_2(buf))
		rep_2(bot);
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
		return(ret_error("Errro bad number of arguments, Need <ip_Serveur> <Port> <Password>\n"));

	bot.sock = 0;
	bot._Ip = av[1];
	std::stringstream aa(av[2]);
	aa >> bot._port;
	bot._Pass = "PASS ";
	bot._Nick = "NICK Mr_robot";
	bot._User_name = "USER bot * rob ot";
	bot._Pass = bot._Pass + av[3] + "\r\n";

	if ((bot.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return(ret_error("Socket creation error \n"));
	bot.serv_addr.sin_family = AF_INET;
	bot.serv_addr.sin_addr.s_addr = INADDR_ANY;
	bot.serv_addr.sin_port = htons(bot._port);

	if(inet_pton(AF_INET, bot._Ip.c_str(), &bot.serv_addr.sin_addr)<=0)
		return(ret_error("\nInvalid address/ Address not supported \n"));
	bot.server = gethostbyname(bot._Ip.c_str());
	if (bot.server == NULL)
		ret_error(strerror(errno));


	std::memcpy((char *)bot.server->h_addr, (char *)&bot.serv_addr.sin_addr.s_addr, bot.server->h_length);

	if (connect(bot.sock, (struct sockaddr *)&bot.serv_addr, sizeof(bot.serv_addr)) == -1)
		return(ret_error("\nConnection Failed \n"));

	go_connect(bot);

	while (bot._online)
		go_online(bot);
	return 0;
}
