#include "../Includes/lib.hpp"

/*
* Main.
*/
int	main(int ac, char **av)
{
	if (ac != 3)
		return (ret_error("Number of arguments incorrect.\nPlease follow the rules ./ircserv <port> <password>."));

	data<user *> data;

	if (init_and_pars_data(data ,av))
		return (FAIL);

	std::cout << "parseur :\n\nport = " << data.port << "\npassword = " << data.password << std::endl;

	create_socket(data);
	start_online(data);
	return (SUCCESS);
}
