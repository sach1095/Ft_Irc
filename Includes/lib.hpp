# ifndef __LIB_HPP__
#define __LIB_HPP__

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

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>

typedef struct s_serveur
{
	int					port;
	int					primary_socket;
	struct sockaddr_in	address;
	fd_set				readfds;
	std::string			password;
}t_serveur;

typedef struct s_data
{
	t_serveur serv;
}t_data;

/* parsing.cpp */
bool	init_and_pars_data(t_data *data, char **av);

/* ret_error.cpp */
bool	ret_error(std::string str);

/* connect.cpp */
bool	create_socket(t_data *data);


#endif
