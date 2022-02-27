#pragma once

# include "lib.hpp"

class Channel{

private:
		std::string	_name;
		std::string	_password;
		std::string _topic;
		user *_creator;
		std::vector<user*> _members;
		std::vector<user*> _op;
		std::vector<user*> _banned;
		std::vector<user*> _invited;
		bool _Private;

		Channel();
		Channel(Channel const& other);
		Channel	operator=(Channel const& other);
	public:
		Channel(std::string name);
		Channel(std::string name, std::string topic, std::string password);
		Channel(std::string name, std::string topic);
		~Channel();

		std::string			getName() const;
		std::string			getPassword() const;
		std::string			getTopic() const;
		bool				getPrivate() const;
		std::vector<user*>	getMembers();
		user *getCli(std::string cli);

		void	setName(std::string name);
		void	setPassword(std::string password);
		void	setTopic(std::string topic);
		void	setPrivate(bool b);

		void	addUser(user *cli);
		void	addInvitation(user *cli);
		void	addOp(user *cli);
		void	addBan(user *cli);
		void	deleteUser(user *cli);
		void	deleteBan(std::string cli);
		void	deleteOp(user *cli);
		bool	isMember(user *cli) const;
		bool	isMember(std::string cli) const;
		bool	isOp(user *cli) const;
		bool	isInvited(user *cli) const;
		bool	isInvited(std::string cli) const;
		bool	isBanned(user *cli) const;
		bool	isBanned(std::string cli) const;
};
