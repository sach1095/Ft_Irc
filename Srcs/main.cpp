#include "../Includes/lib.hpp"

/*
* Main.
*/
int	main(int ac, char **av)
{
	if (ac != 3)
		return (ret_error("Number of arguments incorrect.\nPlease use: ./ircserv <port> <password>."));

	data<user *> data;

	if (pars_data(data ,av))
		return (FAIL);

	std::cout << "parseur :\n\nport = " << data.port << "\npassword = " << data.password << std::endl;

	if (create_socket(data))
		return 1;
	try
	{
		start_online(data);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (SUCCESS);
}
