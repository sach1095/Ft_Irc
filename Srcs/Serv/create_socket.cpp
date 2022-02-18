#include "../../Includes/lib.hpp"

bool	create_socket(data<user *> &data)
{
	/*
	* Création d'un socket :
	* AF_INET - représente la famille de protocole utilise (AF_INET pour TCP/IP).
	* SOCK_STREAM -  indique le type de service (orienté connexion ou non) dans le cas present communication par flot de données.
	* 0 - permet de spécifier un protocole permettant de fournir le service désiré. Dans le cas de la suite TCP/IP il n'est pas utile.
	*/
	if ((data.primary_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		ret_error("Imposible to create socket");

	//set master socket to allow multiple connections (avoid address already in use pbs)
	int enable = 1;
	if (setsockopt(data.primary_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		ret_error("Error set multiple connections");
	std::cout << "test : " << data.primary_socket << std::endl;
	/*
	* Creation du type de socket
	* sin_family représente le type de famille
	* sin_port représente le port à contacter
	* sin_addr représente l'adresse de l'hôte
	*/
	data.address.sin_family = AF_INET;
	data.address.sin_addr.s_addr = htonl(INADDR_ANY);
	data.address.sin_port = htons(data.port);

	if (bind(data.primary_socket, (struct sockaddr *)&data.address, sizeof(data.address)) < 0)
		ret_error("Error bind return - Socket can't connect");

	std::cout << "listen on port : " << data.port << std::endl;

	/*
	* La fonction listen() permet de mettre un socket en attente de connexion.
	* Ici jusqu'a 3 connexion.
	*/
	if (listen(data.primary_socket, 3) < 0)
		ret_error("Error listen return - Socket can't be in wait states");

	std::cout << "Waiting for connections ..." << std::endl;
	return (SUCCESS);
}