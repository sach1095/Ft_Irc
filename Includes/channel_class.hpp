#pragma once

# include "lib.hpp"

class Channel{

private:
		std::string			_name;
		std::string			_topic;
		std::vector<user*>	_members;
		std::vector<user*>	_op;
		user				*_creator;
		bool				_Private;

		Channel();
		Channel(Channel const& other);
		Channel	operator=(Channel const& other);
	public:
		Channel(std::string name);
		Channel(std::string name, std::string topic);
		~Channel();

		std::string			getName() const;
		std::string			getTopic() const;
		bool				getPrivate() const;
		std::vector<user*>	getMembers();
		user				*getCli(std::string cli);

		void	setName(std::string name);
		void	setTopic(std::string topic);
		void	setPrivate(bool b);

		bool	isPrivate() const;
		void	addUser(user *cli);
		void	addOp(user *cli);
		void	deleteUser(user *cli);
		void	deleteOp(user *cli);
		void	deleteEverywhere(user *cli);
		bool	isMember(user *cli) const;
		bool	isMember(std::string cli) const;
		bool	isOp(user *cli) const;

		bool	OpisEmpty();
		bool	MemberisEmpty();
		void	setNewOp();
};
