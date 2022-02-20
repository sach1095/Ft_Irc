#include "../../Includes/lib.hpp"

void	parse_cmd(data<user *> &data , user *cursor, std::string buf)
{
	std::string cmd = buf.substr(0, buf.find(' '));

	/*
	* Le but principal du protocole IRC est de fournir une base afin que des clients puissent communiquer entre eux.
	* PRIVMSG et NOTICE sont les seuls messages disponibles qui réalisent
	* effectivement l'acheminement d'un message textuel d'un client à un autre,
	* le reste le rend juste possible et assure que cela se passe de façon fiable et structurée.
	*/
	if (cmd == "NICK" || cmd == "/nick")
		cmd_nick(data, cursor, buf);
	else if (cmd == "USER" || cmd == "/user")
		cmd_user(data, cursor, buf);
	else if (cmd == "QUIT" || cmd == "/quit")
	{
		// faire une commande qui fait quitte proprement le clien;
	}
	else if (cmd == "PART" || cmd == "/part")
	{
		/* Le message PART provoque le retrait du client expéditeur de la liste
		* des utilisateurs actifs pour tous les canaux listés dans la chaîne de paramètres.
		*/
	}
	else if (cmd == "JOIN" || cmd == "/join")
	{
		/* join permet de rejoindre un canal si il existe ou de le cree dans le cas echean.
		* l'utilisateur doit être invité si le canal est en mode "sur invitation seulement" (voir MODE)
		* le pseudo/nom d'utilisateur/nom d'hôte ne doit pas correspondre à un bannissement actif.
		* une clef peut etre demander si le salon en a une.
		* ex: JOIN #foo,#bar fubar,foobar ;
		* accède au canal #foo en utilisant la clé "fubar", et au canal #bar en utilisant la clé "foobar".
		*/

	}
	else if (cmd == "MODE" || cmd == "/mode")
	{
		// Ce referer a l'article 4.2.3 de http://abcdrfc.free.fr/rfc-vf/rfc1459.html#411 .
	}
	else if (cmd == "TOPIC" || cmd == "/topic")
	{
		/* TOPIC est utilisé pour modifier ou voir le sujet d'un canal.
		* Le sujet du canal <canal> est renvoyé s'il n'y a pas de <sujet> fourni en paramètre.
		*/
	}
	else if (cmd == "INVITE" || cmd == "/invite")
	{
		/*
		* Paramètres: <pseudonyme> <canal>
		* Le message INVITE est utilisé pour inviter des utilisateurs dans un canal.
		* Le paramètre <pseudonyme> est le pseudonyme de la personne à inviter dans le canal destination <canal>.
		* Il n'est pas nécessaire que le canal dans lequel la personne est invitée existe, ni même soit valide.
		* Pour inviter une personne dans un canal en mode sur invitation (MODE +i),
		* le client envoyant l'invitation doit être opérateur sur le canal désigné.
		*/
	}
	else if (cmd == "NOTICE" || cmd == "/notice")
	{
		/*
		* Lire PRIVMSG en meme temps.
		* Ce referer a l'article 4.4.2 de http://abcdrfc.free.fr/rfc-vf/rfc1459.html#411 .
		*/
		//
	}
	else if (cmd == "PRIVMSG" || cmd == "/privmsg")
	{
		// Ce referer a l'article 4.4.1 de http://abcdrfc.free.fr/rfc-vf/rfc1459.html#411 .
	}
	else if (cmd == "KICK" || cmd == "/kick")
	{
		/*
		* Paramètres: <canal> <utilisateur> [<commentaire>]
		* La commande KICK est utilisée pour retirer par la force un utilisateur d'un canal.
		*/
	}
	else if (cmd == "LIST" || cmd == "/list")
	{
		/*
		* Paramètres: [<canal>{,<canal>} [<serveur>]]
		* Le message LIST est utilisé pour lister les canaux et leur sujet. Si le paramètre <canal> est utilisé,
		* seul le statut de ces canaux est affiché. Les canaux privés sont listés (sans leur sujet) comme canal "Prv"
		* à moins que le client qui génère la requête soit effectivement sur le canal. De même,
		* les canaux secrets ne sont pas listés du tout, à moins que le client soit un membre du canal en question.
		*/
	}
	else if (cmd == "NAME" || cmd == "/name")
	{
		/*
		* Paramètres: [<canal>{,<canal>}]

		* En utilisant la commande NAMES, un utilisateur peut obtenir la liste des pseudonymes visibles
		* sur n'importe quel canal qu'il peut voir. Les noms de canaux qu'il peut voir sont ceux qui ne sont
		* ni privés (+p), ni secrets (+s), ou ceux sur lesquels il est actuellement.
		* Le paramètre <canal> spécifie quels sont les canaux dont l'information est voulue, s'ils sont valides.
		* Il n'y a pas de message d'erreur pour les noms de canaux invalides.
		*/
	}
	else{
		std::string str = ":server " + std::string(ERR_UNKNOWNCOMMAND) + " " + cmd + " :Unknown command\r\n";
		send(cursor->getSd(), str.c_str(), str.length(), 0);
	}
}

void	cmd_process(data<user *> &data)
{
	int		sd;
	int		ret_read;
	int		size_adress = sizeof(data.address);
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
				* if someone is disconnected, get his details and print hem.
				*/
				getpeername(sd, (struct sockaddr*)&data.address, (socklen_t*)&data.address);
				std::cout << "User disconnected, ip " << inet_ntoa(data.address.sin_addr) << " port " << ntohs(data.address.sin_port) << std::endl;
				/*
				* close the socket and set is as 0 in list.
				*/
				close(sd);
				sd = 0;
				/*
				* delete the user from the list.
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
				std::cout << "Cmd " << " : " << cursor->getBuffer() << std::endl;
				std::string command = cursor->getBuffer().substr(0, cursor->getBuffer().find(' '));

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