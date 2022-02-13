#include "../Includes/lib.hpp"

bool	ret_error(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

bool	init_data(t_data *data, char **av)
{
	int	i = 0;

	while (av[1][i])
	{
		if (!isdigit(av[1][i]))
			return (ret_error("Port incorrect.\nPlease check your port again."));
		i++;
	}
	data->port = atoi(av[1]);
	if (av[2])
		data->password.assign(av[2], strlen(av[2]));
	else
		return (ret_error("Password cant be NULL.\nPlease try again witch another password."));
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	if (ac != 3)
		return (ret_error("Number of arguments incorrect.\nPlease follow the rules ./ircserv <port> <password>."));

	t_data data;

	if (init_data(&data ,av))
		return (FAIL);

	std::cout << "parseur :\n\nport = " << data.port << "\npassword = " << data.password << std::endl;
	return (SUCCESS);
}
