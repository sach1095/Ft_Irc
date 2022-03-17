#pragma once

# include "lib.hpp"

class user
{
	private:
		std::string					_nick;
		std::string					_login;
		std::string					_realName;
		std::vector<std::string>	_invited;
		bool		_identify;
		int			_sd;
		bool		_access;
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
		std::string	getBuffer() const;
		sockaddr_in	getAddress() const;
		void		addInvitation(std::string name_chan);
		bool		isInvited(std::string name_chan) const;
		int			getSd() const;
		bool		getAccept() const;
		void		setNick(std::string nick);
		void		setLogin(std::string login);
		void		setRealName(std::string realName);
		void		setBuffer(std::string buffer);
		void		cleanBuffer();
		void		setSd(int sd);
		void		setAccept(bool integer);
		void		setAddr(sockaddr_in address);
		void		setIdentfy(bool b);
		bool		getIdentify(void);

};
