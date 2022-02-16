#include "../Includes/lib.hpp"

/*
/* Main.
*/
int		main(int ac, char **av)
{
	if (ac != 3)
		return (ret_error("Number of arguments incorrect.\nPlease follow the rules ./ircserv <port> <password>."));

	t_data data;

	if (init_and_pars_data(&data ,av))
		return (FAIL);

	std::cout << "parseur :\n\nport = " << data.serv.port << "\npassword = " << data.serv.password << std::endl;

	create_socket(&data);
	return (SUCCESS);
}
