#include "../../Includes/lib.hpp"

bool	checkExisteBefor(user *cli, Channel *chan)
{
	std::vector<user *> members = chan->getMembers();
	user *c;
	for (std::vector<user*>::iterator it = members.begin(); it != members.end(); it++)
	{
		c = *it;
		if (c->getSd() == cli->getSd())
			return true;
	}
	return false;
}

std::string	listClients(Channel *chan_cmd)
{
	std::string liste;
	std::vector<user*> members = chan_cmd->getMembers();
	user *index;
	for (std::vector<user *>::iterator it = members.begin(); it != members.end(); it++)
	{
		index = *it;
		if (chan_cmd->isOp(index))
			liste += "@";
		liste += index->getNick() + " ";
	}
	return liste;
}

void	cmd_join(data<user *> &data , user *cursor, std::string buf)
{
	std::vector<std::string> cmd = parse_msg(buf);
	Channel *chan_cmd = NULL;
	std::string msg;
	bool first_time = false;
	if (!(cmd.size() > 1))
	{
		msg = ":server " + std::string(ERR_NEEDMOREPARAMS) + " " + cursor->getNick() + " " + " :" + cmd[0] + ":Not enough parameters\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd[1][0] != '#')
		cmd[1] = '#' + cmd[1];
	if (chan_cmd == NULL && cmd.size() == 2)
		data.channels.push_back(new Channel(cmd[1]));
	else if (!getChan(data, cmd[1]))
		data.channels.push_back(new Channel(cmd[1], cmd[2]));
	chan_cmd = getChan(data, cmd[1]);
	if (chan_cmd->isBanned(cursor))
	{
		msg = ":server " + std::string(ERR_BANNEDFROMCHAN) + " " + cmd[1] + " :Cannot join channel, your are banned\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	if (chan_cmd->isPrivate() && !cursor->isInvited(chan_cmd->getName()))
	{
		msg = ":server " + std::string(ERR_INVITEONLYCHAN) + " " + cmd[1] + " :Cannot join channel, your are not invited\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	else if (chan_cmd->isMember(cursor))
	{
		msg = ":server " + std::string(ERR_USERONCHANNEL) + " " + cursor->getNick() + " " + cursor->getNick() + " :is already on channel\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		return;
	}
	else if (!checkExisteBefor(cursor, chan_cmd))
	{
		chan_cmd->addUser(cursor);
		if (chan_cmd->getMembers().size() == 1)
			chan_cmd->addOp(cursor);
		first_time = true;
	}
	msg = ":" + cursor->getNick() + "!" + cursor->getLogin() + "@" + cursor->getIp() + " JOIN " + cmd[1] + "\r\n";
	send_to_all_members(msg, chan_cmd);
	if (first_time == true)
	{
		msg = ":server " + std::string(RPL_TOPIC) + " " + cursor->getNick() + " " + cmd[1] + " :" + chan_cmd->getTopic() + "\r\n";
		send(cursor->getSd(), msg.c_str(), msg.length(), 0);
		std::vector<user*> members = chan_cmd->getMembers();
		for (std::vector<user*>::iterator it =  members.begin(); it != members.end(); it++)
		{
			msg = ":server " + std::string(RPL_NAMREPLY) + " " + (*it)->getNick() + " = " + chan_cmd->getName() + " :" + listClients(chan_cmd) + "\r\n";
			send((*it)->getSd(), msg.c_str(), msg.length(), 0);
			msg = ":server " + std::string(RPL_ENDOFNAMES) + " " + chan_cmd->getName() + " :End of NAMES list\r\n";
			send((*it)->getSd(), msg.c_str(), msg.length(), 0);
		}
	}
	return ;

	/*
	* Pour mon Foubienne. ( Si tu a un doute http://abcdrfc.free.fr/rfc-vf/rfc1459.html#421 )
	* ex de commande join :
	* JOIN #foobar ; la le user (cursor->getName()) rejoind le canal #foobar.
	* JOIN #foo,#bar ; accède au canaux #foo et #bar.
	*
	* Donc la marche a suivre est la suivante :
	* 1. check dans data.channels si la chan en question existe, sinon la rajouter.
	*
	* 2. check si le user fait deja partie de la channel, si oui revoyer msg d'erreur :
	*    std::string msg = ":server " + std::string(ERR_USERONCHANNEL) + " " + cursor->getNick() + " :is already on channel\r\n";
	*    puis send via :
	*    send(cursor->getSd(), msg.c_str(), msg.length(), 0);
	*    puis on return ; pour retourne a la boucle inf ;) .
	*
	* 3. check si la chan est en mode priver (que sur invitation) et si le user a une invitation
	*     a la rejoindre linvitation est stocker dans le user,
	*    via le vector de string _invited ou je stock le nom des chaines ou le user est inviter.
	*
	* 4. si c'est le premier user a entrer dans la channel ,
	*    il faudra le set en operator channel, via chan->addOp(user).
	*
	* 5. puis la dernierre etape on envoie à l'utilisateur le sujet du canal
	*    (en utilisant RPL_TOPIC) et la liste des utilisateurs du canal (en utilisant RPL_NAMREPLY),
	*    y compris lui-même. (tu peut regarde sur list faut swap RPL_LIST par RPL_NAMREPLY).
	*    si ta besoin d'aide pour la syntax de message retour tu me dit ;).
	*/
}
