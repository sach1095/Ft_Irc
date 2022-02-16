#include "../Includes/lib.hpp"

bool	create_socket(t_data *data)
{
	/*
	* Création d'un socket :
	* AF_INET - représente la famille de protocole utilise (AF_INET pour TCP/IP).
	* SOCK_STREAM -  indique le type de service (orienté connexion ou non) dans le cas present communication par flot de données.
	* 0 - permet de spécifier un protocole permettant de fournir le service désiré. Dans le cas de la suite TCP/IP il n'est pas utile.
	*/
	if ((data->serv.primary_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ret_error("Imposible to create socket");

	/*
	* Creation du type de socket
	* sin_family représente le type de famille
	* sin_port représente le port à contacter
	* sin_addr représente l'adresse de l'hôte
	*/
	data->serv.address.sin_family = AF_INET;
	data->serv.address.sin_addr.s_addr = htonl(INADDR_ANY);
	data->serv.address.sin_port = htons(data->serv.port);

	if (bind(data->serv.primary_socket, (struct sockaddr *)&data->serv.address, sizeof(data->serv.address)) < 0)
		ret_error("Error bind return - Socket can't connect");

	/*
	* La fonction listen() permet de mettre un socket en attente de connexion.
	* Ici jusqu'a 10 connexion.
	*/
	if (listen(data->serv.primary_socket, 10) != SUCCESS)
		ret_error("Error listen return - Socket can't be in wait states");

	/* to continue avec select, accepte et connect */
}
