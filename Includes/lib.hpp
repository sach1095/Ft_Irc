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

class user
{
	private:
		std::string	_nick;
		std::string	_login;
		std::string	_realName;
		int			_sd;
		struct sockaddr_in	_address;
		std::string	_buffer;
		user();
		user(user const& other);
		user operator=(user const& other);

	public:

		user(int sd, sockaddr_in address);
		~user();
		std::string	getNick() const;
		std::string	getLogin() const;
		std::string	getRealName() const;
		std::string	getIp() const;
		std::string getBuffer() const;
		sockaddr_in	getAddress() const;
		int			getSd() const;
		bool		getAccept() const;
		void		setNick(std::string nick);
		void		setLogin(std::string login);
		void		setRealName(std::string realName);
		void		setBuffer(std::string buffer);
		void		cleanBuffer();
		void		setSd(int sd);
		void		setAddr(sockaddr_in address);
};


template < typename T >
class data
{
	public:
		int					port;
		int					primary_socket;
		struct sockaddr_in	address;
		fd_set				readfds;
		std::string			password;
		std::vector<user *>	users;

		data(){};
		~data(){};
		data(data const& other)
		{
			this->port = other.port;
			this->primary_socket = other.primary_socket;
			this->address = other.address;
			this->readfds = other.readfds;
			this->password = other.password;
			this->users = other.users;
		}

		data operator=(data const& other)
		{
			if (this == &other)
				return (*this);
			this->port = other.port;
			this->primary_socket = other.primary_socket;
			this->address = other.address;
			this->readfds = other.readfds;
			this->password = other.password;
			this->users = other.users;
			return (*this);
		}
};

/* parsing.cpp */
bool	init_and_pars_data(data<user *> &data, char **av);

/* ret_error.cpp */
bool	ret_error(std::string str);

/* connect.cpp */
bool	create_socket(data<user *> &data);
bool	start_online(data<user *>  &data);

/* command_user.cpp */
void	delete_user(data<user *> data, user *cursor);

/* process_cmd.cpp */
void	cmd_process(data<user *> &data);
