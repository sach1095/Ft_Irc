#pragma once

# define SUCCESS 0
# define FAIL 1

# include <iostream>
# include <memory>
# include <algorithm>
# include <array>
# include <iterator>
# include <ios>
# include <istream>
# include <iomanip>
# include <cstring>
# include <sstream>
# include <string>
# include <cctype>
# include <cstdlib>
# include <vector>

# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>
# include <netdb.h>
#include "lib.hpp"

class Bot
{

public:

	int							sock;
	int							_sd;
	int							_online;
	int							_port;
	std::string					_Ip;
	std::string					_buffer;
	std::string					_Pass;
	std::string					_Nick;
	std::string					_User_name;
	std::vector<std::string>	_Connect;
	std::vector<std::string>	_Cmd;
	struct						sockaddr_in serv_addr;
	time_t						actuel;
	std::string					to_ban;
	struct hostent *server;
	Bot();
	~Bot();
};
