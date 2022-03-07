#include "../../Includes/lib.hpp"

void	delete_user(data<user *> data, user *cursor)
{
	std::vector<user *>::iterator it = data.users.begin();
	cursor->setAccept(false);
	cursor->setSd(0);
	while (it != data.users.end())
	{
		if (*it == cursor)
			break ;
		it++;
	}
	for (std::vector<Channel *>::iterator chan_it = data.channels.begin(); chan_it < data.channels.end(); chan_it++)
	{
		Channel *chan = *chan_it;
		(*chan_it)->deleteEverywhere(*it);
	}
	delete cursor;
	data.users.erase(it);
}
