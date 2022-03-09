#include "../../Includes/lib.hpp"

static void	parse_cmd(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));
	std::cout << "cmd = : " << buf << std::endl;
	/*
	* Le but principal du protocole IRC est de fournir une base afin que des clients puissent communiquer entre eux.
	* PRIVMSG et NOTICE sont les seuls messages disponibles qui réalisent
	* effectivement l'acheminement d'un message textuel d'un client à un autre,
	* le reste le rend juste possible et assure que cela se passe de façon fiable et structurée.
	*/
	if (cmd == "NICK")
		cmd_nick(data, cursor, buf);
	else if (cmd == "USER")
		cmd_user(data, cursor, buf);
	else if (cmd == "NOTICE")
		cmd_notice(data, cursor, buf);
	else if (cmd == "PRIVMSG")
		cmd_privmsg(data, cursor, buf);
	else if (cmd == "KICK")
		cmd_kick(data, cursor, buf);
	else if (cmd == "EXIT")
		data.online = false;
	else if (cmd == "INVITE")
		cmd_invite(data, cursor, buf);
	else if (cmd == "LIST")
		cmd_list(data, cursor, buf);
	else if (cmd == "JOIN")
		cmd_join(data, cursor, buf);
	else if (cmd == "MODE")
		cmd_mode(data, cursor, buf);
	else if(cmd == "PASS")
	{
		std::string err = ":server " + std::string(ERR_ALREADYREGISTRED) + " " + cmd + " :You are already register\r\n";
		send(cursor->getSd(), err.c_str(), err.length(), 0);
		return ;
	}
	else if (cmd != "PONG")
	{
		std::string str = ":server " + std::string(ERR_UNKNOWNCOMMAND) + " " + cmd + " :Unknown command\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
	}
}

void	cmd_process(data<user *> &data)
{
	int		sd;
	int		ret_read;
	//int		size_adress = sizeof(data.address);
	char	buffer[1024];

	for (std::vector<user *>::iterator it = data.users.begin(); it != data.users.end(); it++)
	{
		user *cursor = *it;
		sd = cursor->getSd();

		if (FD_ISSET(sd, &data.readfds))
		{
			if ((ret_read = read(sd, buffer, 1024)) == 0)
			{
				/*
				* des quelqu'un ce deconnecte, recuperer ses detail et les affiche.
				*/
				getpeername(sd, (struct sockaddr*)&data.address, (socklen_t*)&data.address);
				std::cout << "User " << cursor->getNick() << " disconnected, ip " << inet_ntoa(data.address.sin_addr) << " port " << ntohs(data.address.sin_port) << std::endl;
				/*
				* Close le socket et le set a 0 dans la liste.
				*/
				close(sd);
				sd = 0;
				/*
				* Supprime l'utilisateur de la liste.
				*/
				delete_user(data, cursor);
				return ;
			}
			else
			{
				buffer[ret_read] = '\0';
				if (buffer[ret_read - 1] != '\n')
				{
					cursor->setBuffer(cursor->getBuffer() + buffer);
					return;
				}
				if (cursor->getBuffer().empty())
					cursor->setBuffer(buffer);
				else
					cursor->setBuffer(cursor->getBuffer() + buffer);
				/*
				* Si l'utilisateur est deja accepter,
				* Nous allons commencer a traiter la commande.
				*/
				if (cursor->getAccept() == true)
					parse_cmd(data, cursor, buffer);
				else
				{
					try
					{
						/*
						* A la premier connection d'un user la commande PASS <mdp> est envoye du clien
						* Si le mdp est correct alors user.accepte est set a true.
						* Par la suite le client va nous envoye :
						* NICK <nickname>
						* Puis USER <login> <distance server> <* <realname>>
						*/
						cmd_pass(data, cursor, cursor->getBuffer());
					}
					catch(const std::exception& e)
					{
						send(cursor->getSd(), e.what(), std::strlen(e.what()), 0);
						close(sd);
						sd = 0;
						delete_user(data, cursor);
						return ;
					}
				}
				cursor->cleanBuffer();
			}
		}
	}
}
