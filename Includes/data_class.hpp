#pragma once

# include "lib.hpp"

// class user;
// class Channel;

template < typename T >
class data
{
	public:
		int						port;
		int						primary_socket;
		int						online;
		struct sockaddr_in		address;
		fd_set					readfds;
		std::string				password;
		std::vector<user *>		users;
		std::vector<Channel *>	channels;

		data(){};
		~data()
		{
			puts("aikkk");
			for (std::vector<user *>::iterator it = users.begin(); it != users.end(); it++)
			{
				close((*it)->getSd());
				delete *it;
			}
			users.clear();
			for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
				delete *it;
			channels.clear();
		}
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
