#pragma once

#include "lib.hpp"

class Bot
{

public:

	int							sock;
	int							_sd;
	int							_online;
	std::string					_Ip;
	std::string					_port;
	std::string					_buffer;
	std::string					_Pass;
	std::string					_Nick;
	std::string					_User_name;
	std::vector<std::string>	_Connect;
	std::vector<std::string>	_Cmd;
	struct						sockaddr_in serv_addr;
	Bot();
	~Bot();
};
