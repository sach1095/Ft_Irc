#include "../../Includes/lib.hpp"

void	delete_user(data<user *> &data, user *cursor)
{
	std::vector<user *>::iterator it = data.users.begin();
	std::vector<Channel*>::iterator ite = data.channels.end();
	for (std::vector<Channel*>::iterator it = data.channels.begin(); it != ite; it++)
	{
		(*it)->deleteEverywhere(cursor);
	}
	while (it != data.users.end())
	{
		if (*it == cursor)
			break ;
		it++;
	}
	delete cursor;
	data.users.erase(it);
}
