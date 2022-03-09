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

# include "code_error.hpp"
# include "exception_class.hpp"
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>

# include "user_class.hpp"
# include "data_class.hpp"
# include "channel_class.hpp"

/*
* Cmd
*/
void	cmd_process(data<user *> &data);

void	cmd_invite(data<user *> &data , user *cursor, std::string buf);
void	cmd_join(data<user *> &data , user *cursor, std::string buf);
void	cmd_kick(data<user *> &data , user *cursor, std::string buf);
void	cmd_list(data<user *> &data , user *cursor, std::string buf);
void	cmd_mode(data<user *> &data , user *cursor, std::string buf);
void	cmd_nick(data<user *> &data , user *cursor, std::string buf);
void	cmd_notice(data<user *> &data , user *cursor, std::string buf);
void	cmd_pass(data<user *> &data , user *cursor, std::string buf);
void	cmd_privmsg(data<user *> &data , user *cursor, std::string buf);
void	cmd_user(data<user *> &data , user *cursor, std::string buf);


/*
* Serv
*/

/* connect.cpp */
bool	create_socket(data<user *> &data);
bool	start_online(data<user *>  &data);

/* creat_socket.cpp */
bool	create_socket(data<user *> &data);


/*
* Utils
*/

/* delete.cpp */
void	delete_user(data<user *> &data, user *cursor);

/* parsing.cpp */
bool						pars_data(data<user *> &data, char **av);
std::vector<std::string>	parse_cmd(std::string buf);
std::vector<std::string>	parse_msg(std::string buf);
/* ret_error.cpp */
bool	ret_error(std::string str);

/* user.cpp */
/* all command class user and -> */
user*	getUser(std::string name, Channel *channel);
user*	getUser_from_list(std::string name, std::vector<user *> users);
bool	checkUser(user *cli, Channel *chan);
bool	checkUserStr(std::string cli, Channel *chan);

/* channel.cpp */
/* all command class channel and -> */
Channel*	getChan(data<user *> &data, std::string name);
void		send_to_all_members(std::string message, Channel *channel);
void		send_msg_to_all_members(std::string message, Channel *channel, user *sender);
