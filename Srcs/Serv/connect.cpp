#include "../../Includes/lib.hpp"

static bool	new_connection(data<user *> &data)
{
	int new_socket = 0;
	int size_adress = sizeof(data.address);

	/*
	* try create new socket and connect to it.
	*/
	if ((new_socket = accept(data.primary_socket, (struct sockaddr *)&data.address, (socklen_t *)&size_adress)) < 0)
		ret_error("Connection not accepted");
	/*
	* show connection, socket, ip and port.
	*/
	std::cout << "\n------------------------------------";
	std::cout << "\nNew connection establish,\nsocket fd is : " << new_socket;
	std::cout << "\nIp adress is : " << inet_ntoa(data.address.sin_addr);
	std::cout << "\nPort : " << ntohs(data.address.sin_port);
	std::cout << "\n------------------------------------\n" << std::endl;

	/*
	* add new socket to vector of sockets.
	*/
	data.users.push_back(new user(new_socket, data.address));
	return (SUCCESS);
}

bool start_online(data<user *> &data)
{
	int	max_sd, sd, activity = 0;

	data.online = 1;
	while (data.online)
	{
		FD_ZERO(&data.readfds);
		/*
		* FD_SET, ajout du socket maître
		*/
		FD_SET(data.primary_socket, &data.readfds);
		max_sd = data.primary_socket;

		for(std::vector<user *>::iterator it = data.users.begin(); it != data.users.end(); it++)
		{
			user *cursor = *it;
			sd = cursor->getSd();
			/*
			* Si "socket descriptor" valide, ajout à la liste de lecture
			*/
			if (sd > 0)
				FD_SET(sd, &data.readfds);

			/*
			* "File Descriptor" le plus élevé,
			* nous en avons besoin pour la fonction select()
			*/
			if (sd > max_sd)
				max_sd = sd;
		}
		/*
		* Un des "socketsm timeout" est NULL
		* Attendre indéfiniment
		*/
		activity = select(max_sd + 1, &data.readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno!=EINTR))
			std::cerr << "timeout select" << std::endl;

		/*
		* Si le "master socket" détecte quelque chose,
		* alors c'est une connection entrante
		*/
		if (FD_ISSET(data.primary_socket, &data.readfds))
			new_connection(data);

		/*
		* Ou une opération IO sur un des autres sockets
		*/
		cmd_process(data);
	}
	return (SUCCESS);
}
